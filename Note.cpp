#include "MidiEvent.h"
#include <cmath>
class Note
{
	public:
		double frequency;
		double beatDuration;
		double startBeat;
		int tempo;
		int pianoKey;
		int velocity;
		Note(smf::MidiEvent event, int ticksPerQuarterNote, int tempoinput)
		{
			ev = event;
			tempo = tempoinput;
			pianoKey = event[1];
			velocity = event[2];
			frequency = pow(2, (double)(pianoKey-69)/12) * 440;
			startBeat = event.tick / ticksPerQuarterNote;
			beatDuration = event.getTickDuration() / ticksPerQuarterNote;
		}
		
	private:
		smf::MidiEvent ev;
};

int main(){ return 0;}
