#pragma once

#include "ofMain.h"
#include "visEffect.h" // the Faust module
#include "ofxFft.h"

//-----------------------------------------------------------------------------
// Preprocessor definitions
//-----------------------------------------------------------------------------
#define MY_SRATE         44100            // sample rate
#define MY_CHANNELS      2                // number of channels
#define MY_BUFFERHISTORY 72               // number of buffers to save
#define MY_BUFFERSIZE    512              // number of frames in a buffer
#define MY_NBUFFERS      2                // number of buffers latency
#define MY_PIE           3.14159265358979 // for convenience
#define N_BINS           MY_BUFFERSIZE / 2
// for convenience


//-----------------------------------------------------------------------------
// My application
//-----------------------------------------------------------------------------

class SetColors {
public:
    // Constructor and destructor -- do nothing
    SetColors() {}
    ~SetColors() {}
    
    void setup(){
        color.r = ofRandom(0, 255);            // Get random color (r)
    }
    
    void update(float alphaValue, float fade) {
        // Update the alpha value, so it can be responsive to input
        // (in our case, the magnitude of an FFT bin.
        alphaValue= alphaValue*100.0;
        
        color.a = 255 / (alphaValue*1.3);
        color.r = 128 + 188 * alphaValue;
        color.g = 128 + 110 * (alphaValue);
        color.b = 128 + 128  * alphaValue*1.2;
//        std::cout << alphaValue << "\n";

       
    }
    void findLargestBin()
    {
        
    }
    
    void draw() {
    }
    
    void setColor() {
        ofSetColor(color);
    }
    
private:
    // Member variables
//    ofImage bokeh_image;     // Holds our image data
    ofColor color;     // Keep track of Color's color
    int x, y, width, height; // Position member variables
};



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

    // Get buffer samples
    void audioIn(float * input, int bufferSize, int nChannels);

    void audioOut(float * input, int bufferSize, int nChannels);

    //------------------- for Faust reverb stuff!
    float **audioBuffer; // The 2d audio buffer that Faust wants to work with
    
    visEffect effect; // the Faust module (Reverb.h)
    MapUI effectControl; // used to easily control the Faust module (Reverb.h)
    
    ofMutex myMutex;
    ofNode node;
    
    // Our sound stream object
    ofSoundStream soundStream;
    
    vector <float> lAudio;
    vector <float> rAudio;
    
private:
  
    ofxFft* fft;

    // Vectors for our left- and right-channel waveforms
    vector<float> left;
    vector<float> right;
    
    vector<float> faustLeft;
    vector<float> faustRight;
    
    // Double vectors to save previous waveforms, for plotting in the waterfall
    vector< vector<float> > leftHistory;
    vector< vector<float> > rightHistory;
    
    float disIntensity;
    float mouse1;
    float mouse2;
    float mouse3;
    bool myDis;
    bool effectOn;
    bool catMode;
    bool catMode2;
    bool catMode3;
    bool fftSwitch;
    float addSub;
    float fade;
    float speed;
    SetColors myCol[N_BINS];
    float rotIncr;
};
