#include <vector>
#include "song.h"
#include "midinote.h"
#include "track.h"


Song::Song()
{
    Track empty_track;
    vector<MidiNote> empty_nums;
    //Default values for now, we may just want to leave these as is, but we currently have the option to change them
    tempo = 144;
    time_sig_top = 4;
    time_sig_bottom = 4;
    this->addTrack(empty_track);
}

void Song::addTrack(Track new_track)
{
    tracks.push_back(new_track);

    return;
}

/*
 * Each track needs a unique ID due to the fact that tracks may or may not have the same instrument,
 * so deleting based on the instrument would not be ideal.
 */
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

//Done so we can easily swap between project by setting current song equal to a song object.
Song& Song::operator=(const Song &song_data)
{
    tempo = song_data.tempo;
    time_sig_top = song_data.time_sig_top;
    time_sig_bottom = song_data.time_sig_bottom;
    std::vector<Track> tracks = song_data.tracks;

    return *this;
}
