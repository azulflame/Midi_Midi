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
    int stored_duration = 4;

    index = findNote(desired_note, start_time);

    //If valid index is returned delete, otherwise, exit
    if(index == -1)
    {
        qDebug("COULDN'T FIND NOTE");
    }
    else
    {
        stored_duration = note_map.at(start_time)[index].duration;
        note_map.at(start_time).erase(note_map.at(start_time).begin() + index);
    }

    //If last tick does not depend on the deleted note, return here;
    if((start_time + (stored_duration * 20)) < GlobalMainWindow->last_tick)
    {
        return;
    }

    /*When deleting a note that ends at last tick, check to see if you decrease the loop range (last tick) to reflect
      no notes being in the current last tick and update accordingly.*/

    int latest_tick = start_time;
    /*STOP HERE YOU FUCK STOP UNDOING HERE DONT DO UNDO NO MO*/
    //Determine the next latest start time
    for(int i = 0; i < GlobalMainWindow->last_tick; i+=20)
    {
        std::map<int, tone_vector>::iterator track_iterator;

        //Play notes
        track_iterator = note_map.find(i);

        if(track_iterator != note_map.end())
        {
            //Determine the longest note at this time
            for(int j = 0; j < note_map.at(i).size(); j++)
            {
                int note_duration = (note_map.at(i)[j].duration * 20);

                if((note_duration + i) > latest_tick)
                {
                    latest_tick = note_duration + i;
                }
            }
        }
    }

    //Set new end tick
    GlobalMainWindow->last_tick = latest_tick;

    qDebug() << "Tracks last: " << latest_tick;

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
