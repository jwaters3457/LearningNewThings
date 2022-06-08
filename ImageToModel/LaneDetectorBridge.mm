//
//  LaneDetectorBridge.m
//  ImageToModel
//
//  Created by James Macbook on 6/8/22.
//

#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>
#import <Foundation/Foundation.h>
#import "LaneDetectorBridge.h"
#import "LaneDetector.hpp"

@implementation LaneDetectorBridge

- (UIImage *) detectLaneIn: (UIImage *) image {
    cv::Mat opencvImage;
    UIImageToMat(image, opencvImage, true);
    
    cv::Mat convertedColorSpaceImage;
    cv::cvtColor(opencvImage, convertedColorSpaceImage, COLOR_RGBA2RGB);
    
    LaneDetector laneDetector;
    cv::Mat imageWithLaneDetected = laneDetector.detect_lane(convertedColorSpaceImage);
    
    return MatToUIImage(imageWithLaneDetected);
}

@end
