#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(backgroundColor);
	ofSetFrameRate(30);

    for (int i = 0; i < 7000; i++){
        boids.push_back(boid(ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()))));
        
    }
    for (int i = 0; i < 2000; i++){
        particles.push_back(particle(ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()))));
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(std::to_string(ofGetFrameRate()));
    //delete if out of screen
    for (auto it = boids.begin(); it != boids.end(); it++){
        t = ofGetFrameNum() * TIME_SPEED_ONE;
        //check if out of screen
        auto position = it->pos;
        if( position.x > ofGetWidth() || position.y > ofGetHeight()){
            boids.erase(it);
            //spawn a new one
            boids.push_back(boid(ofVec2f(ofRandom(0, ofGetWidth()),0)));
            it--;
        }
		
    }
    
    //Create boid static - create new class if time
    for (auto it = particles.begin(); it != particles.end(); it++){
        t = ofGetFrameNum() * TIME_SPEED_TWO;
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
    for (auto && b : boids){
        if (b.seesPath(boidPath)){
            b.setPath(boidPath);
        }
    }
    for (auto && b : boids){
        b.followPath();
    }
        

    for (auto && b : boids){
        b.followWind(getField(b.pos));
    }
    
    
    for (auto && b : boids){
        b.move();
        
    }
    
    for (auto && p : particles){
        p.pos+=getField(p.pos)*scalarfield;
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
        ofDrawCircle(b.pos, rand() % 5 + 1);
        
    }
    for (auto p : particles){
        //ofSetColor(b.color);
        ofSetColor(p.color);
        ofDrawCircle(p.pos, rand() % 4 +1);
    }
    }
    
    


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='e'){
        //end the current path, add it to paths
        paths.push_back(currentPath);
        vector<ofVec2f> path;
        for (auto && p : currentPath){
            path.push_back(ofVec2f(p.x,p.y));
        }
        boidPath = path;
        
        currentPath.clear();
    }
    if (key=='c'){
        //clears paths
        currentPath.clear();
        paths.clear();
        boidPath.clear();
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
