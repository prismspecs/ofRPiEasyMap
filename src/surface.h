/*
 ofRPiEasyMap is a joint venture between Shobun Baile and Grayson Earle
*/

#ifndef surface_h
#define surface_h

#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework

class Surface {
    
public:
    
    Surface();
    
    void updateVectors();
    void update();
    void draw();
    int getVert(int x, int y);
    
    int vertsX; // how many vertices length wise?
    int vertsY; // ..
    int width;
    int height;
    ofVec2f corners[4];
    
    vector<ofVec2f> verts;
    ofTexture texture;
    ofVideoPlayer videoTexture;
    
    // temporary
    int textureWidth;
    int textureHeight;
    
};

#endif