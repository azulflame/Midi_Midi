#ifndef SONG_H
#define SONG_H
#include "track.h"
#include <vector>

/*
 * The Song class will hold all relevant data for a given project, so the data used for
 * saving and loading will directly correlate to the information contained inside of an instance of this class.
 * So this class essentially correlates directly to a project.
 */

class Song
{
public:
    Song();
    void addTrack(Track new_track); //Create a new track (If we ever implement more)
    void removeTrack(int track_id); //Remove an existing track (If we ever implement more)
    void setTimeSig(int new_top, int new_bottom); //Update given time signature
    void setTempo(int new_tempo); //Update the tempo of the song

    Song& operator=(const Song &currentSong); //For ease of access to say song1 = song2;

    int tempo; //Beats per minute
    int time_sig_top; //Beats per measure
    int time_sig_bottom; //Note that gets beat
    std::vector<Track> tracks; //All tracks for the current project (we're assuming only 1 for now)
};

#endif // SONG_H
