#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {


    VideoCapture capture;
    Mat frame, img;

    capture.open(0);

    while (true) {
        capture >> frame;

        resize(frame, frame, Size(320, 240));
        
        CascadeClassifier faceCascade;
        faceCascade.load("Resources/haarcascade_frontalface_default.xml");

        vector<Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 10); //

        for (int i = 0; i < faces.size();i++) {
            rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3); //

        }

        imshow("Image", frame);
        waitKey(1);
        faces.clear();

    }

	return 0;
}