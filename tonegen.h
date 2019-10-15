#ifndef TONEGEN_H
#define TONEGEN_H
#include <QBuffer>
#include <QAudioFormat>


struct tone{
    QByteArray toneProfile;
    double volume;

};

class ToneGen
{
public:
    ToneGen();
    tone* MakeTone(float freq,float seconds, double volume);
    QByteArray Oscillate(float freq,float seconds);
    void PlayTone(tone *soundProfile);
    void RealTimePlay(float freq, double volume, int currentTime);

    int toneType = 0;

    QByteArray* bytebuf = new QByteArray();
    QAudioFormat format;

};

#endif // TONEGEN_H
