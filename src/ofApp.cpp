/*
 ofRPiEasyMap is a joint venture between Shobun Baile and Grayson Earle
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    surfaces.push_back(Surface());
        
    ofBackground(0,0,0);
    
    ofSetVerticalSync(false);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // update each surface
    for (int i=0; i<surfaces.size(); i++) {
        
        surfaces[i].update();
        surfaces[i].updateVectors();
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // draw each surface
    for (int i=0; i<surfaces.size(); i++) {
        
        surfaces[i].draw();

    }
    
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), ofGetWidth() * .05, ofGetHeight() * .05);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // pass any key presses to active surface
    for (int i=0; i<surfaces.size(); i++) {
        
        if(surfaces[i].active)
            surfaces[i].keyPressed(key);
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
