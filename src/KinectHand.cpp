//
//  KinectHand.cpp
//  airbending hands
//
//  Created by Leo Dastur on 12/1/16.
//  Copyright Leo Dastur 2016. This file is licensed Under the MIT License.
//

#include "KinectHand.hpp"


KinectHand::KinectHand() {
	bool success = setupKinect();
	if (!success) {
		std::cout << "ERROR: NO KINECT DETECTED!";
	}
	
	minDepth.set("Min Depth", 10, 0.1, 3000);
	maxDepth.set("Max Depth", 1100, 0.1, 3001);
	handLocation = ofVec2f(0, 0);
	
	refinedMap.allocate(512, 424, OF_IMAGE_COLOR);
	refinedMap.setColor(ofColor::white);
	
	handLocationContainer = ofRectangle(0, 0, 512, 424);
	handLocationContainer.setWidth(512);
	handLocationContainer.setHeight(424);
}

bool KinectHand::setupKinect() {
	if (kinect.getDeviceList().size()>0) {
		kinect.open(kinect.getDeviceList().begin()->serial);
		return true;
	}
	else {
		return false;
	}
}

void KinectHand::update() {
	
	kinect.update();
	if (kinect.isFrameNew()) {
		
		int xRollingSumAverage = 0, yRollingSumAverage = 0, counterSumAverage = 0;
		
		ofFloatPixels depthMap = kinect.getRawDepthPixels();
		ofImage & grayScaleMap = refinedMap;
		grayScaleMap.setColor(ofColor::blue);
		int x = 0, y = 0;
		for (auto&& depthPoint : depthMap) {
			float truncatedDepth = depthPoint;
			if (truncatedDepth > maxDepth || truncatedDepth < minDepth) {
				truncatedDepth = 16384;
			} else {
				xRollingSumAverage+=x;
				yRollingSumAverage+=y;
				counterSumAverage++;
			}
			int depth = ofMap(truncatedDepth, 0.0, 16384, 0, 255);
			
			ofColor color;
			color.set(depth, depth, depth);
			grayScaleMap.setColor(x, y, color );
			if (++x == 512) {
				y++;
				x=0;
			}
		}
		grayScaleMap.update();
		if (counterSumAverage > 20) {
			float xAvg = ((xRollingSumAverage/counterSumAverage)/512.0) * handLocationContainer.getWidth();
			float yAvg = ((yRollingSumAverage/counterSumAverage)/424.0) * handLocationContainer.getHeight();
			handLocation=ofVec2f(xAvg, yAvg);
		}
		
	}
}




