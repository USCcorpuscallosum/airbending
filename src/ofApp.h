#pragma once

#include "ofMain.h"
#include "boid.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector<ofPolyline> paths;
        ofPolyline currentPath;
        vector<vector<ofVec2f>> boidPaths;
    
    vector<boid> boids;
    //noise
    ofVec2f getField(ofVec2f position);
    float COMPLEXITY = 6;
    float TIME_SPEED = .02;
    float PHASE = TWO_PI;
    float WIND_SPEED = 80;
    float t;
    //colors
    ofColor pathColor = ofColor::white;
    ofColor currentPathColor = ofColor::red;
    ofColor backgroundColor = ofColor::black;
    
};
