#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidGrabber.setup(ofGetWidth(),ofGetHeight()); //set up video
	
    
    myColorImg.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayImage.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myBackground.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayDiff.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());

    
	bLearnBackground = true;
	threshold = 30;
	ofSetBackgroundAuto(false);
    
    
    //set up text rain
    for(int i=0; i<NRAIN; i++){
        letters[i] = generateString();
    };
    
    


}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100,100,100);

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
    


}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// draw the incoming video image
	ofSetHexColor(0xffffff);
    
	ofPushMatrix();
    
	if(bShowVideo){
		//myGrayDiff.draw(0,0);
         myColorImg.draw(0,0);
        //myGrayDiff.draw(myColorImg.getWidth(),0);
	}
    
    ofPopMatrix();

    //draw falling rain
    
    fallingLetters();
    
    ofPushMatrix();
    ofSetColor(ofColor::darkBlue);
    ofFill();
    ofDrawBitmapString("Press + and - to adjust Threshold", ofGetWidth()/2.0, ofGetHeight()-100.0);
    ofPopMatrix();
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

char ofApp::generateString(){
    char string[4] = {'R','A','I','N'};
    char currentChar = string[rand() % 5];
    return currentChar;
}


void ofApp::fallingLetters(){
    
    //asign variable to get pixels of myGrayDiff
    
    pix = myGrayDiff.getPixels();
    
    //deteremine letter spacing, position and speed

    float letterPosX = 0;
    int letterXSpace = vidGrabber.getWidth()/NRAIN;
    float letterSpeed = 1;

    
   // cout << letterXSpace << '/' ;
    
  //loop to generte rain
    
    for(int i=0; i<NRAIN; i++){
        
        int locX = letterPosX + ( i * letterXSpace);
        int locY = letterPosY[i] ;
       
        //lerp colors for shades of blue
        firstColor = ofColor(0,5,127);
        secondColor = ofColor(0,10,255);
        
        lerpColor = secondColor.lerp(firstColor, i / 0.5);
        
        ofDrawBitmapString(letters[i], letterPosX, letterPosY[i]);
        ofSetColor(lerpColor);
        ofFill();
        
        letterPosX += letterXSpace;
        
        float pixBrightness = pix.getColor(locX,locY).getBrightness(); //get pixel brightness
        
        if(letterPosY[i] >= vidGrabber.getHeight() - 1) //if letter is at the bottom of video, return to top
        {
            letterPosY[i] = 0;
        }
        
        else if(pixBrightness > threshold) //if pixel brightness is dark slow down letters and reverse speed
        {
            if(letterPosY[i] > 10)
            {
                ofSetColor(ofColor::antiqueWhite);
                letterPosX += (rand()%2);
                letterPosY[i]-=letterSpeed;
 
            }
        }
        else
        {
            letterPosY[i]+=letterSpeed; //otherwise keep raining
        }
    }

}
