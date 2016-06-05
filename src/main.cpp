/*
    ofRPiEasyMap is a joint venture between Shobun Baile and Grayson Earle
*/

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    // this should be changed to screen res connected to RPi
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
