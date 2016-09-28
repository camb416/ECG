#include "ofApp.h"

int drawFaces;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    // gui stuff
    gui.setup("my panel"); // most of the time you don't need a name
    gui.add(radius.setup("radius", 10, 1, 200));
    gui.add(zPos.setup("z pos",600,0,1000));
    gui.add(twists.setup("twists",8,0,32));
    
    gui.add(res.setup("res",6,3,32));
    gui.add(numSections.setup("sections",8,4,64));
    
    gui.add(colorA.setup("colorA", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(colorB.setup("colorB", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(colorC.setup("colorC", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(colorD.setup("colorD", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    
    gui.add(rotSpeed.setup("rot. speed",0.0f,-5.0f,5.0f));
    
    gui.add(bBackground.setup("redraw background", true));
    gui.add(backgroundColor.setup("bg color",ofColor(0,0,0),ofColor(0,0),ofColor(255,255)));
    
    gui.loadFromFile("settings.xml");
    
    
    
    // Load a CSV File.
    if(csv.load("curves.csv")) {
        //csv.trim(); // Trim leading/trailing whitespace from non-quoted fields.
        
        // Like with C++ vectors, the index operator is a quick way to grab row
        // & col data, however this will cause a crash if the row or col doesn't
        // exist, ie. the file didn't load.
        ofLog() << "Print out a specific CSV value";
        ofLog() << csv[0][1];
        // also you can write...
        ofLog() << csv[0].at(1);
        // or you can get the row itself...
        ofxCsvRow row = csv[0];
        ofLog() << row.getString(1);
    }
    
    // A safer method is to use the getters which will do a check on the
    // given row & col indices but will be slightly slower.
    ofLog() << "Print out the first value";
    ofLog() << csv.getRow(0).getString(0);
    
    // Print the table to the console.
    ofLog() << "Print the table";
    //csv.print(); // Uses default separator ",".
    // ... or do it manually
    for(auto row : csv) {
        ofLog() << ofJoinString(row, "|");
    }
    
    
    ofVec3f a,b,c,d;
    for(int i=0;i<csv.getNumRows();i+=5){
        ofLog() << "first: " << ofJoinString(csv.getRow(i),"<<>>");
        ofLog() << "2nd: " << ofJoinString(csv.getRow(i+1),"<<>>");
        ofLog() << "3rd: " << ofJoinString(csv.getRow(i+2),"<<>>");
        ofLog() << "4th: " << ofJoinString(csv.getRow(i+3),"<<>>");
        ofLog() << "5th: " << ofJoinString(csv.getRow(i+4),"///////////");
        a.set(csv.getRow(i).getFloat(0),
              csv.getRow(i).getFloat(1),
              csv.getRow(i).getFloat(2)
              );
        
        b.set(csv.getRow(i+1).getFloat(0),
              csv.getRow(i+1).getFloat(1),
              csv.getRow(i+1).getFloat(2)
              );
        c.set(csv.getRow(i+2).getFloat(0),
              csv.getRow(i+2).getFloat(1),
              csv.getRow(i+2).getFloat(2)
              );
        d.set(csv.getRow(i+3).getFloat(0),
              csv.getRow(i+3).getFloat(1),
              csv.getRow(i+3).getFloat(2)
              );
        curves.push_back(new ofxCurve(a,b,c,d));
        
    }
    
    
    
    
    
    bHide = false;
    
    
    capture = false;
    
    drawFaces = 0;
    
    // ofVec3f a,b,c,d;
    
    //    a.set(0,0,0);
    //    b.set(200,0,0);
    //    c.set(0,200,200);
    //    d.set(0,200,0);
    //
    //    curve = new ofxCurve(a,b,c,d);
    
    zPos = 0;
    
    t = 0.0f;
    ofSetBackgroundAuto(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0;i<curves.size();i++){
        curves.at(i)->update();
    }
    t += 0.003f;
    while(t>1.0f) t -= 1.0f;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // if(ofGetFrameNum()%30==0) ofLog() << curves.size();
    
    ofMesh mesh;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
//    int numSections = 8;
//    int res = 6;
    
    //ofColor colorA,colorB,colorC;
    //colorA = colorB = colorC = ofColor(255,0,255);
    
    
    ////////////////////////////////////////////////////////////////////////////////
    
    for(int i=0;i<curves.size();i++){
        
        ofxCurve * c = curves.at(i);
        
        for(int j=0;j<numSections;j++){
            
            
            
            for(int k=0;k<res;k++){
                // do something here.
                ofVec3f p =c->plot3d((float)j/(float)numSections);
                ofVec3f d = c->getDirection((float)j/(float)numSections);
                ofVec3f a = ofVec3f(0,0,1.0f);
                ofQuaternion q;
                q.makeRotate(a,d);
                ofVec3f myPoint = ofVec3f(cos((float)k/(float)res*TWO_PI)*radius,sin((float)k/(float)res*TWO_PI)*radius,0);
                mesh.addVertex(p+myPoint*q);
                ofColor thisColor = colorB;
                if(k%2==0) thisColor = colorA;
                if(j==0 && i==0) thisColor = colorC;
                mesh.addColor(thisColor);
                
            }
            /*
             for(int k=0;k<res;k++){
             // do something here.
             ofVec3f p =c->plot3d((float)j/(float)numSections);
             ofVec3f d = c->getDirection((float)j/(float)numSections);
             ofVec3f a = ofVec3f(0,0,1.0f);
             ofQuaternion q;
             q.makeRotate(a,d);
             ofVec3f myPoint = ofVec3f(cos((float)k/(float)res*TWO_PI)*radius,sin((float)k/(float)res*TWO_PI)*radius,0);
             mesh.addVertex(p+myPoint*q);
             ofColor thisColor = colorB;
             if(k%2==0) thisColor = colorA;
             if(j==0 && i==0) thisColor = colorC;
             mesh.addColor(thisColor);
             
             }*/
            
            
            
            
            
            
        }
    }
    for(int i=0;i<mesh.getNumVertices()-res;i+=res){
        //            mesh.addIndex(i);
        //            mesh.addIndex(i+res);
        //            mesh.addIndex(i+res-1);
        for(int j=i;j<i+res-1;j++){
            mesh.addIndex(j);
            mesh.addIndex(j+res);
            mesh.addIndex(j+1);
            
            mesh.addIndex(j+1);
            mesh.addIndex(j+res);
            mesh.addIndex(j+res+1);
        }
        //            mesh.addIndex(i+res-1);
        //            mesh.addIndex(i+res-1+res);
        //            mesh.addIndex(i+res-1+res+1);
    }
    
    int offset = 0;
    for(int i=mesh.getNumVertices()-res;i<mesh.getNumVertices()-1;i++){
        mesh.addIndex(i);
        mesh.addIndex(offset);
        mesh.addIndex(i+1);
        
        mesh.addIndex(i+1);
        mesh.addIndex(offset);
        mesh.addIndex(offset+1);
        offset++;
    }

    
    ////////////////////////////////////////////////////////////////////////////////
    
    
    // ofBackground(255);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,zPos);
    
    
    ofRotateY((float)mouseX);
    ofRotateX((float)mouseY);
    
    ofTranslate(-150,-150,0);
    
    ofSetColor(255);
    ofEnableDepthTest();
    mesh.enableColors();
    mesh.drawFaces();
    
    
    
    mesh.disableColors();
    mesh.drawWireframe();
    
    
    
    for(int i=0;i<curves.size();i++){
        
        
        ofxCurve * curve = curves.at(i);
        
        ofNoFill();
        ofSetColor(0);
        curve->draw();
        ofDrawEllipse(curve->start,5,5);
        ofDrawEllipse(curve->startControl,5,5);
        ofDrawEllipse(curve->endControl,5,5);
        ofDrawEllipse(curve->end,5,5);
        ofDrawLine(curve->start,
                   curve->startControl);
        ofDrawLine(curve->end,
                   curve->endControl);
        
        ofVec3f d = curve->getDirection(t);
        ofVec3f p = curve->plot3d(t);
        
        ofSetColor(0,0,0);
        ofFill();
        ofDrawEllipse(p, 10, 10);
        ofDrawEllipse(p+d*100.0f,5,5);
        ofDrawLine(p,p+d*100.0f);
        
        /*
         ofVec3f myAngle = ofVec3f(100.0f,0,0);
         
         ofSetColor(255,0,0);
         for(int i=0;i<16;i++){
         ofVec3f normal = myAngle.getRotated(i*360/16,d);
         
         ofDrawEllipse(p+normal,5,5);
         //  ofDrawLine(p,p+normal);
         }
         
         myAngle = ofVec3f(0,100.0f,0);
         ofSetColor(0,255,0);
         for(int i=0;i<16;i++){
         ofVec3f normal = myAngle.getRotated(i*360/16,d);
         
         
         ofDrawEllipse(p+normal,5,5);
         //   ofDrawLine(p,p+normal);
         }
         
         myAngle = ofVec3f(0,0,100.0f);
         ofSetColor(0,0,255);
         for(int i=0;i<16;i++){
         ofVec3f normal = myAngle.getRotated(i*360/16,d);
         
         
         ofDrawEllipse(p+normal,5,5);
         //    ofDrawLine(p,p+normal);
         }
         */
        //    okay here's what i'm trying to do...
        // v1 = new THREE.Vector3(1, 1, 1)
        // v2 = new THREE.Vector3(1, 1, -1)
        //var quaternion = new THREE.Quaternion().setFromUnitVectors( v1, v2 );
        // var matrix = new THREE.Matrix4().makeRotationFromQuaternion( quaternion );
        
        // object.applyMatrix( matrix );
        
        
        ofVec3f myAngle = ofVec3f(0,0,100.0f);
        // radius = 50.0f;
        
        ofQuaternion q;
        q.makeRotate(myAngle,d);
        
        ofSetColor(255);
        for(int i=0;i<16;i++){
            ofVec3f myPoint = ofVec3f(cos((float)i*TWO_PI/16.0f)*radius,sin((float)i*TWO_PI/16.0f)*radius,0);
            
            
            
            
            ofDrawEllipse(p+myPoint*q,5,5);
            ofDrawLine(p,p+myPoint*q);
        }
        
    }
    
    
    //    float radius = 50.0f;
    
    //    for(int i=0;i<8;i++){
    //        float angle = i * 360/8.0f;
    //
    //        ofVec3f rightVec = ofVec3f(radius,0,0).getRotated(t+i,d);
    //        ofVec3f leftVec = ofVec3f(radius,0,0).getRotated(t+i+10,d);
    //
    //        ofSetColor(0,255,0);
    //        ofDrawEllipse(p+rightVec,10,10);
    //        ofSetColor(0,0,255);
    //        ofDrawEllipse(p+leftVec,10,10);
    //
    //
    //    }
    
    
    ofDrawBox(-5,-5,-5,10,10,10);
    
    ofPopMatrix();
    
    ofPopMatrix();
    
    ofDisableDepthTest();
    if(!bHide){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    drawFaces++;
    if(drawFaces>2) drawFaces = 0;
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
