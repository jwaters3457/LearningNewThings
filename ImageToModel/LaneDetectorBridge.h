#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface LaneDetectorBridge : NSObject

- (UIImage *) detectLaneIn: (UIImage *) image;

@end
