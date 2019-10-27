#include "tone.h"

tone::tone()
{

    frequcnecy = 0;
    //duriation = 0.0;
    volumeMult = 0.0;
    bToneOn = false;
    //ToneStartTime = 0.0;
    //ToneEndTime = 0.0;
}

tone::tone(int freq)
{
    frequcnecy = freq;
    //duriation = dur;
    //volumeMult = vol;

}

void tone::play(){

    bToneOn = true;
    //ToneStartTime = *timePntr;
    //ToneEndTime = ToneStartTime + duriation;
}

void tone::stop(){
    bToneOn = false;

}
