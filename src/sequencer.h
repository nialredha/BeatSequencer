#ifndef SEQUENCER_H_
#define SEQUENCER_H_

#include <stdint.h>
#include <stdio.h>

// Load Default Samples (kick, hihat, snare)
void load_default_samples();

// Load Samples
void load_samples();

// Set BPM
void set_bpm();

// Set Num Bars
void set_num_bars();

// Set Time Sig 
void set_time_sig();

// Set Resolution
void set_resolution();

// Set Sequence
void set_sequence();

// Export to WAV
void export_to_wav();

#endif // SEQUENCER_H_
