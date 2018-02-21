#ifndef _RAIN // if this class hasn't been defined, the program can define it
#define _RAIN // by using this if statement you prevent the class to be called more than once which would confuse the compiler
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
class Rain {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void setup(float _x, float _y, char _letter);	// setup method, use this to setup your object's initial state
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
//    void checkDistance(); //check its distance to the other vector
   char generateString();
//    void fallingLetters();
    
    // variables
//    float x;        // position
//    float y;
    
//    float speedY;   // speed and direction
//    float speedX;
    //int dim;        // size
    
    ofColor color;  // color using ofColor type
    
    ofTrueTypeFont myfont;
    
    //textrain variable
//    
//    float letterSpeed = 1;
//    float letterPosX = 0;
//    float letterPosY [NRAIN] = {};
//    float letterXSpace;
//    float threshold = 80.0;
//     char letters [NRAIN] = {};

    
//    char str;
    
    //new variables
    
    char letter;
    float x;
    float y;
    int velocity;
    int threshold;

    ofPixels                pix;

    float pixBrightness;

    
    Rain();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
    
private: // place private functions or variables declarations here
    
};
#endif
