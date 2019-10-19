#ifndef TRACK_H
#define TRACK_H
#include <map>
#include <vector>
#include "tonegen.h"

typedef std::vector<tone*> tone_vector;

class Track
{
public:
    tone_vector getNotesAtTime(int start_time); //Return all notes to be played at a given start time
    void addNote(tone* new_note, int start_time); //Add a note to collection of notes
    int findNote(tone* desired_note, int start_time); //Find the position on the collection of a given note pointer
    void removeNote(tone* desired_note, int start_time); //Remove a note from the collection

    std::map<int, tone_vector> note_map; //All the notes in a given track, mapped by start time
    int id; //Idenfifier for this track (if we every add multiple)
};

#endif // TRACK_H
