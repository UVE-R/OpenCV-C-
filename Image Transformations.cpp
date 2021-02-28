#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//Colour Conversions, Blurs, Dilation, Erosion

int main() {

    string path = "Resources/test.png";
    Mat img = imread(path), imgGray, imgBlur, imgCanny, imgDil, imgErode;
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY); //Convert to grayscale
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0); //Blur image
    Canny(imgBlur, imgCanny, 25, 75); //Draws edges of shapes of images

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //Creates kernel for dialation, Size must be odd
    dilate(imgCanny, imgDil, kernel); //Adds pixels to object boundaries
    erode(imgDil, imgErode, kernel); //Removes pixels on object boundaries


    imshow("Image", img);
    //imshow("Image Grey", imgGray);
    //imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);
    imshow("Image Erode", imgErode);
    waitKey(0);

    return 0;
}
