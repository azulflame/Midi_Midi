#ifndef TONEGEN_H
#define TONEGEN_H
#include <QtCore>
#include "olcnoisemaker.h"
#include "tone.h"

class ToneGen : public QThread
{
public:
    ToneGen();
    void run();

    int nCurrentKey = -1;
    bool bKeyPressed = false;
    vector<tone> toneVector;
    olcNoiseMaker<short> sound;
    bool b_IsRealTime = false;
    void addTone(int toneToAdd);
    void removeTone(int toneToRemove);
    void playTone(int toneToPlay);
    void stopTone(int toneToStop);

};


#endif // TONEGEN_H
