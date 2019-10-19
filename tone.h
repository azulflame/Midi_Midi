

#ifndef TONE_H
#define TONE_H


class tone
{
public:
    tone();
    tone(int freq, double dur, double vol, double* dTime);

    int frequcnecy = 0.0;
    double duriation = 0.0;
    double volumeMult = 0.0;
    bool bToneOn = false;
    //double* timePntr = nullptr;

    double ToneStartTime = 0.0;
    double ToneEndTime = 0.0;

    void start();


};

#endif // TONE_H
