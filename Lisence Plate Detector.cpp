#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Face detection
int main() {

    VideoCapture cap(0);
    Mat img;

    CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml"); //Load Classifier

    if (plateCascade.empty()) { cout << "XML file not loaded" << endl; } //Check if file is present

    vector<Rect> plates; //Stores rectangles to bound plate

    while (true) {
        cap.read(img);
        plateCascade.detectMultiScale(img, plates, 1.1, 10); //Detect Plate

        //Display multiple images 
        for (int i = 0; i < plates.size();i++) {
            Mat imgCrop = img(plates[i]);
            imshow(to_string(i), imgCrop);
            imwrite("Resources/Plates/" + to_string(i) + ".png", imgCrop); //Save image
            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3); //Draw rectangles to bound face

        }

        imshow("Image", img);
        waitKey(1);
    }


    return 0;
}
