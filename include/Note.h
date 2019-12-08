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
		Note(smf::MidiEvent event, int ticksPerQuarterNote, int tempoinput, int tickDuration);
		
		
	private:
		smf::MidiEvent ev;
};
