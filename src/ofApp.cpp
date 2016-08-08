#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofSetBackgroundAuto(false);
    
    numRows = 3;
    numCols = 3;
    
    
    /*
    ptRefs = {6,7,8,
        5,4,3,
        0,1,2,
        
        2,5,8,
        7,4,1,
        0,3,6
        
    };
    
    */
    
  
    
    allCurves.push_back(new ofxCurve(0,0,
                                     50,0,
                                     50,0,
                                     100,0));
    
    allCurves.push_back(new ofxCurve(100,0,
                                     150,0,
                                     150,0,
                                     200,0));
    
    allCurves.push_back(new ofxCurve(200,0,
                                     300,0,
                                     300,100,
                                     200,100));
    
    allCurves.push_back(new ofxCurve(200,100,
                                     150,100,
                                     150,100,
                                     100,100));
    
    allCurves.push_back(new ofxCurve(100,100,
                                     50,100,
                                     50,100,
                                     0,100));
    
    allCurves.push_back(new ofxCurve(0,100,
                                     -100,100,
                                     -100,200,
                                     0,200));
    
    allCurves.push_back(new ofxCurve(0,200,
                                     50,200,
                                     50,200,
                                     100,200));
    
    allCurves.push_back(new ofxCurve(100,200,
                                     150,200,
                                     150,200,
                                     200,200));
    
    allCurves.push_back(new ofxCurve(200,200,
                                     400,200,
                                     200,400,
                                     200,200));

    allCurves.push_back(new ofxCurve(200,200,
                                     200,150,
                                     200,150,
                                     200,100));

    allCurves.push_back(new ofxCurve(200,100,
                                     200,50,
                                     200,50,
                                     200,0));

    allCurves.push_back(new ofxCurve(200,0,
                                     200,-100,
                                     100,-100,
                                     100,0));

    allCurves.push_back(new ofxCurve(100,0,
                                     100,50,
                                     100,50,
                                     100,100));

    allCurves.push_back(new ofxCurve(100,100,
                                     100,150,
                                     100,150,
                                     100,200));

    allCurves.push_back(new ofxCurve(100,200,
                                     100,300,
                                     0,300,
                                     0,200));
    
    allCurves.push_back(new ofxCurve(0,200,
                                     0,150,
                                     0,150,
                                     0,100));

     allCurves.push_back(new ofxCurve(0,100,
                                     0,50,
                                     0,50,
                                     0,0));

    allCurves.push_back(new ofxCurve(0,0,
                                     0,-200,
                                     -200,0,
                                     0,0));



    
    
    
    
    
    for(int j=0;j<numRows;j++){
    
        
        for(int i=0;i<numCols;i++){
            
            ofPoint pt;
            pt = ofPoint(i*300.0f,j*300.0f);
            basePts.push_back(pt);
        }
    }
   
    
    // starting over...
    for(int j=0;j<numRows;j++){
        
        bool direction = (j%2 == 0);
        // left true
        // right false
        int startNum, endNum;
        
       
        if(direction){
            for(int i=0;i<numCols-1;i++){
                
                ofxCurve * c = new ofxCurve();
                ofPoint anchorA = basePts.at(j*numCols+i);
                ofPoint anchorB = basePts.at(j*numCols+i+1);
                
                ofPoint ctrlA = (anchorB-anchorA)/4.0f + anchorA;
                ofPoint ctrlB = (anchorB-anchorA)*3.0f/4.0f + anchorA;
                
                c->set(anchorA,ctrlA,ctrlB,anchorB);
                
                curves.push_back(c);
                
                
            }
        } else {
            for(int i=numCols-1;i>0;i--){
                
                ofxCurve * c = new ofxCurve();
                ofPoint anchorA = basePts.at(j*numCols+i);
                ofPoint anchorB = basePts.at(j*numCols+i-1);
                
                ofPoint ctrlA = (anchorB-anchorA)/4.0f + anchorA;
                ofPoint ctrlB = (anchorB-anchorA)*3.0f/4.0f + anchorA;
                
                c->set(anchorA,ctrlA,ctrlB,anchorB);
                
                curves.push_back(c);

                
            }
        }
   
        if(j<numRows-1){
            ofxCurve * c = new ofxCurve();
            ofPoint anchorA;
            ofPoint anchorB;
            
            ofPoint prevPt;
            
            if(direction){
                anchorA = basePts.at(j*numCols+(numCols-1));
               anchorB = basePts.at((j+1)*numCols+(numCols-1));
                prevPt = basePts.at(j*numCols+(numCols-1)-1);
            } else {
                anchorA = basePts.at(j*numCols+(0));
                anchorB = basePts.at((j+1)*numCols+(0));
                prevPt = basePts.at(j*numCols+(0)+1);

            }
            
            ofPoint ctrlA = (anchorA-prevPt)/1.5f + anchorA;
            ofPoint ctrlB = (anchorA-prevPt)/1.5f + anchorB;

            
            c->set(anchorA,ctrlA,ctrlB,anchorB);
            
            curves.push_back(c);
        }
        
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0;i<curves.size();i++){
        ofxCurve * c = curves.at(i);
        ofSetColor(255);
        ofNoFill();
        c->update();
    }
    
    for(int i=0;i<allCurves.size();i++){
        ofxCurve * c = allCurves.at(i);
        ofSetColor(255);
        ofNoFill();
        c->update();
    }
    myPct += 0.03125f;
    while(myPct>=allCurves.size()){
        myPct -= allCurves.size();
    }
    
    int whichCurve = (int)myPct;
    
    
    
    myPt = allCurves.at(whichCurve)->plot(myPct-whichCurve);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(255,255,255,255);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2-100, 500.0f);
    
    ofRotateZ(45);
    
    ofRotateY((float)mouseX);
    ofRotateX((float)mouseY);
    
    
    for(int i=0;i<allCurves.size();i++){
        ofxCurve * c = allCurves.at(i);
        ofSetColor(0);
      
        ofNoFill();
        c->draw();
    }
    ofNoFill();
    
    ofDrawBox(myPt,30);
    
    
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
