#ifndef TRACK_H
#define TRACK_H
#include <map>
#include <vector>
#include "tonegen.h"
#include "midinote.h"

typedef std::vector<MidiNote> tone_vector;

/*
 * Note: The collection of notes is stored in a map so that we dont need
 * to exhaustively search through all the notes to find notes that play at a given time.
 * Instead we simply map a collection of notes based on their designated start time in
 * the UI, so that we need only search the notes relevant to the current time that we care
 * about.
 */
class Track
{
public:
    Track();
    tone_vector getNotesAtTime(int start_time); //Return all notes to be played at a given start time
    void addNote(int note_value, float note_duration, int start_time); //Add a note to collection of notes
    int findNote(int desired_note_value, int start_time); //Find the position on the collection of a given note pointer
    void removeNote(int desired_note, int start_time); //Remove a note from the collection

    std::map<int, tone_vector> note_map; //All the notes in a given track, mapped by start time
    int id; //Idenfifier for this track (if we every add multiple)
};

#endif // TRACK_H
