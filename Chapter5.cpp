#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

float w = 250, h = 350;
Mat matrix, imgWarp, imgWarp2;

//Warping an image

int main() {

    string path = "Resources/cards.jpg";
    Mat img = imread(path);

    Point2f src[4] = { {529,142}, {771, 190}, {405,395}, {674, 457} }; //Array to hold king's card corner coordinates
    Point2f dst[4] = { {0.0f,0.0f}, {w, 0.0f}, {0.0f,h}, {w, h} }; //New warped image

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h)); //Warp the image to extract the king

    Point2f src2[4] = { {66,327}, {333, 280}, {95,632}, {399, 569} }; //Array to hold queen's card corner coordinates
    matrix = getPerspectiveTransform(src2, dst);
    warpPerspective(img, imgWarp2, matrix, Point(w, h)); //Warp the image to extract the queen

    //Display where the coordinates have been taken from
    for (int i = 0; i < 4; i++) {
        circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
    }
    for (int i = 0; i < 4; i++) {
        circle(img, src2[i], 10, Scalar(0, 0, 255), FILLED);
    }

    imshow("Image", img);
    imshow("Image Warp King", imgWarp);
    imshow("Image Warp Queen", imgWarp2);
    waitKey(0);




	return 0;
}