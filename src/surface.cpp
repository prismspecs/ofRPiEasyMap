/*
 ofRPiEasyMap is a joint venture between Shobun Baile and Grayson Earle
 */

#include "surface.h"

Surface::Surface() {
    
    // arbitrary starting properties
    // VERTS IS VERY IMPORTANT for the RPi, I set to
    // 6 and my FPS shot up to 60fps
    vertsX = 12;
    vertsY = 12;
    textureType = 1;    //vid
    active = true;
    activeCorner = 2;   // bottom right
    
    // corners for pinning
    // top left
    corners[0].x = 10;
    corners[0].y = 10;
    // top right
    corners[1].x = 900;
    corners[1].y = 10;
    // bottom right
    corners[2].x = 900;
    corners[2].y = 800;
    // bottom left
    corners[3].x = 10;
    corners[3].y = 700;
    
    switch(textureType) {
        case 0:
            // load in image
            ofLoadImage(texture, "checker.jpg");
            textureWidth = texture.getWidth();
            textureHeight = texture.getHeight();
            break;
        case 1:
            // load in video
            videoTexture.load("hd.mov");
            videoTexture.setLoopState(OF_LOOP_NORMAL);
            videoTexture.play();
            textureWidth = videoTexture.getWidth();
            textureHeight = videoTexture.getHeight();
            break;
    }
    
    
    // set texture width and height
    // just manual for now, to switch between
    // video and still image for testing
    //textureWidth = 640;
    //textureHeight = 360;
    
    // determine how to divide quad into mesh
    updateVectors();
    
}

void Surface::updateVectors() {
    
    // erase any existing vectors
    verts.clear();
    
    // set up array of vectors
    for(int yy = 0; yy <= vertsY; yy++) {
        for(int xx = 0; xx <= vertsX; xx++) {
            
            // the idea is to generate a linear interpolation of x
            // coordinates along the top and bottom, just even divisions
            // and then interpolate between those based on Y position
            
            // where does this vert X fall on the top of the quad?
            float xPosTop = ofMap(xx, 0, vertsX, corners[0].x, corners[1].x);
            // and the bottom?
            float xPosBot = ofMap(xx, 0, vertsX, corners[3].x, corners[2].x);
            // interpolate based on this verts Y location
            float xLerp = ofLerp(xPosTop, xPosBot, float(yy)/float(vertsY));
            
            // same for Y
            float yPosLeft = ofMap(yy, 0, vertsY, corners[0].y, corners[3].y);
            float yPosRight = ofMap(yy, 0, vertsY, corners[1].y, corners[2].y);
            float yLerp = ofLerp(yPosLeft, yPosRight, float(xx)/float(vertsX));
            
            verts.push_back(ofVec2f(xLerp, yLerp));
            
        }
    }
}

void Surface::update() {
    
    // update video if that's the texture type
    if(textureType == 1)
        videoTexture.update();
    
    // need to improve this mucho
    if(active) {
        corners[activeCorner].x = ofGetMouseX();
        corners[activeCorner].y = ofGetMouseY();
    }
    
}

void Surface::draw() {
    
    // draw four corners
    ofSetColor(255);
    ofFill();
    
    // if this is currently being pinned, draw corners
    if(active)
        for(int i = 0; i < 4; i++)
            ofDrawCircle(corners[i].x, corners[i].y, 5);
    
    // draw vec array
    for(int y = 0; y < vertsY; y++) {
        for(int x = 0; x < vertsX; x++) {
            
            
            // diagnostics... draw red verts
            //ofSetColor(255,0,0);
            //ofFill();
            //ofDrawCircle(verts[getVert(x, y)].x, verts[getVert(x, y)].y, 2);
            
            // set color to full white for texture to render un-tinted
            ofSetColor(255);
            
            
            // new method...
            
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            
            // top left
            int whichVert = getVert(x, y);
            float mappedX = float(x) / float(vertsX) * textureWidth;
            float mappedY = float(y) / float(vertsY) * textureHeight;
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            if(textureType == 0)
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            if(textureType == 1)
            mesh.addTexCoord(videoTexture.getTexture().getCoordFromPoint(mappedX, mappedY));
            
            // top right
            whichVert = getVert(x + 1, y);
            mappedX = float(x+1) / float(vertsX) * textureWidth;
            mappedY = float(y) / float(vertsY) * textureHeight;
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            if(textureType == 0)
                mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            if(textureType == 1)
                mesh.addTexCoord(videoTexture.getTexture().getCoordFromPoint(mappedX, mappedY));
            
            // bottom right
            whichVert = getVert(x + 1, y + 1);
            mappedX = float(x+1) / float(vertsX) * textureWidth;
            mappedY = float(y+1) / float(vertsY) * textureHeight;
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            if(textureType == 0)
                mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            if(textureType == 1)
                mesh.addTexCoord(videoTexture.getTexture().getCoordFromPoint(mappedX, mappedY));
            
            // bottom right again
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            if(textureType == 0)
                mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            if(textureType == 1)
                mesh.addTexCoord(videoTexture.getTexture().getCoordFromPoint(mappedX, mappedY));
            
            // bottom left
            whichVert = getVert(x, y + 1);
            mappedX = float(x) / float(vertsX) * textureWidth;
            mappedY = float(y+1) / float(vertsY) * textureHeight;
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            if(textureType == 0)
                mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            if(textureType == 1)
                mesh.addTexCoord(videoTexture.getTexture().getCoordFromPoint(mappedX, mappedY));
            
            // top left again
            whichVert = getVert(x, y);
            mappedX = float(x) / float(vertsX) * textureWidth;
            mappedY = float(y) / float(vertsY) * textureHeight;
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            if(textureType == 0)
                mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            if(textureType == 1)
                mesh.addTexCoord(videoTexture.getTexture().getCoordFromPoint(mappedX, mappedY));
            
            
            // bind texture depending on which type we're using
            switch(textureType) {
                case 0:
                    // still image texture
                    texture.bind();
                    mesh.draw();
                    texture.unbind();
                    break;
                case 1:
                    // video texture
                    videoTexture.getTexture().bind();
                    mesh.draw();
                    videoTexture.getTexture().unbind();
                    break;
            }
            
        }
    }
}

int Surface::getVert(int x, int y) {
    return x + (y * (vertsX+1));
}

void Surface::keyPressed(int key) {
    ofLog() << "the number is " << key;
    
    if(key == '1')
        activeCorner = 0;
    if(key == '2')
        activeCorner = 1;
    if(key == '3')
        activeCorner = 2;
    if(key == '4')
        activeCorner = 3;
    // for now, just stop pinning all corners w/ #5 on keyboard
    if(key == '5')
        active = !active;
}