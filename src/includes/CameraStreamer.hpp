#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <tbb/concurrent_queue.h>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;
using namespace tbb;

class CameraStreamer{
    public:
    vector<string> camera_source;
    vector<int> camera_index;
    vector<VideoCapture*> camera_capture;
    vector<concurrent_queue<Mat>*> frame_queue;
    vector<thread*> camera_thread;

    // constructor for IP Camera capture
    CameraStreamer(vector<string> source);
    // constructor for USB Camera capture
    CameraStreamer(vector<int> index);
    // destructor for releasing resource(s)
    ~CameraStreamer();

    private:
    bool isUSBCamera;
    int camera_count;
    void startMultiCapture();
    void stopMultiCapture();
    void captureFrame(int index);
};
