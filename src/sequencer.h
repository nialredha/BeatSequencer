#ifndef SEQUENCER_H_
#define SEQUENCER_H_

/*	Provides basic functions for creating a sequenced audio file with 
	user-inputed samples.
*/

#include <stdint.h>
#include <stdio.h>

#define DEFAULT_BPM 240			// beats per minute
#define DEFAULT_TIME_SIG 4		// beats per bar
#define DEFAULT_NUM_BARS 16		// total number of bars
#define DEFAULT_NUM_BEATS 64	// total number of beats (num_bars*time_sig)
#define DEFAULT_RESOLUTION 0	// number of beats between each beat

void load_default_samples();	// Load Default Samples (kick, hihat, snare)
void load_samples();			// Load Samples
void set_bpm();					// Set BPM
void set_num_bars();			// Set Num Bars
void set_time_sig();			// Set Time Sig 
void set_resolution();			// Set Resolution
void set_sequence();			// Set Sequence
void export_to_wav();			// Export to WAV

#endif // SEQUENCER_H_
