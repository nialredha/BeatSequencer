#include <stdio.h>
#include <stdlib.h>

#include "sequencer.h"
#include "wav.h"

// Load WAV Samples 
// ----------------
// Where should the data be? I do not know... 
// One long array? And pointers to the start of each set of data? Probably
// the way to go. 

// For now, the sequencer will default load a kick, hihat and snare - still 
// need to figure out how to handle not knowing the amount and type of sounds
// that will be loaded. I think one long array is how this will be possible. 

// Let's think about this. I could have the "Load WAV Samples" command load 
// a new sample onto an array... wait isn't there a data type for this?

// I guess there are a lot of options to choose from here...
// I need to be able to append large amounts of data and easily access them.  

// I don't know the answer right now. I need to make a bad implementation so 
// I can get a better look at what I am even trying to do. 

wav_info kick;
wav_info hihat;
wav_info snare;

float *kickData, *hihatData, *snareData;

int num_bars = 16;	// total number of bars
int time_sig = 4;	// beats per bar
int num_beats = 64;	// total number of beats (num_bars * time_sig)
int bpm = 240;		// beats per minute
int resolution = 1;	// number of beats between each beat

int *sequence;

void load_default_samples() {
	
	// TODO: Edit retrieve_data to accept a file dir so that I don't have to
	//		 input the relatiove dirs everytime while I am testing code

	printf("\nLet's Load Some Sounds\n");
	printf("--------------------------------\n");

    char* file_path = "samples/kick.wav";
	kickData = retrieve_data(&kick, file_path);
	printf("From here on out, the kick = 0\n");

    char* file_path_2 = "samples/hihat.wav";
	hihatData = retrieve_data(&hihat, file_path_2);
	printf("From here on out, the hihat = 1\n");

    char* file_path_3 = "samples/snare.wav";
	snareData = retrieve_data(&snare, file_path_3);
	printf("From here on out, the snare = 2\n");

}

void load_samples() {
	
	// TODO: Edit retrieve_data to accept a file dir so that I don't have to
	//		 input the relatiove dirs everytime while I am testing code

	printf("\nLet's Load Some Sounds\n");
	printf("--------------------------------\n");

	printf("\n");
	printf("Enter Relative Path To Sample 0: ");
    char file_path[1000];
	scanf("%s", file_path); 
	kickData = retrieve_data(&kick, file_path);
	printf("From here on out, Sample 0 = 0\n");

	printf("\n");
	printf("Enter Relative Path To Sample 1: ");
    char file_path_2[1000];
	scanf("%s", file_path_2); 
	hihatData = retrieve_data(&hihat, file_path_2);
	printf("From here on out, Sample 1 = 1\n");

	printf("\n");
	printf("Enter Relative Path To Sample 2: ");
    char file_path_3[1000];
	scanf("%s", file_path_3); 
	snareData = retrieve_data(&snare, file_path_3);
	printf("From here on out, Sample 2 = 2\n");

}

// Set BPM
void set_bpm() {

	printf("\n");
	printf("Enter BPM: ");
	scanf("%d", &bpm); 
	printf("\n");

}

void set_time_sig() {
	
	printf("\n");
	printf("Enter Time Signature: ");
	scanf("%d", &time_sig); 

	num_beats = num_bars * time_sig;
}

void set_num_bars() {
	
	printf("\n");
	printf("Enter Number of Bars: ");
	scanf("%d", &num_bars); 

	num_beats = num_bars * time_sig;
}

void set_resolution() {
	
	printf("\n");
	printf("Enter Resolution: ");
	scanf("%d", &resolution);

}

// Set Sequence
void set_sequence() {

	sequence = (int *)malloc(sizeof(int) * num_beats);
	for(int i = 0; i < time_sig; i++)
	{
		printf("Enter Sample For Index %d: ", i);
		scanf("%d", &sequence[i]);
	}

	for(int bar=1; bar<num_bars; bar++)
	{
		for(int i = time_sig*bar; i < time_sig*(bar+1); i++)
		{
			sequence[i] = sequence[i-(time_sig*bar)];
		}
	}

}

// Export to WAV
void export_to_wav() {
	
	float min_per_beat = 1.0 / (float)bpm;
	float sec_per_beat = min_per_beat * 60.0;
	float duration = min_per_beat * (float)num_beats * 60.0;

	// initialize struct for output file to store basic info
	wav_info output;

	// set output .wav parameters
    output.num_channels = kick.num_channels;		
    output.bits_per_sample = kick.bits_per_sample;
    output.sample_rate = kick.sample_rate; 
    output.num_samples = (int)((float)output.sample_rate * duration);

	int samples_per_beat = (int)(sec_per_beat * (float)output.sample_rate);

	float *outputData = (float *)malloc(sizeof(float)*(output.num_samples*output.num_channels));
	if(outputData == NULL) { return; }

	int outputDataPtr = 0;

	printf("\n");
	for(int c=0; c<output.num_channels; c++)
	{
		for(int i=0; i<num_beats; i++)
		{
			if(sequence[i] == 0)	// Kick
			{
				for(int n=outputDataPtr; n<outputDataPtr+kick.num_samples; n++)
				{
					if(n>(i+1)*samples_per_beat)
					{
						break;
					}

					int nK = n - outputDataPtr;
					outputData[n + output.num_samples*c] = kickData[nK + kick.num_samples*c];
				}
				outputDataPtr = (i+1)*samples_per_beat;
				printf("KICK. Array Ptr Val = %d\n", outputDataPtr);
			}
			else if(sequence[i] == 1)	// HiHat
			{
				for(int n=outputDataPtr; n<outputDataPtr+hihat.num_samples; n++)
				{
					if(n>(i+1)*samples_per_beat)
					{
						break;
					}

					int nHH = n - outputDataPtr;
					outputData[n + output.num_samples*c] = hihatData[nHH + hihat.num_samples*c];
				}
				outputDataPtr = (i+1)*samples_per_beat;
				printf("HIHAT. Array Ptr Val = %d\n", outputDataPtr);
			}
			else if(sequence[i] == 2)	// Snare
			{
				for(int n=outputDataPtr; n<outputDataPtr+snare.num_samples; n++)
				{
					if(n>(i+1)*samples_per_beat)
					{
						break;
					}

					int nS = n - outputDataPtr;
					outputData[n + output.num_samples*c] = snareData[nS + snare.num_samples*c];
				}
				outputDataPtr = (i+1)*samples_per_beat;
				printf("SNARE. Array Ptr Val = %d\n", outputDataPtr);
			}
		}

		if((c+1) != output.num_channels)
		{
			outputDataPtr = 0;
		}
	}

	printf("\n");
	printf("Enter relative file path to output .wav file: ");
	create_file_write_data(&output, outputData);

	free(outputData);

}
