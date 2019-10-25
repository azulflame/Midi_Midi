#include "MidiEvent.h"
#include "Note.h"
Note::Note(smf::MidiEvent event, int ticksPerQuarterNote, int tempoinput, int tickDuration)
{
	ev = event;
	tempo = tempoinput;
	pianoKey = event[1];
	velocity = event[2];
	frequency = pow(2, (double)(pianoKey-69)/12) * 440;
	startBeat = (double)event.tick / ticksPerQuarterNote;
	beatDuration = (double)tickDuration / ticksPerQuarterNote;
}
