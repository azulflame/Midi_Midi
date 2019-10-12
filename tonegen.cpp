#include "tonegen.h"
#include "audioconstants.h"
#include <QtMultimedia>

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <QKeyEvent>
#include <QWidget>

ToneGen::ToneGen()
{
    // Set up the format, so that QT knows how to play our tones on our machine
    format.setSampleRate(SAMPLE_RATE);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

}

void ToneGen::PlayTone(tone* toneData){

    // Make a QBuffer from our QByteArray
    QBuffer* input = new QBuffer(&(toneData->toneProfile));
    input->open(QIODevice::ReadOnly);

    // Create an output with our premade QAudioFormat
    QAudioOutput* audio = new QAudioOutput(format);
     audio->setVolume(toneData->volume);
     //qDebug() << audio->volume();


    audio->setNotifyInterval(0);
    audio->start(input);
}

tone* ToneGen::MakeTone(float freq,float seconds, double volume){

    QByteArray* toneProfile = new QByteArray();

    toneProfile->resize(seconds * static_cast<float>(SAMPLE_RATE)); // resize the buffer to accomidate the sound being produced
    // sin(2 * pi * frequency * i / sample_rate) will give you a sin tone of the desired frequency, i being an offset

    for (int i=0; i<(seconds * SAMPLE_RATE); i++) {
        double freqOffset = static_cast<double>(freq * i); // frequency *i
        freqOffset = (freqOffset * static_cast<double>(FREQ_CONST)); // (frequency *i)*((2.0 * M_PI) / SAMPLE_RATE)
        freqOffset = qSin(freqOffset); // sin((frequency *i)*((2.0 * M_PI) / SAMPLE_RATE))
        freqOffset *= AMP; // now we normalize freqOffset, this doesn't affect volume. QT compresses all volume to the set scaler audio->volume.
        (*toneProfile)[i] = (quint8)freqOffset; // stuff that tone into the a byte array, one byte at a time
    }
    tone* toneData = new tone; // make a new tone
    toneData->toneProfile = *toneProfile;
    toneData->volume = volume;
    delete toneProfile; // clean up pointer
    return(toneData);
}

void ToneGen::RealTimePlay(float freq, double volume, int currentTime){

    QByteArray* toneProfile = new QByteArray();

    toneProfile->resize(static_cast<float>(SAMPLE_RATE)); // resize the buffer to accomidate the sound being produced
    // sin(2 * pi * frequency * i / sample_rate) will give you a sin tone of the desired frequency, i being an offset

    for (int i=0; i<(SAMPLE_RATE/60); i++) {
        double freqOffset = static_cast<double>(freq * (currentTime+i)); // frequency *i
        freqOffset = (freqOffset * static_cast<double>(FREQ_CONST)); // (frequency *i)*((2.0 * M_PI) / SAMPLE_RATE)
        freqOffset = qSin(freqOffset); // sin((frequency *i)*((2.0 * M_PI) / SAMPLE_RATE))
        freqOffset *= AMP; // now we normalize freqOffset, this doesn't affect volume. QT compresses all volume to the set scaler audio->volume.
        (*toneProfile)[i] = (quint8)freqOffset; // stuff that tone into the a byte array, one byte at a time
    }
    //qDebug() << freqOffset;
    tone* toneData = new tone; // make a new tone
    toneData->toneProfile = *toneProfile;
    toneData->volume = volume;
    delete toneProfile; // clean up pointer
    PlayTone(toneData);
}

