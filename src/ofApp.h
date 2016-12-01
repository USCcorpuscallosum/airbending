#pragma once

#include "ofMain.h"
#include "boid.hpp"
#include "particle.hpp"
#include "KinectHand.hpp"

class ofApp : public ofBaseApp{
    
public:
    int scalarfield = 5;
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
    vector<ofVec2f> boidPath;
    
    vector<boid> boids;
    vector<particle> particles;
    vector<boid> boidfollowing;
    //noise
    ofVec2f getField(ofVec2f position);
    float COMPLEXITY = 6;
    float TIME_SPEED_ONE = 0.005;
    float TIME_SPEED_TWO = 0.02;
    float PHASE = TWO_PI;
    float WIND_SPEED = 80;
    float t;
    //colors
    ofColor pathColor = ofColor::white;
    ofColor currentPathColor = ofColor::red;
    ofColor backgroundColor = ofColor::black;
    vector<ofColor> boidColorChoices;
    vector<ofColor> particleColorChoices;

	KinectHand kHand;
    ofVec2f handLocation;
	
    bool kinectDebug = false;
    
    
    
};
