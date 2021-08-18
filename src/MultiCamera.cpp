#include "includes/CameraStreamer.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, char** argv) {
    // IP Câmera - urls
    /*
    vector<string> capture_source = {
        "",
        ""
    };
    */
    // USB Câmera - índices
    vector<int> capture_index = {0, 2, 4};

    vector<string> label;
    for(int i = 0; i < capture_index.size(); i++){
        string title = "CiMMov " + to_string(i);
        label.push_back(title);
    }

    CameraStreamer cam(capture_index);

    while (waitKey(20) != 27) {
        for (int i = 0; i < capture_index.size(); i++) {
            Mat frame;
            if (cam.frame_queue[i]->try_pop(frame)) {
                imshow(label[i], frame);
            }
        }
    }
}
