#pragma once

#include "ofMain.h"
#include "ofxCurve.h"
#include "ofxCsv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxCurve * curve;
    float t;
    
    vector<ofxCurve*> curves;
    
    ofxCsv csv;
    
    // ofxVectorGraphics output;
    bool capture;
    
    // GUI stuff
    
    ofxFloatSlider radius;
    ofxColorSlider colorA;
    
     ofxColorSlider colorB;
     ofxColorSlider colorC;
     ofxColorSlider colorD;
    
    ofxFloatSlider rotSpeed;
    
    ofxPanel gui;
    bool bHide;
    
//    bool bBackground;
    ofxToggle bBackground;

    
    
    
};
