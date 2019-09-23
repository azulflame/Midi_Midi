#include "MidiFile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "MidiEvent.h"
#include <string>

using namespace std;
using namespace smf;

struct Note{
	int key;
	int vel;
	int duration;
	int start; 
};

int main(int argc, char *argv[])
{
	if(argc < 2) // argument sanity check
	{
		cout << "please add the filename on the command line" << endl;
		return 1;
	}
	
	vector<Note> noteVect; // used to hold notes, not used in this file

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
					// copy certain values
					int key = (int)midi[track][event][1]; // note in MIDI terms
					int velocity = (int)midi[track][event][2];	// volume
					int startTick = midi[track][event].tick;	// start point
					int durationTick = midi[track][event].getTickDuration();	// duration in ticks
					
					// generate a new Note
					// fill it out
					// and add it to the vector
					// this is not used for this file, it is just a setup
					Note note;
					note.key = key;
					note.vel = velocity;
					note.start = startTick;
					note.duration = durationTick;
					noteVect.push_back(note);
					
					// print what we pulled out
					cout << "key: " << key << endl;	// key, range of 21-108, 21 being low notes
					cout << "vel: " << velocity << endl;
					cout << "sbt: " << startTick << endl;
					cout << "dur: " << durationTick << endl << endl;
				}
			}
		}
	}
}
