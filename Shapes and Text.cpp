#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Adding shapes and text

int main() {

	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); //Create blank white image

	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED); //Add filled circle to centre of image

	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); //Add filled rectangle

	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2); //Add solid line

	putText(img, "STOP", Point(137, 280), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 69, 255), 2); //Add Text

	imshow("Image", img);
	waitKey(0);


	return 0;
}
