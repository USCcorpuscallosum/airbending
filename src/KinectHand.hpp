//
//  KinectHand.hpp
//  airbending hands
//
//  Created by Leo Dastur on 12/1/16.
//  Copyright Leo Dastur 2016. This file is licensed Under the MIT License.
//

#pragma once
#include "ofMain.h"
#include "ofxKinectV2.h"


class KinectHand {
	ofxKinectV2 kinect;
	
	bool setupKinect();
	
	
public:
	KinectHand();
	void update(); // Call every frame (just put in ofApp::update )
	ofImage refinedMap;
	ofVec2f handLocation;
	ofRectangle handLocationContainer; // Adjust Height/Width to for larger coverage areas
	ofParameter<float> minDepth;
	ofParameter<float> maxDepth;
	
	
};


