#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Displaying files

//Displaying a picture
void picture() {
    string path = "Resources/test.png";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);

}

//Displaying a video
void video() {

    string path = "Resources/test_video.mp4";
    VideoCapture cap(path);
    Mat img;

    while (true) {

        cap.read(img);
        imshow("Image", img);
        waitKey(20);

    }
}

//Display webcam
void webcam() {

    VideoCapture cap(0);
    Mat img;

    while (true) {

        cap.read(img);
        imshow("Image", img);
        waitKey(1);

    }

}

int main() {

    picture();
    video();
    webcam();

    return 0;
}
