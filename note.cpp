#include "note.h"
#include "tonegen.h"

Note::Note()
{
    Tone = nullptr;
    start_time = -1;
}

Note::Note(tone* t, int s)
{
    Tone = t;
    start_time = s;
}

void Note::setNote(tone* t, int s)
{
    Tone = t;
    start_time = s;
}
