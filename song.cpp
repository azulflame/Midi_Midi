#include <vector>
#include "song.h"
#include "track.h"


Song::Song()
{
    tempo = 144;
    time_sig_top = 4;
    time_sig_bottom = 4;
}

void Song::addTrack(Track new_track)
{
    tracks.push_back(new_track);

    return;
}

void Song::removeTrack(int track_id)
{
    for(int i = 0; i < tracks.size(); i++)
    {
        if(track_id == tracks.at(i).id)
        {
            tracks.erase(tracks.begin() + i);

            return;
        }
    }

    return;
}

void Song::setTimeSig(int new_top, int new_bottom)
{
    time_sig_top = new_top;
    time_sig_bottom = new_bottom;

    return;
}

void Song::setTempo(int new_tempo)
{
    tempo = new_tempo;

    return;
}

Song& Song::operator=(const Song &song_data)
{
    tempo = song_data.tempo;
    time_sig_top = song_data.time_sig_top;
    time_sig_bottom = song_data.time_sig_bottom;
    std::vector<Track> tracks = song_data.tracks;

    return *this;
}
