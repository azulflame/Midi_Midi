#ifndef TRACK_H
#define TRACK_H
#include <map>
#include <vector>
#include "tonegen.h"

typedef std::vector<tone*> tone_vector;

class Track
{
public:
    Track();
    tone_vector getNotesAtTime(int start_time);
    void addNote(tone* new_note, int start_time);
    void removeNote();

    std::map<int, tone_vector> note_map;
    int id;
};

#endif // TRACK_H
