#include "midinote.h"

MidiNote::MidiNote()
{

}

MidiNote::MidiNote(int new_val, double new_duration)
{
    value = new_val;
    duration = new_duration;
}
