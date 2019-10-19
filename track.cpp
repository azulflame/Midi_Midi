#include "track.h"
#include <map>
#include <vector>
#include "tonegen.h"

tone_vector Track::getNotesAtTime(int start_time)
{
    return note_map.at(start_time);
}

int Track::findNote(tone* desired_note, int start_time)
{
    int index = -1;

    for(int i = 0; i < note_map.at(start_time).size(); i++)
    {
        if(note_map.at(start_time).at(i) == desired_note)
        {
            index = i;
        }
    }

    return index;
}

void Track::removeNote(tone* desired_note, int start_time)
{
    int index;

    index = findNote(desired_note, start_time);

    //If valid index is returned delete, otherwise, exit
    if(index == -1)
    {
        qDebug("COULDN'T FIND NOTE");
    }
    else
    {
        note_map.at(start_time).erase(note_map.at(start_time).begin() + index);
    }

    return;
}

void Track::addNote(tone* new_note, int start_time)
{
    note_map.at(start_time).push_back(new_note);

    return;
}
