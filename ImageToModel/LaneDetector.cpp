//
//  LaneDetector.cpp
//  ImageToModel
//
//  Created by James Macbook on 6/8/22.
//

#include "LaneDetector.hpp"

using namespace cv;
using namespace std;

double getAverage(vector<double> vector, int nElements){
    double sum = 0;
    int initialIndex = 0;
    int last30Lines = int(vector.size()) - nElements;
    if (last30Lines > 0){
        initialIndex = last30Lines;
    }
    
    for (int i = initialIndex; i<vector.size(); i++){
        sum += vector[i];
    }
    
    int size;
    if (vector.size() < nElements) {
        size = (int)vector.size();
    } else {
        size = nElements;
    }
    
    return (double)sum/size;
}

Mat LaneDetector::detect_lane(Mat image) {
    Mat colorFilteredImage = filter_only_yellow_white(image);
    Mat regionOfInterest = crop_region_of_interest(colorFilteredImage);
    Mat edgesOnly = detect_edges(regionOfInterest);
    
    vector<Vec4i> lines;
    HoughLinesP(edgesOnly, lines, 1, CV_PI/180, 10, 20, 100);
    
    return draw_lines(image, lines);
}


Mat LaneDetector::filter_only_yellow_white(Mat image) {
    Mat hlsColorspacedImage;
    //might change to BGR to match videoDataOutput.videoSettings
    cvtColor(image, hlsColorspacedImage, COLOR_RGB2HLS); //Hue, lightness, saturation
    
    Mat yellowMask;
    Scalar yellowLower = Scalar(10,0,90);
    Scalar yellowUpper = Scalar(50,255,255);
    inRange(hlsColorspacedImage,yellowLower,yellowUpper,yellowMask);
    
    Mat whiteMask;
    Scalar whiteLower = Scalar(0,190,0);
    Scalar whiteUpper = Scalar(255,255,255);
    inRange(hlsColorspacedImage, whiteLower, whiteUpper, whiteMask);
    
    Mat mask;
    bitwise_or(yellowMask, whiteMask, mask);
    
    Mat maskedImage;
    bitwise_and(image, image, maskedImage, mask);
    
    return maskedImage;
}

Mat LaneDetector::crop_region_of_interest(Mat image){
    int maxX = image.rows;
    int maxY = image.cols;
    
    Point shape[1][5];
    shape[0][0] = Point(0,maxX);
    shape[0][1] = Point(maxY,maxX);
    shape[0][2] = Point((int)(0.55 * maxY), (int)(0.6 * maxX));
    shape[0][3] = Point((int)(0.55 * maxY), (int)(0.6 * maxX));
    shape[0][4] = Point(0,maxX);
    
    Scalar color_to_filter(255,255,255);
    
    Mat filledPolygon = Mat::zeros(image.rows, image.cols, CV_8UC3);
    const Point* polygonPoints[1] = {shape[0]};
    int numberOfPoints[] = {5};
    int numberOfPolygons = 1;
    fillPoly(filledPolygon, polygonPoints, numberOfPoints, numberOfPolygons, color_to_filter);
    
    Mat maskedImage;
    bitwise_and(image,filledPolygon, maskedImage);
    
    return maskedImage;
}

Mat LaneDetector::draw_lines(Mat image, vector<Vec4i> lines){
    vector<double> rightSlope, leftSlope, rightIntercept, leftIntercept;
    
    for (int i=0; i<lines.size(); i++){
        Vec4i line = lines[i];
        double x1 = line[0];
        double y1 = line[1];
        double x2 = line[2];
        double y2 = line[3];
        
        double yDiff = y1-y2;
        double xDiff = x1-x2;
        double slope = yDiff/xDiff;
        double yIntercept = y2 - (slope*x2);
        
        if((slope > 0.3) && (x1 > 500)) {
            rightSlope.push_back(slope);
            rightIntercept.push_back(yIntercept);
        } else if ((slope < -0.3) && (x1 < 600)) {
            leftSlope.push_back(slope);
            leftIntercept.push_back(yIntercept);
        }
        
        double leftAvgSlope = getAverage(leftSlope, 30);
        double leftAvgIntercept = getAverage(leftIntercept, 30);
        double rightAvgSlope = getAverage(rightSlope, 30);
        double rightAvgIntercept = getAverage(rightIntercept, 30);
        
        int leftLineX1 = int(((0.65*image.rows) - leftAvgIntercept)/leftAvgSlope);
        int leftLineX2 = int(((image.rows) - leftAvgIntercept)/leftAvgSlope);
        int rightLineX1 = int(((0.65*image.rows) - rightAvgIntercept)/rightAvgSlope);
        int rightLineX2 = int(((image.rows) - rightAvgIntercept)/rightAvgSlope);
        
        Point shape[1][4];
        shape[0][0] = Point(leftLineX1, int(0.65*image.rows));
        shape[0][1] = Point(leftLineX2, int(image.rows));
        shape[0][2] = Point(rightLineX2, int(image.rows));
        shape[0][3] = Point(rightLineX1, int(0.65*image.rows));
        
        const Point* polygonPoints[1] = {shape[0]};
        int numberOfPoints[] = {4};
        int numberOfPolygons = 1;
        Scalar fillColor(0, 0, 255);
        fillPoly(image, polygonPoints, numberOfPoints, numberOfPolygons, fillColor);
        
        Scalar rightColor(0, 255, 0);
        Scalar leftColor(255, 0, 0);
        cv::line(image, shape[0][0], shape[0][1], leftColor, 10);
        cv::line(image, shape[0][3], shape[0][2], rightColor, 10);
        
    }
    return image;
}

Mat LaneDetector::detect_edges(Mat image){
    Mat greyScaledImage;
    cvtColor(image, greyScaledImage, COLOR_RGB2GRAY);
    
    Mat edgedOnlyImage;
    Canny(greyScaledImage, edgedOnlyImage, 50, 120);
    
    return edgedOnlyImage;
}
