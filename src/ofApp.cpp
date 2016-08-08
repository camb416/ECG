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
    
    for(int i=0;i<ptRefs.size();i++){
        linePts.push_back(&basePts.at(ptRefs.at(i)));
    }
    for(int i=1;i<linePts.size()-1;i++){
        
        ofPoint * ctrlPt = new ofPoint();
        
        ofPoint ptA = *linePts.at(i-1);
        ofPoint ptB = *linePts.at(i);
        
        ofPoint midPt = (ptA- ptB)/2.0f + ptB;
        
        ctrlPt->set(midPt);
        
        ctrlPts.push_back(ctrlPt);
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    
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
        ofDrawLine(ctrlPts.at(i)->x-10,ctrlPts.at(i)->y-10,
                   ctrlPts.at(i)->x+10,ctrlPts.at(i)->y+10);
        ofDrawLine(ctrlPts.at(i)->x+10,ctrlPts.at(i)->y-10,
                   ctrlPts.at(i)->x-10,ctrlPts.at(i)->y+10);
        
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
