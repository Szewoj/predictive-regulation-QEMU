#include <fcntl.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <sys/timerfd.h>
#include <thread>
#include <unistd.h>

#include "InPort.h"
#include "SimObject.h"
#include "pshm_stc.h"

int main(int, char **) {

  //--- INITIALIZE SHARED MEMORY
  int fd = shm_open("/regShm", O_RDWR, S_IWUSR);
  if (fd == -1)
        errExit("shm_open");
  struct shm_data *shm = (shm_data*) mmap(NULL, sizeof(struct shm_data), PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);
  //---

  //--- INITIALIZE COMUNICATION THREAD
  std::shared_ptr<InPort> tcpPort = std::make_shared<InPort>();
  std::thread commThread(InPort::threadCall, tcpPort);
  //---

  //--- INITIALIZE SIMULATION VARIABLES
  double y, u, z;
  SimObject simulation;
  //---

  //--- INITIALIZE VIDEOCAPTURE
  std::cout << "OpenCV Version used: " << CV_MAJOR_VERSION << "."
            << CV_MINOR_VERSION << std::endl;
  cv::Mat frame;
  cv::Vec3b pixel, redPix;
  cv::VideoCapture cap;

  redPix[0] = 0;
  redPix[1] = 0;
  redPix[2] = 255;

  // open the default camera using default API
  // cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 0;        // 0 = open default camera
  int apiID = cv::CAP_ANY; // 0 = autodetect default API
  // open selected camera using selected API
  cap.open(deviceID, apiID);
  // check if we succeeded
  if (!cap.isOpened()) {
    std::cerr << "ERROR! Unable to open camera\n";
    return -1;
  }
  //---

  //--- INITIALIZE TIMERFD
  struct itimerspec timerSpec;
  int timerFD;
  int64_t numExp;
  ssize_t sizeRead;

  timerFD = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
  if (timerFD == -1) {
    std::cerr << "ERROR unable to create timerfd\n";
    exit(EXIT_FAILURE);
  }

  timerSpec.it_value.tv_sec = 1;
  timerSpec.it_value.tv_nsec = 0;

  timerSpec.it_interval.tv_sec = 0;
  timerSpec.it_interval.tv_nsec = 500000000;
  //---

  //--- START TIMERFD
  if (timerfd_settime(timerFD, 0, &timerSpec, NULL) == -1) {
    std::cerr << "ERROR cannot initialize timerFD (settime)\n";
  }
  std::cout << "Timer started with interval " << timerSpec.it_interval.tv_nsec
            << "ms.\n";
  //---

  for (;;) {

    // wait for a new frame from camera and store it into 'frame'
    cap.read(frame);

    // check if we succeeded
    if (frame.empty()) {
      std::cerr << "ERROR! blank frame grabbed\n";
      exit(EXIT_FAILURE);
    }
    // calculate center pixel
    int centerRow = frame.rows / 2;
    int centerCol = frame.cols / 2;

    // paint crosshair for reference
    for (int i = 2; i < 10; ++i) {
      frame.at<cv::Vec3b>(centerRow + i, centerCol) = redPix;
      frame.at<cv::Vec3b>(centerRow, centerCol + i) = redPix;
      frame.at<cv::Vec3b>(centerRow - i, centerCol) = redPix;
      frame.at<cv::Vec3b>(centerRow, centerCol - i) = redPix;
    }

    cv::imshow("Live", frame);

    // wait for timerfd expiration
    sizeRead = read(timerFD, &numExp, sizeof(uint64_t));
    if (numExp > 0) {
      // reset timer expiration variable
      numExp = 0;

      // copy u from buffer (atomic variable)
      u = tcpPort->u_;

      // get center pixel and calculate luminance
      pixel = frame.at<cv::Vec3b>(centerRow, centerCol);
      int luminance = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];

      // calculate disturbance signal
      z = luminance * 100.0 / 255.0;

      // calculate y
      y = simulation.CalculateY(u, z);

      std::cout << "y = " << y << '\n';

      // save variables to port memory
      tcpPort->z_ = z;
      tcpPort->y_ = y;

      // save variables to shm
      pthread_rwlock_wrlock(&shm->rw);
        memcpy(&shm->Y,(char*)&y, sizeof(double));
        memcpy(&shm->U,(char*)&u, sizeof(double));
        memcpy(&shm->Z,(char*)&z, sizeof(double));
      pthread_rwlock_unlock(&shm->rw);
    }

    if (cv::waitKey(5) == 27)
      break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  exit(EXIT_SUCCESS);
}
