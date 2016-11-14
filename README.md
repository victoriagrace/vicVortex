# vicVortex

- This vortex visualizer reacts sound coming into your computer's microphone input and features a vocal effect that can be turned on by pressing the 'v' key on your keyboard.

- Use the up and down arrow keys to change the distance between circular waveforms.

- Click and drag your mouse to adjust the size of the waveform object.

- Rotational transformations can be turned on and off by keys 'z', 'x' and 'c'

- The default mode uses only the time domain signal where the colors and distance between circles can be changed by 'q', 'w', 'e', 'r' and 't' keys. 

- You can switch to an FFT mode where the colors of the vortex are set by the amplitudes in each FFT bins.  


To Build:

Extract this directory and place it in your $OF/apps/myapps/ directory, where $OF is the path to your OpenFrameworks directory. On OSX, open up waveformWaterfall.xcodeproj and build the target for "waveformWaterfall Release > My Mac (64 bit)" (or Debug, or 32-bit, etc.)

NOTE: This code requires that you have downloaded the ofxFft addon and included it in your project. You can download from https://github.com/kylemcdonald/ofxFft and then unzip it into openFrameworks/addons/ofxFft/

