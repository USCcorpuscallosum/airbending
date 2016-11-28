#include <stdio.h>
#include "ofMain.h"


class boid {
    
public:
    ofVec2f pos;
    ofVec2f vel;
    
    //boid properties
    const static int sightRadius = 100; //what the boid can see
    const static int terminalVelocity = 3; //boid max velocity
    constexpr static float m2 = 1; //weight
    constexpr static float m3 = .1; //weight
    const static int pathRadius = 30; //radius around point
    float size;
    
    
    
    
    //path seeking a2, m2
    
    ofVec2f a2;
    
    
    bool followingPath = false;
    bool seesPath(const vector<ofVec2f> & inputPath); //returns true if path within sight
    vector<ofVec2f>* path;
    vector<ofVec2f>::iterator target;
    
    void followPath();
    void setPath(vector<ofVec2f> & targetPath);
    
    
    //move with wind
    bool followingWind = true;
    ofVec2f a3;
    
    void followWind(ofVec2f wind); //sets a3 as wind
    
    void move(); //applies mN * aN to vel
    

    boid(ofVec2f initialPosition, ofVec2f startingVelocity = ofVec2f(0,0), float startingSize = 1);
    ofVec2f futurePos(); //helper function, returns pos + vel
    
    
    
};
