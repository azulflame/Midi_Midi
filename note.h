#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Note
{
public:
    Note();
    Note(float f, float d, double a);
    float frequency;
    float duration;
    double amplitude;
};

#endif // NOTE_H
