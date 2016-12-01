#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(backgroundColor);
    // allocate color choices
    boidColorChoices.push_back(ofColor(0,255,255));
    boidColorChoices.push_back(ofColor(175,238,238));
    boidColorChoices.push_back(ofColor(207,244,244));
    boidColorChoices.push_back(ofColor(176,224,230));
    boidColorChoices.push_back(ofColor(153,255,255));
    
    //allocate particle color choices
    particleColorChoices.push_back(ofColor(50,50,255));
    particleColorChoices.push_back(ofColor(0,153,204));
    particleColorChoices.push_back(ofColor(51,153,255));
    particleColorChoices.push_back(ofColor(64,105,225));
    
    for (int i = 0; i < 6500; i++){
        boids.push_back(boid(ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()))));
        
    }
    for (int i = 3; i < 4000; i++){
        if(ofGetFrameNum() % 100== 0) {
            particles.push_back(particle(ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()))));
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    t = ofGetFrameNum() * TIME_SPEED;
    //delete if out of screen
    for (auto it = boids.begin(); it != boids.end(); it++){
        //check if out of screen
        auto position = it->pos;
        if( position.x > ofGetWidth() || position.y > ofGetHeight()){
            boids.erase(it);
            //spawn a new one
            boids.push_back(boid(ofVec2f(ofRandom(0, ofGetWidth()),0)));
            it--;
        }
        
        //if (ofGetFrameNum() % 25 == 0) {
            //boid1color.set(35, ofRandom(180, 255), 255);
            //boid1color.set(127,175,229);
           
            
        //}
        //if (ofGetFrameNum() % 40==0) {
            //boid2color.set(70, ofRandom(130, 150), 178);
            //boid2color.set(50, ofRandom(165, 185), 255);
            //boid2color.set(50,50,255);
        //}
    }
    
    //Create boid static - create new class if time
    for (auto it = particles.begin(); it != particles.end(); it++){
        //check if out of screen
        auto position = it->pos;
        if( position.x > ofGetWidth() || position.y > ofGetHeight()){
            particles.erase(it);
            //spawn a new one
            particles.push_back(particle(ofVec2f(ofRandom(0, ofGetWidth()),0)));
            it--;
           
        }
        
        
    }
    
    //    set boids on paths
    if(boidPaths.size() > 0){
        for (auto && b : boids){
            for (auto && path : boidPaths){
                if (b.seesPath(path)){
                    b.setPath(path);
                    
                }
            }
        }
        for (auto && b : boids){
            b.followPath();
            
        }
        
    }
    for (auto && b : boids){
        b.followWind(getField(b.pos));
    }
    
    
    for (auto && b : boids){
        b.move();
        
    }
    
    for (auto && p : particles){
        p.pos+=getField(p.pos)*5;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //    for(auto l : paths){
    //        ofSetColor(pathColor);
    //        l.draw();
    //        for ( auto p : l){
    //            ofDrawCircle(p, boid::pathRadius);
    //        }
    //    }
    ofSetColor(currentPathColor);
    currentPath.draw();

    for (auto b : boids ){
        ofSetColor(b.color);
        ofDrawCircle(b.pos, ofRandom(3,5));
        
    }
    for (auto p : particles){
        //ofSetColor(b.color);
        ofSetColor(p.color);
        ofDrawCircle(p.pos, ofRandom(3,4));
    }
    }
    
    


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='e'){
        //end the current path, add it to paths
        paths.push_back(currentPath);
        vector<ofVec2f> boidPath;
        for (auto && p : currentPath){
            boidPath.push_back(ofVec2f(p.x,p.y));
        }
        boidPaths.push_back(boidPath);
        
        currentPath.clear();
    }
    if (key=='c'){
        //clears paths
        currentPath.clear();
        paths.clear();
        boidPaths.clear();
    }
}

ofVec2f ofApp::getField(ofVec2f position){
    /// magic algorithm courtesy of the noiseField2dExample
    /// returns velocity vector at a 2D position
    float normx = ofNormalize(position.x, 0, ofGetWidth());
    float normy = ofNormalize(position.y, 0, ofGetHeight());
    float u = ofNoise(t + PHASE, normx * COMPLEXITY + PHASE, normy * COMPLEXITY + PHASE);
    float v = ofNoise(t - PHASE, normx * COMPLEXITY - PHASE, normy * COMPLEXITY + PHASE);
    
    return ofVec2f(u,v).rotate(45).getNormalized();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    currentPath.addVertex(ofPoint(x,y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
