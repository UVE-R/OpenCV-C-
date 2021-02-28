#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, imgDil, imgGray, imgCanny, imgBlur, imgThre, imgWarp, imgCrop;

vector<Point>initialPoints, docPoints;

float w = 420, h = 596; //Width and height of paper

Mat preProcessing(Mat img) {
    cvtColor(img, imgGray, COLOR_BGR2GRAY); //Convert to grayscale
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0); //Blur image
    Canny(imgBlur, imgCanny, 25, 75); //Draws edges of shapes of images

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //Creates kernel for dialation, Size must be odd
    dilate(imgCanny, imgDil, kernel); //Adds pixels to object boundaries
    //erode(imgDil, imgErode, kernel); //Removes pixels on object boundaries

    return imgDil;
}

vector<Point> getContours(Mat imgDil) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //Finding contours and store in contours
    vector<vector<Point>> conPoly(contours.size());//Stores number of approximate verticies
    vector<Rect> boundRect(contours.size());//Stores Rectangles which bound each shape

    vector<Point>biggest;
    int MaxA = 0;

    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);

        if (area > 1000) {
            float peri = arcLength(contours[i], true); //Find perimeter
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); //Approximates contour shape to another shape

            if (area > MaxA && conPoly[i].size() ==4) {
                biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
                MaxA = area;
                //drawContours(img, conPoly, i, Scalar(255, 0, 255), 5); //Draw all contours that fit the description
            }

            //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); //Add Rectangle for Rectangular Dimensions
        }
    }
    return biggest;
}

vector<Point> reorder(vector<Point>points) {
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for (int i = 0; i < 4; i++) {
        sumPoints.push_back(points[i].x + points[i].y);
    }
    for (int i = 0; i < 4; i++) {
        subPoints.push_back(points[i].x - points[i].y);
    }

    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

    return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {

    Point2f src[4] = { points[0], points[1], points[2], points[3] }; //Array to hold document's corner coordinates
    Point2f dst[4] = { {0.0f,0.0f}, {w, 0.0f}, {0.0f,h}, {w, h} }; //New warped image

    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h)); //Warp the image to extract the document

    return imgWarp;

}

int main() {

    VideoCapture capture;
    capture.open(0);

    while (true) {
        capture >> img;

        waitKey(10);
        //Preprocess image
        imgDil = preProcessing(img);

        //Get the contours
        initialPoints = getContours(imgDil);

        //Reorder points
        docPoints = reorder(initialPoints);

        //Warp
        imgWarp = getWarp(img, docPoints, w, h);

        imshow("Image", img);
        imshow("Image Processed", imgDil);
        imshow("Document", imgWarp);
        waitKey(1);

    }


	return 0;
}