#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include "tonegen.h"

class Note
{
public:
    Note();
    Note(tone* Tone, int s);
    void setNote(tone* t, int s);
    tone* Tone;
    int start_time;

};

#endif // NOTE_H
