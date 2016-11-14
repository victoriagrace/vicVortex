import("reverb.lib");
import("delay.lib");
import("filter.lib");
import("compressor.lib");

//import("miscoscillator.lib");


n =2; //the max delay length as a power of 2
d = hslider("delayLength",1,0,44100,0.01) :si.smoo; //the delay length as a number of samples (float)
dt1 =10;// hslider("decayTime1",0.5,0,20,0.01) :si.smoo; //the delay length as a number of samples (float)
dt2 =10;// hslider("decayTime2",0.5,0,20,0.01) :si.smoo; //the delay length as a number of samples (float)

rdel = 1; 
f1= 400;
f2= 6000;
t60dc= dt1;
t60m = dt2;
fsmax= 44100;

delayMe = _ : delay(n,d) : _;
process = hgroup("saw",_,_ :bp,bp :zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax) :comp,comp :dcblocker, dcblocker); //: delayMe, delayMe: bp,bp: comp, comp;

comp=compressor_mono(ratio1,thresh1,.002,.4) *1.5;

bp= bandpass(4,200,900);

ratio1= 5;
thresh1= -30;