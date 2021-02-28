#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void getContours(Mat imgDil, Mat img) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //Finding contours and store in contours
    vector<vector<Point>> conPoly(contours.size());//Stores number of approximate verticies
    vector<Rect> boundRect(contours.size());//Stores Rectangles which bound each shape
   
    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        string objectType; //Stores which shape it is
        if (area > 1000) {
            float peri = arcLength(contours[i], true); //Find perimeter
            approxPolyDP(contours[i], conPoly[i], 0.02*peri,true); //Approximates contour shape to another shape
            boundRect[i] = boundingRect(conPoly[i]); //Store rectangle           
            
            int objCor = (int)conPoly[i].size();
            
            if (objCor == 3) {
                objectType = "Triangle";
            }else if (objCor == 4) {
                //If the ratio is height and width are roughly the same then it is a square
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;                
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                }
                else {
                    objectType = "Rectangle";
                }               
            }
            else if (objCor > 4) {
                objectType = "Circle";
            }
            
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); //Draw all contours
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); //Add Rectangle for Rectangular Dimensions
            putText(img, objectType, { boundRect[i].x,boundRect[i].y -5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1); //Display which shape

        }
    }
}

//Shape Detection
int main() {

    string path = "Resources/shapes.png";
    Mat img = imread(path), imgGray, imgBlur, imgCanny, imgDil, imgErode;

    //Preprocessing
    cvtColor(img, imgGray, COLOR_BGR2GRAY); //Convert to grayscale
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0); //Blur image
    Canny(imgBlur, imgCanny, 25, 75); //Draws edges of shapes of images    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //Creates kernel for dialation, Size must be odd
    dilate(imgCanny, imgDil, kernel); //Adds pixels to object boundaries
    
    //Displays all contours(curve joining all points with same colour/intensity)
    getContours(imgDil, img);

    imshow("Image", img);    
    waitKey(0);



	return 0;
}
