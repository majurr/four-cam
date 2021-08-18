#include "includes/CameraStreamer.hpp"

CameraStreamer::CameraStreamer(vector<string> stream_source) {
    camera_source = stream_source;
    camera_count = camera_source.size();
    isUSBCamera = false;

    startMultiCapture();
}

CameraStreamer::CameraStreamer(vector<int> capture_index) {
    camera_index = capture_index;
    camera_count = capture_index.size();
    isUSBCamera = true;

    startMultiCapture();
}

CameraStreamer::~CameraStreamer() {
    stopMultiCapture();
}

void CameraStreamer::captureFrame(int index){
    cv::VideoCapture *capture = camera_capture[index];

    while(true) {
        Mat frame;
        (*capture) >> frame;
        frame_queue[index]->push(frame);
        frame.release();
    }
}

void CameraStreamer::startMultiCapture(){
    cv::VideoCapture *capture;
    thread *t;
    concurrent_queue<Mat> *q;

    for (int i = 0; i < camera_count; i++) {
        if(!isUSBCamera) {
            string url = camera_source[i];
            capture = new cv::VideoCapture(url);
            cout << "Camera Setup: " << url << endl;
        } else {
            int idx = camera_index[i];
            capture = new cv::VideoCapture(idx);
            
            // capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
            // capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
            
            cout << "Camera Setup: " << to_string(idx) << endl;
        }

        camera_capture.push_back(capture);
        t = new thread(&CameraStreamer::captureFrame, this, i);
        camera_thread.push_back(t);
        q = new concurrent_queue<Mat>;
        frame_queue.push_back(q);
    }
}

void CameraStreamer::stopMultiCapture()
{
    cv::VideoCapture *cap;
    for(int i = 0; i < camera_count; i++) {
        cap = camera_capture[i];
        if(cap->isOpened()){
            cap->release();
            cout << "Capture " << i << " released" << endl;
        }
    }
}
