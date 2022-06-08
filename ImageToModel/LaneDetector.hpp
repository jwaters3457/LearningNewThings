//
//  LaneDetector.hpp
//  ImageToModel
//
//  Created by James Macbook on 6/8/22.
//
#ifndef LaneDetector_hpp
#define LaneDetector_hpp

#include <stdio.h>

#endif /* LaneDetector2_hpp */

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class LaneDetector {
    
public:
    Mat detect_lane(Mat image);
    
private:
    Mat filter_only_yellow_white(Mat image);
    
    Mat crop_region_of_interest(Mat image);
    
    Mat draw_lines(Mat image, vector<Vec4i> lines);
    
    Mat detect_edges(Mat image);
};
