//
//  surface.cpp
//  testing
//
//  Created by Jargon Jargon on 6/4/16.
//
//

#include "surface.h"

Surface::Surface() {
    
    // arbitrary starting properties
    vertsX = 16;
    vertsY = 16;
    width = 400;
    height = 400;
    
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
    
    // load in image
    ofLoadImage(texture, "checker.jpg");
    
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
    
    // diagnostics... just corner pin the bottom right to the mouse position for now
    corners[2].x = ofGetMouseX();
    corners[2].y = ofGetMouseY();
    
}

void Surface::draw() {
    
    // draw four corners
    ofSetColor(255);
    ofFill();
    
    for(int i = 0; i < 4; i++)
        ofDrawCircle(corners[i].x, corners[i].y, 5);
    
    // draw vec array
    for(int y = 0; y < vertsY; y++) {
        for(int x = 0; x < vertsX; x++) {
            
            // diagnostics... draw red verts
            ofSetColor(255,0,0);
            ofFill();
            //ofDrawCircle(verts[getVert(x, y)].x, verts[getVert(x, y)].y, 2);
            
            // set color to full white for texture to render un-tinted
            ofSetColor(255);
            
            
            // new method...
            
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            
            // top left
            int whichVert = getVert(x, y);
            float mappedX = float(x) / float(vertsX) * texture.getWidth();
            float mappedY = float(y) / float(vertsY) * texture.getHeight();
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            
            
            // top right
            whichVert = getVert(x + 1, y);
            mappedX = float(x+1) / float(vertsX) * texture.getWidth();
            mappedY = float(y) / float(vertsY) * texture.getHeight();
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            
            // bottom right
            whichVert = getVert(x + 1, y + 1);
            mappedX = float(x+1) / float(vertsX) * texture.getWidth();
            mappedY = float(y+1) / float(vertsY) * texture.getHeight();
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            
            // bottom right again
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            
            // bottom left
            whichVert = getVert(x, y + 1);
            mappedX = float(x) / float(vertsX) * texture.getWidth();
            mappedY = float(y+1) / float(vertsY) * texture.getHeight();
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            
            // top left again
            whichVert = getVert(x, y);
            mappedX = float(x) / float(vertsX) * texture.getWidth();
            mappedY = float(y) / float(vertsY) * texture.getHeight();
            
            mesh.addVertex(ofPoint(verts[whichVert].x, verts[whichVert].y));
            mesh.addTexCoord(texture.getCoordFromPoint(mappedX, mappedY));
            
            texture.bind();
            mesh.draw();
            texture.unbind();
            
            
            
            // old method, doesn't work on RPi
//            texture.bind();
//            glBegin(GL_QUADS);
//            
//            // top left
//            int whichVert = getVert(x, y);
//            float mappedX = float(x) / float(vertsX) * texture.getWidth();
//            float mappedY = float(y) / float(vertsY) * texture.getHeight();
//            
//            glTexCoord2f(mappedX, mappedY);
//            glVertex2f(verts[whichVert].x, verts[whichVert].y);
//            
//            // top right
//            whichVert = getVert(x + 1, y);
//            mappedX = float(x+1) / float(vertsX) * texture.getWidth();
//            mappedY = float(y) / float(vertsY) * texture.getHeight();
//            
//            
//            glTexCoord2f(mappedX, mappedY);
//            glVertex2f(verts[whichVert].x, verts[whichVert].y);
//            
//            // bottom right
//            whichVert = getVert(x + 1, y + 1);
//            mappedX = float(x+1) / float(vertsX) * texture.getWidth();
//            mappedY = float(y+1) / float(vertsY) * texture.getHeight();
//            
//            glTexCoord2f(mappedX, mappedY);
//            glVertex2f(verts[whichVert].x, verts[whichVert].y);
//            
//            // bottom left
//            whichVert = getVert(x, y + 1);
//            mappedX = float(x) / float(vertsX) * texture.getWidth();
//            mappedY = float(y+1) / float(vertsY) * texture.getHeight();
//            
//            glTexCoord2f(mappedX, mappedY);
//            glVertex2f(verts[whichVert].x, verts[whichVert].y);
//            
//            glEnd();
//            ofEndShape();
//            texture.unbind();

        }
    }
}

int Surface::getVert(int x, int y) {
    return x + (y * (vertsX+1));
}