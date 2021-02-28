#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//Cropping and resizing
int main() {

	string path = "Resources/test.png";
	Mat img = imread(path), imgResize, imgCrop;
	

	//resize(img, imgResize, Size(640, 480)); //Resize an image by pixels
	resize(img, imgResize, Size(), 0.5, 0.5); //Resize an image by scale

	Rect roi(200, 100, 300, 300); //Create a rectangle to act as the new image dimendions
	imgCrop = img(roi); //Crop the image by the rectangle



	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	waitKey(0);


	return 0;
}
