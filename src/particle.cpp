#include "particle.hpp"
particle::particle(ofVec2f startpos){
    pos = startpos;
    color =  ofRandom(vector<ofColor> particleColorChoices);
    
}
