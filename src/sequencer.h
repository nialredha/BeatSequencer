#ifndef SEQUENCER_H_
#define SEQUENCER_H_

/*	Provides basic functions for creating a sequenced audio file with 
	user-inputed samples.
*/

#include <stdint.h>
#include <stdio.h>

void load_default_samples();	// Load Default Samples (kick, hihat, snare)
void load_samples();			// Load Samples
void set_bpm();					// Set BPM
void set_num_bars();			// Set Num Bars
void set_time_sig();			// Set Time Sig 
void set_resolution();			// Set Resolution
void set_sequence();			// Set Sequence
void export_to_wav();			// Export to WAV

#endif // SEQUENCER_H_
