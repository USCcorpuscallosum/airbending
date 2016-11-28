#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(backgroundColor);

    
    for (int i = 0; i < 4000; i++){
        boids.push_back(boid(ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()))));
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
            boids.push_back(boid(ofVec2f(0,ofRandom(0,ofGetHeight()))));
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
    ofSetColor(ofColor::green);
    for (auto b : boids){
        ofDrawCircle(b.pos, ofRandom(0,1));
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
    
    return ofVec2f(u,v).rotate(-45).getNormalized();
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
