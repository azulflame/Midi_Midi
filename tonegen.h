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
    void PlayTone(tone *soundProfile);
    void RealTimePlay(float freq, double volume, int currentTime);

    QByteArray* bytebuf = new QByteArray();
    QAudioFormat format;

};

#endif // TONEGEN_H
