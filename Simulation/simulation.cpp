#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <vector>
using namespace cv;
using namespace std;
int main(int, char **) {
  vector<uchar> buffer;
  vector<int> encodeParams;
  encodeParams.push_back(IMWRITE_JPEG_QUALITY);
  encodeParams.push_back(10);
  Mat frame;
  Mat decodedFrame;
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
  cout << "Start grabbing" << endl << "Press any key to terminate" << endl;
  for (;;) {
    buffer.clear();
    // wait for a new frame from camera and store it into 'frame'
    cap.read(frame);
    // check if we succeeded
    if (frame.empty()) {
      cerr << "ERROR! blank frame grabbed\n";
      break;
    }
    imencode(".jpg", frame, buffer, encodeParams);

    decodedFrame = imdecode(buffer, IMREAD_UNCHANGED);
    if (decodedFrame.empty()) {
      cerr << "ERROR! cannot decode frame\n";
      break;
    }
    // show live and wait for a key with timeout long enough to show images
    imshow("Live", decodedFrame);
    if (waitKey(5) == 27)
      break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
