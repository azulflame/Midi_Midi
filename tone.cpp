#include "tone.h"

tone::tone()
{

    frequcnecy = 0;
    duriation = 0.0;
    volumeMult = 0.0;
    bToneOn = false;
    ToneStartTime = 0.0;
    ToneEndTime = 0.0;
}

tone::tone(int freq, double dur, double vol, double* dTime)
{
    frequcnecy = freq;
    duriation = dur;
    volumeMult = vol;
    //timePntr = dTime;

}

void tone::start(){

    bToneOn = true;
    //ToneStartTime = *timePntr;
    //ToneEndTime = ToneStartTime + duriation;
}
