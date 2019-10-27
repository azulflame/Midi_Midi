

#ifndef TONE_H
#define TONE_H


class tone
{
public:
    tone();
    tone(int freq);

    int frequcnecy = 0.0;
    //int duriation = 0.0;
    double volumeMult = 1.0;
    bool bToneOn = false;
    //double* timePntr = nullptr;
    bool killFlag= false;

    //int ToneStartTime = 0;
    //int ToneEndTime = 0;

    void play();
    void stop();

};

#endif // TONE_H
