#include "particle.hpp"
#include <time.h>
particle::particle(ofVec2f startpos){
    
    vector<ofColor> particleColorChoices;
    //allocate particle color choices
    particleColorChoices.push_back(ofColor(50,50,255));
    particleColorChoices.push_back(ofColor(0,153,204));
    particleColorChoices.push_back(ofColor(51,153,255));
    particleColorChoices.push_back(ofColor(64,105,225));
    
    pos = startpos;
    color = particleColorChoices[rand() % particleColorChoices.size()];
    
}
