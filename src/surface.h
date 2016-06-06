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
    void keyPressed(int key);
    
    int vertsX; // how many vertices length wise?
    int vertsY; // ..
    
    vector<ofVec2f> verts;  // points in the mesh (vertsX * vertsY)
    
    // texture (still image or vid?)
    int textureType;
    ofTexture texture;
    ofVideoPlayer videoTexture;
    
    // temporary, until we implement automatic switching based
    // on which mode--video or still
    int textureWidth;
    int textureHeight;
    
    // corner pinning
    ofVec2f corners[4];
    bool active;        // is this particular surface active? (for pinning)
    int activeCorner;    // which corner is currently selected (1-4) TL, TR, BR, BL
    
};

#endif