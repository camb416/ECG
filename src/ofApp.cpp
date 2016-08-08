#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    numRows = 3;
    numCols = 3;
    
    ptRefs = {6,7,8,
        5,4,3,
        0,1,2,
        
        2,5,8,
        7,4,1,
        0,3,6
        
    };
    
    
    
    
    
    for(int j=0;j<numRows;j++){
    
        
        for(int i=0;i<numCols;i++){
            
            ofPoint pt;
            pt = ofPoint(i*100.0f,j*100.0f);
            basePts.push_back(pt);
        }
    }
    
    int numPts = 6;
    
    for(int i=0;i<numPts;i++){
        
        ofPoint * thisPoint = new ofPoint();
        thisPoint->x = cos((float)i/numPts*TWO_PI)*300;
        thisPoint->y = sin((float)i/numPts*TWO_PI)*300;
        linePts.push_back(thisPoint);
    }
    
    // first slope
    ofVec2f zero = ofPoint(1,0);
    
    float firstAngle = zero.angleRad(*linePts.at(1) - *linePts.at(0));
    
    angles.push_back(firstAngle);
    
    for(int i=1;i<linePts.size()-1;i++){
        
        ofPoint ptA = *linePts.at(i-1);
        ofPoint ptB = *linePts.at(i+1);
        
        float thisAngle = zero.angleRad(ptB - ptA);
        angles.push_back(thisAngle);
    }
    
    float lastAngle = zero.angleRad(*linePts.at(linePts.size()-2) - *linePts.at(linePts.size()-1));
    angles.push_back(lastAngle);
    

    
    
    
    
    // first point
    ofPoint * firstPt = new ofPoint();
    firstPt->set(*linePts.at(0));
    ctrlPts.push_back(firstPt);
                      
    for(int i=1;i<linePts.size();i++){
        
        ofPoint * ctrlPt = new ofPoint();
        
        ofPoint ptA = *linePts.at(i-1);
        ofPoint ptB = *linePts.at(i);
        
        ofPoint midPt = (ptA- ptB)/2.0f + ptB;
        
        ctrlPt->set(midPt);
        
        ctrlPts.push_back(ctrlPt);
        
        
    }
    
    // last point
    ofPoint * lastPt = new ofPoint();
    lastPt->set(*linePts.at(linePts.size()-1));
    ctrlPts.push_back(lastPt);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    /*
    ofFill();
    ofSetColor(255);
    for(int i=0;i<basePts.size();i++){
        ofDrawEllipse(basePts.at(i),5,5);
    }
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    for(int i=1;i<ptRefs.size();i++){
        ofDrawLine(basePts.at(ptRefs.at(i-1)), basePts.at(ptRefs.at(i)));
    }
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    for(int i=0;i<ctrlPts.size();i++){
        ofDrawLine(ctrlPts.at(i)->x-3,ctrlPts.at(i)->y-3,
                   ctrlPts.at(i)->x+3,ctrlPts.at(i)->y+3);
        ofDrawLine(ctrlPts.at(i)->x+3,ctrlPts.at(i)->y-3,
                   ctrlPts.at(i)->x-3,ctrlPts.at(i)->y+3);
        ofDrawBitmapString(ofToString(i),*ctrlPts.at(i));
        
    }
    
    ofSetColor(0,255,0);
    for(int i=1;i<linePts.size()-1;i++){
        ofDrawCurve(ctrlPts.at(i)->x,ctrlPts.at(i)->y,
                    linePts.at(i-1)->x,linePts.at(i-1)->y,
                     linePts.at(i)->x,linePts.at(i)->y,
                    ctrlPts.at(i)->x,ctrlPts.at(i)->y);
    }
    */
    ofSetColor(255,0,0);
    ofNoFill();
    for(int i=1;i<linePts.size();i++){
                ofDrawLine(*linePts.at(i-1),*linePts.at(i));
    }
    
    
    ofSetColor(0,0,255);
    ofNoFill();
    for(int i=0;i<linePts.size();i++){
        ofPoint left = ofPoint(linePts.at(i)->x - cos(angles.at(i))*10, linePts.at(i)->y - sin(angles.at(i))*10);
        ofPoint right = ofPoint(linePts.at(i)->x - cos(angles.at(i)+PI)*10, linePts.at(i)->y - sin(angles.at(i)+PI)*10);
        ofDrawLine(left,right);
    }
    
    ofSetColor(0,255,255);
    ofNoFill();
    for(int i=1;i<linePts.size();i++){
        ofPoint left = ofPoint(linePts.at(i-1)->x - cos(angles.at(i-1)+PI)*500, linePts.at(i-1)->y - sin(angles.at(i-1)+PI)*500);
        ofPoint right = ofPoint(linePts.at(i)->x - cos(angles.at(i))*500, linePts.at(i)->y - sin(angles.at(i))*500);
        
     
        ofDrawEllipse(left, 10,10);
       ofDrawEllipse(right, 10,10);
      
        
        
        ofDrawCurve(left.x,left.y,
                    linePts.at(i-1)->x,linePts.at(i-1)->y,
                    linePts.at(i)->x,linePts.at(i)->y,
                    right.x,right.y);
    }
    
    
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
