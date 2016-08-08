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
                                     0,0,
                                     100,0,
                                     100,0));
    
    allCurves.push_back(new ofxCurve(100,0,
                                     100,0,
                                     200,0,
                                     200,0));
    
    allCurves.push_back(new ofxCurve(200,0,
                                     300,0,
                                     300,100,
                                     200,100));
    
    allCurves.push_back(new ofxCurve(200,100,
                                     200,100,
                                     100,100,
                                     100,100));
    
    allCurves.push_back(new ofxCurve(100,100,
                                     100,100,
                                     0,100,
                                     0,100));
    
    allCurves.push_back(new ofxCurve(0,100,
                                     -100,100,
                                     -100,200,
                                     0,200));
    
    allCurves.push_back(new ofxCurve(0,200,
                                     0,200,
                                     100,200,
                                     100,200));
    
    allCurves.push_back(new ofxCurve(100,200,
                                     100,200,
                                     200,200,
                                     200,200));
    
    allCurves.push_back(new ofxCurve(200,200,
                                     400,200,
                                     200,400,
                                     200,200));

    allCurves.push_back(new ofxCurve(200,200,
                                     200,200,
                                     200,100,
                                     200,100));

    allCurves.push_back(new ofxCurve(200,100,
                                     200,100,
                                     200,0,
                                     200,0));

    allCurves.push_back(new ofxCurve(200,0,
                                     200,-100,
                                     100,-100,
                                     100,0));

    allCurves.push_back(new ofxCurve(100,0,
                                     100,0,
                                     100,100,
                                     100,100));

    allCurves.push_back(new ofxCurve(100,100,
                                     100,100,
                                     100,200,
                                     100,200));

    allCurves.push_back(new ofxCurve(100,200,
                                     100,300,
                                     0,300,
                                     0,200));
    
    allCurves.push_back(new ofxCurve(0,200,
                                     0,200,
                                     0,100,
                                     0,100));

     allCurves.push_back(new ofxCurve(0,100,
                                     0,100,
                                     0,0,
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
    /*
    int numPts = 6;
    
//    for(int i=0;i<numPts;i++){
//        
//        ofPoint * thisPoint = new ofPoint();
//        thisPoint->x = cos((float)i/numPts*TWO_PI)*3000;
//        thisPoint->y = sin((float)i/numPts*TWO_PI)*3000;
//        linePts.push_back(thisPoint);
//    }
    for(int i=0;i<ptRefs.size();i++){
        linePts.push_back(&basePts.at(ptRefs.at(i)));
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
    */
    
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2-100, 500.0f);
    
    ofRotateZ(45);
    
    ofRotateY((float)mouseX);
    ofRotateX((float)mouseY);
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
    /*
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
        ofPoint left = ofPoint(linePts.at(i-1)->x - cos(angles.at(i-1)+PI)*200, linePts.at(i-1)->y - sin(angles.at(i-1)+PI)*200);
        ofPoint right = ofPoint(linePts.at(i)->x - cos(angles.at(i))*200, linePts.at(i)->y - sin(angles.at(i))*200);
        
     
        ofDrawEllipse(left, 10,10);
       ofDrawEllipse(right, 10,10);
      
        
        
        ofDrawBezier(linePts.at(i-1)->x,linePts.at(i-1)->y,
                     left.x,left.y,
                     right.x,right.y,
                    linePts.at(i)->x,linePts.at(i)->y
                    );
    }
    */
    /*
    for(int i=0;i<curves.size();i++){
        ofxCurve * c = curves.at(i);
        ofSetColor(0);
        ofNoFill();
        c->draw();
        ofDrawBitmapString(ofToString(i),c->start);
    }
    */
    
    for(int i=0;i<allCurves.size();i++){
        ofxCurve * c = allCurves.at(i);
        ofSetColor(0);
        //ofSetLineWidth(15.0f);
      
        ofNoFill();
        c->draw();
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
