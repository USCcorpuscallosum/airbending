
#include "boid.hpp"
#include <time.h>


boid::boid(ofVec2f initialPosition, ofVec2f startVelocity, float startingSize){
    vector<ofColor> boidColorChoices;
    boidColorChoices.push_back(ofColor(0,255,255));
    boidColorChoices.push_back(ofColor(175,238,238));
    boidColorChoices.push_back(ofColor(207,244,244));
    boidColorChoices.push_back(ofColor(176,224,230));
    boidColorChoices.push_back(ofColor(153,255,255));
    pos = initialPosition;
    vel = startVelocity;
    size = startingSize;
    color =  boidColorChoices[rand() % boidColorChoices.size()];
    
}


ofVec2f boid::futurePos(){
    return pos + vel;
}

void boid::followPath(){
    
    if (followingPath){
        if (target == path->end()){
            followingPath = false;
            return;
        }
        while(target->distance(pos) < sightRadius){
            target++;
        }
        if (target == path->end()){
            followingPath = false;
            return;
        }
        if (target->distance(pos) > pathRadius){
            a2 = (*target - futurePos()).getNormalized();
        } else {
            a2 = ofVec2f(0,0);
        }
        
    }
    
}
void boid::setPath(vector<ofVec2f> & targetPath){
    followingPath = true;
    path = &targetPath;
    
    
    target = path->begin();
    
    while (target != path->end()){
        if (pos.distance(*target) < sightRadius){
            return;
        } else {
            target++;
        }
    }
    
}
void boid::move(){
    if(followingPath){
        vel += m2 * a2;
    }
    if (followingWind){
        //srand(time(NULL));
        vel += m3 * a3;
    }
    
    //if (vel.length() > terminalVelocity){
        //vel = terminalVelocity * vel.getNormalized();
    //}
    pos += vel;
}
bool boid::seesPath(const vector<ofVec2f> & inputPath){
    for (auto && p : inputPath){
        if (pos.distance(p) < sightRadius){
            return true;
        }
    }
    return false;
}

void boid::followWind(ofVec2f wind){
    a3 = wind;
}
