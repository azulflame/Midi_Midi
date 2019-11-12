#include "track.h"
#include <map>
#include <vector>
#include "midinote.h"
#include "tonegen.h"
#include "common.h"

Track::Track()
{
    id = 0;
}

tone_vector Track::getNotesAtTime(int start_time)
{
    return note_map.at(start_time);
}

int Track::findNote(int desired_note, int start_time)
{
    int index = -1;

    //Search for the requested note pointer within the start time map
    for(int i = 0; i < note_map.at(start_time).size(); i++)
    {
        if(note_map.at(start_time).at(i).value == desired_note)
        {
            index = i;
        }
    }

    return index;
}

void Track::removeNote(int desired_note, int start_time)
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

        /*UPDATE UI AS NEEDED HERE*/
    }

    return;
}

void Track::addNote(int note_value, float note_duration, int start_time)
{
    MidiNote new_note;

    new_note.value = note_value;
    new_note.duration = note_duration;

    GlobalToneGenPntr->addTone(note_value); //Add not to sythesizer note collection, then add it to the current collection of notes

    std::map<int, tone_vector>::iterator track_iterator;

    track_iterator = note_map.find(start_time);

    if(track_iterator == note_map.end())
    {
        vector<MidiNote> empty_vector;
        note_map[start_time] = empty_vector;
    }

    note_map[start_time].push_back(new_note);

    return;
}
