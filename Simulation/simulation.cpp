#include <fcntl.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
//#include <semaphore.h>
//#include <sys/mman.h>
//#include <sys/stat.h>

using namespace cv;
using namespace std;

int main(int, char **) {

  Mat frame;

  //--- INITIALIZE VIDEOCAPTURE
  VideoCapture cap;
  // open the default camera using default API
  // cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 0;        // 0 = open default camera
  int apiID = cv::CAP_ANY; // 0 = autodetect default API
  // open selected camera using selected API
  cap.open(deviceID, apiID);
  // check if we succeeded
  if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open camera\n";
    return -1;
  }

  //--- GRAB AND WRITE LOOP
  cout << "Start grabbing" << '\n' << "Press any key to terminate" << '\n';

  // wait for a new frame from camera and store it into 'frame'
  cap.read(frame);
  // check if we succeeded
  if (frame.empty()) {
    cerr << "ERROR! blank frame grabbed\n";
    return 1;
  }

  // show live and wait for a key with timeout long enough to show images
  imshow("Snapshot", frame);

  //int centerRow = frame.rows / 2;
  //int centerCol = frame.cols / 2;

  int dims = frame.size.dims();

  cout << "Matrix dimensions: " << dims << '\n';
  for (int i = 0; i < dims; ++i){
    cout << frame.size[i] << ' ';
  }
  cout << '\n';

  int centerRow = frame.rows / 2;
  int centerCol = frame.cols / 2;

  cout << "Center row, col " << centerRow << ' ' << centerCol << '\n';

  Vec3b pixel = frame.at<Vec3b>(centerRow, centerCol);

  int luminance = 0.299*pixel[2] + 0.587*pixel[1] + 0.114*pixel[0];

  cout << "Luminance " << luminance << '\n';

  for (;;) {
    if (waitKey(100) == 27)
      break;
  }

  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
