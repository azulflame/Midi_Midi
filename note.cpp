#include "note.h"

Note::Note()
{
    frequency = 261.63f;
    duration = 1.0f;
    amplitude = 0.3;
}

Note::Note(float f, float d, double a)
{
    frequency = f;
    duration = d;
    amplitude = a;
}
