#include "MidiFile.h"
#include <iostream>
#include <vector>
#include "MidiEvent.h"
#include "Note.h"
#include <cmath>

using namespace std;
using namespace smf;

int main(int argc, char *argv[])
{
	if(argc < 2) // argument sanity check
	{
		cout << "please add the filename on the command line" << endl;
		return 1;
	}
	
	vector<Note*> noteVect; // used to hold notes, not used in this file

	// read and link the midi file
	MidiFile midi;
	midi.read(argv[1]);
	midi.linkNotePairs();
	// for each track
	for(int track = 0; track < midi.size(); track++)
	{
		// for each event in every track
		for(int event = 0; event < midi[track].size(); event++)
		{
			// if the event is a note start
			if(midi[track][event].isNoteOn())
			{
				// and it is linked to a note end
				if(midi[track][event].isLinked())
				{
					// generate a new Note
					// fill it out
					// and add it to the vector
					// this is not used for this file, it is just a setup
					Note *note = new Note(midi[track][event], midi.getTicksPerQuarterNote(), 1, midi[track][event].getTickDuration());
					noteVect.push_back(note);
					
					// print what we pulled out
					cout << "key: " << note->pianoKey << endl;	// key, range of 21-108, 21 being low notes
					cout << "frequency: " << note->frequency << "Hz" << endl;
					cout << "velocity: " << note->velocity << endl;
					cout << "start beat: " << note->startBeat << endl;
					cout << "duration: " << note->beatDuration << endl << endl;
				}
			}
		}
	}
}
