project: midiread.cpp
	g++ midiread.cpp MidiFile.cpp MidiFile.h MidiEvent.cpp MidiEvent.h MidiMessage.cpp MidiMessage.h MidiEventList.cpp MidiEventList.h Binasc.cpp Binasc.h --std=c++11 ;\
	rm *.gch
