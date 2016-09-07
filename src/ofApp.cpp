#include "ofApp.h"

int drawFaces;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);

    // gui stuff
    gui.setup("my panel"); // most of the time you don't need a name
gui.add(radius.setup("radius", 140, 10, 300));
    gui.add(colorA.setup("colorA", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(colorB.setup("colorB", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(colorC.setup("colorC", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(colorD.setup("colorD", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    
    gui.add(rotSpeed.setup("rot. speed",0.0f,-5.0f,5.0f));
    
    gui.add(bBackground.setup("redraw background", true));

    gui.loadFromFile("settings.xml");
    
    bHide = false;

    
    capture = false;
    
    drawFaces = 0;
    
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
    
    
    
    
    a.set(0,0,0);
    b.set(200,0,0);
    c.set(0,200,200);
    d.set(0,200,0);
    
    curve = new ofxCurve(a,b,c,d);
    
   
    ofBackground(0);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    curve->update();
    
    t += rotSpeed;
    
    while(t>360.0f) t -=360.0f;
    
    for(int i=0;i<curves.size();i++){
        ofxCurve * c = curves.at(i);
        ofSetColor(255);
        ofNoFill();
        c->update();
    }
    
    ofEnableDepthTest();
    
     ofSetBackgroundAuto(bBackground);
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //we don't want to capture every frame
    //so we only capture one frame when capture
    //is set to true
    //    if(capture){
    //        output.beginEPS("test.ps");
    //    }
    //
    //    output.noFill();
    
    //ofBackground(0);
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,900);
    
    
    ofRotateY((float)mouseX);
    ofRotateX((float)mouseY);
    
    ofTranslate(-150,-150,0);
    
    ofPoint pt = curve->plot3d(t);
    
    // ofDrawEllipse(pt.x,pt.y,pt.z,10,10);
    
    
    
    ofNoFill();
    ofSetColor(0);
    // curve->draw();
    
    
    ofMesh mesh;
    ofMesh mesh2;
    ofMesh mesh3;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh2.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
     mesh3.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //mesh.setupIndicesAuto();
    
    for(int i=0;i<curves.size();i++){
        ofxCurve * c = curves.at(i);
        ofSetColor(0);
        
        ofNoFill();
        // c->draw();
        
        int numSections = 256;
        
        for(int j=0;j<numSections;j++){
            float t2 = (float)j/(float)numSections;
            float t3 = t2* 360.0f;
            while(t2>1.0f) t2-= 1.0f;
            ofVec3f p =c->plot3d(t2);
            ofVec3f n = c->getNormal(t2) * 25.0f;
            
            ofVec3f rightVec = ofVec3f(20,0,0).getRotated(t+5,n);
            ofVec3f leftVec = ofVec3f(20,0,0).getRotated(t,n);

            mesh.addVertex(p+rightVec);
            mesh.addColor(ofColor(colorA));
            mesh.addVertex(p+leftVec);
            mesh.addColor(ofColor(colorB));

        }
        
        for(int j=0;j<numSections;j++){
            float t2 = (float)j/(float)numSections;
            //while(t2>1.0f) t2-= 1.0f;
            ofVec3f p =c->plot3d(t2);
            ofVec3f n = c->getNormal(t2) * 25.0f;
            
            ofVec3f rightVec = ofVec3f(10,0,0).getRotated(t+5+240,n);
            ofVec3f leftVec = ofVec3f(10,0,0).getRotated(t+240,n);
            
            mesh2.addVertex(p+rightVec);
            mesh2.addColor(ofColor(colorA));
            mesh2.addVertex(p+leftVec);
            mesh2.addColor(ofColor(colorC));
            
        }
    
        
        for(int j=0;j<numSections;j++){
            float t2 = (float)j/(float)numSections;
            while(t2>1.0f) t2-= 1.0f;
            ofVec3f p =c->plot3d(t2);
            ofVec3f n = c->getNormal(t2) * 25.0f;
            
            ofVec3f rightVec = ofVec3f(30,0,0).getRotated(t+5+120,n);
            ofVec3f leftVec = ofVec3f(30,0,0).getRotated(t+120,n);
            
            
            mesh3.addVertex(p+rightVec);
            mesh3.addColor(ofColor(colorA));
            mesh3.addVertex(p+leftVec);
            mesh3.addColor(ofColor(colorD));
            
        }
      
        
    }
    
  
    for(int i=0;i<mesh.getNumVertices()-2;i+=2){
        mesh.addIndex(i);
        mesh.addIndex(i+1);
        mesh.addIndex(i+2);
        
        mesh.addIndex(i+2);
        mesh.addIndex(i+3);
        mesh.addIndex(i+1);
    }
    
            mesh.addIndex(mesh.getNumVertices()-2);
            mesh.addIndex(mesh.getNumVertices()-1);
            mesh.addIndex(0);
    
    mesh.addIndex(0);
    mesh.addIndex(1);
    mesh.addIndex(mesh.getNumVertices()-1);

    for(int i=0;i<mesh2.getNumVertices()-2;i+=2){
        mesh2.addIndex(i);
        mesh2.addIndex(i+1);
        mesh2.addIndex(i+2);
        
        mesh2.addIndex(i+2);
        mesh2.addIndex(i+3);
        mesh2.addIndex(i+1);
    }
    
    mesh2.addIndex(mesh.getNumVertices()-2);
    mesh2.addIndex(mesh.getNumVertices()-1);
    mesh2.addIndex(0);
    
    mesh2.addIndex(0);
    mesh2.addIndex(1);
    mesh2.addIndex(mesh.getNumVertices()-1);

    for(int i=0;i<mesh3.getNumVertices()-2;i+=2){
        mesh3.addIndex(i);
        mesh3.addIndex(i+1);
        mesh3.addIndex(i+2);
        
        mesh3.addIndex(i+2);
        mesh3.addIndex(i+3);
        mesh3.addIndex(i+1);
    }
    
    mesh3.addIndex(mesh.getNumVertices()-2);
    mesh3.addIndex(mesh.getNumVertices()-1);
    mesh3.addIndex(0);
    
    mesh3.addIndex(0);
    mesh3.addIndex(1);
    mesh3.addIndex(mesh.getNumVertices()-1);
    
    
    
    ofSetColor(255);
    
    if(drawFaces == 0){
        mesh.drawFaces();
        mesh2.drawFaces();
        mesh3.drawFaces();
    } else if(drawFaces == 1) {
        mesh.drawVertices();
        mesh2.drawVertices();
        mesh3.drawVertices();
    } else if(drawFaces == 2){
        mesh.drawWireframe();
        mesh2.drawWireframe();
         mesh3.drawWireframe();
    }
    ofPopMatrix();
    
    ofDisableDepthTest();
    if(!bHide){
        gui.draw();
    }
    
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //    curves.clear();
    //    setup();
    if(key == 'd'){
        drawFaces++;
        if(drawFaces>2){
            drawFaces = 0;
        }
    } else if(key == ' '){
        bBackground = !bBackground;
    }
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
