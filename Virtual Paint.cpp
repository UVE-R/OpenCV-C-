#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img; //Image read in from webcam

vector<vector<int>> newPoints; //Stoes x,y and colour for each point

//Stores each colour settings
vector<vector<int>> myColours{ {60,60,26,110,181,93}, //Green   60,110,60,181,26,93
                                {16,42,91,36,218,181}}; //Yellow  16,36,42,218,91,181

//Stores which colour is detected
vector<Scalar>myColourValues{ {0,255,0}, //Green
                              {255,255,0} }; //Yellow

//Return coordinates of bounding rectangle of the detected contour
Point getContours(Mat imgDil) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //Finding contours and store in contours
    vector<vector<Point>> conPoly(contours.size());//Stores number of approximate verticies
    vector<Rect> boundRect(contours.size());//Stores Rectangles which bound each shape
    
    Point myPoint(0, 0);

    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);

        if (area > 1000) {
            float peri = arcLength(contours[i], true); //Find perimeter
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); //Approximates contour shape to another shape
            boundRect[i] = boundingRect(conPoly[i]); //Store rectangle           

            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); //Draw all contours
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); //Add Rectangle for Rectangular Dimensions
        }
    }
    return myPoint;
}

vector<vector<int>> findColour(Mat img) {
    Mat imgHSV;

    cvtColor(img, imgHSV, COLOR_BGR2HSV); //Convert to HSV

    for (int i = 0; i < myColours.size(); i++) {
        Scalar lower(myColours[i][0], myColours[i][1], myColours[i][2]);
        Scalar upper(myColours[i][3], myColours[i][4], myColours[i][5]);
        Mat mask;
        inRange(imgHSV, lower, upper, mask);
        //imshow(to_string(i), mask);
        Point myPoint = getContours(mask); //Get the points of the contour

        if (myPoint.x != 0 && myPoint.y != 0) {
            newPoints.push_back({ myPoint.x, myPoint.y, i }); //Add each detected contour to newPoints
        }
        
    }
    return newPoints;

}

//Draws circles on the screen from the coordinates of the contour
void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar>myColourValues) {
    for (int i = 0; i < newPoints.size();i++) {
        circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColourValues[newPoints[i][2]], FILLED);
    }
}

int main() {
    VideoCapture cap(0);
    while (true) {
        cap.read(img); //Read webcam image
        newPoints = findColour(img); //Get points of all the detected contours
        drawOnCanvas(newPoints,myColourValues); //Draw the points on screen
        imshow("Image", img);
        waitKey(1);
    }
    return 0;
}
