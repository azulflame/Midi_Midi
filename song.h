#ifndef SONG_H
#define SONG_H
#include "track.h"
#include <vector>

class Song
{
public:
    Song();
    void addTrack(Track new_track);
    void removeTrack(int track_id);
    void setTimeSig(int new_top, int new_bottom);
    void setTempo(int new_tempo);

    int tempo;
    int time_sig_top;
    int time_sig_bottom;
    std::vector<Track> tracks;

};

#endif // SONG_H
