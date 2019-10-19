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
    bool b_IsRealTime = true;
};


#endif // TONEGEN_H
