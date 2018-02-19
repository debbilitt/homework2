#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setup(320,240);
	
		
    myColorImg.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayImage.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myBackground.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayDiff.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());

	bLearnBackground = true;
	threshold = 80;
	ofSetBackgroundAuto(false);
    
    
    //set up rain 
    
        for(int i=0; i<NRAIN; i++){
    
          //  int size = (i+1) * 10; // defining the size of each ball based on its place in the array
            int randomX = ofRandom( 0, ofGetWidth() ); //generate a random value bigger than 0 and smaller than our application screen width
//            int randomY = ofRandom( 0, ofGetHeight() ); //generate a random value bigger than 0 and smaller than our application screen height
//    
            rainDrops[i].setup(randomX, 0, 100);
        }

}

//--------------------------------------------------------------
void ofApp::update(){
	//ofBackground(100,100,100);

    bool bNewFrame = false;


	vidGrabber.update();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){


		myColorImg.setFromPixels(vidGrabber.getPixels());

        myGrayImage = myColorImg;
            if (bLearnBackground == true){
                myBackground = myGrayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
                bLearnBackground = false;
            }

		// take the abs value of the difference between background and incoming and then threshold:
		myGrayDiff.absDiff(myBackground, myGrayImage);
		myGrayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(myGrayDiff, 20, (340*240)/3, 1, false);
    }

    
    //update some rain
    for(int i=0; i<NRAIN; i++){
             rainDrops[i].update();
       }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
	
	// draw the incoming video image
	ofSetHexColor(0xffffff);
    
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2 - myColorImg.getWidth()/2,ofGetHeight()/2 - myColorImg.getHeight()/2);
	if(bShowVideo){
		myColorImg.draw(0,0);
	}
    
// original example code - I did not see much of a difference between using boundingRect or centroids
//      for (int i = 0; i < contourFinder.nBlobs; i++){
//		ofSetColor(ofColor::fuchsia);
//		ofFill();
//		//ofDrawEllipse(contourFinder.blobs[i].boundingRect.getCenter(), 20,20);
//        ofDrawEllipse(contourFinder.blobs[i].centroid, 20,20);
//    }
    
    for(auto &blob : contourFinder.blobs){
        ofSetColor(ofColor::violet);
        ofFill();
        ofDrawEllipse(blob.centroid, 20,20);
        
        
    }
    
    
    //draw some balls
    for(int i=0; i<NRAIN; i++){
        rainDrops[i].draw();
    }
    
	ofPopMatrix();
    
    
    

	
	ofDrawBitmapString("Press 'v' to toggle video and path drawing", ofGetWidth()/2.0, ofGetHeight()-100.0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case 'v':
			ofBackground(ofColor::white);
			bShowVideo = !bShowVideo;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
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
