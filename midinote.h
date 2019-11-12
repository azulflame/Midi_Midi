#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class MidiNote
{
public:
    MidiNote();
    MidiNote(int new_val, double new_duration);

    double duration;
    int value;

};

#endif // NOTE_H
