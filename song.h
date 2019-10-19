#ifndef SONG_H
#define SONG_H
#include "track.h"
#include <vector>

class Song
{
public:
    Song();
    void addTrack(Track new_track); //Create a new track (If we ever implement more)
    void removeTrack(int track_id); //Remove an existing track (If we ever implement more)
    void setTimeSig(int new_top, int new_bottom); //Update given time signature
    void setTempo(int new_tempo); //Update the tempo of the song

    Song& operator=(const Song &currentSong);

    int tempo;
    int time_sig_top;
    int time_sig_bottom;
    std::vector<Track> tracks;
};

#endif // SONG_H
