#include <stdio.h>
#include <stdlib.h>

#include "sequencer.h"
#include "wav.h"

wav_info kick;
wav_info hihat;
wav_info snare;

float *kickData, *hihatData, *snareData;	// pointers to the 3 samples
int *sequence;	// pointer to the beat sequence

int bpm = DEFUALT_BPM;					// beats per minute
int time_sig = DEFAULT_TIME_SIG;		// beats per bar
int num_bars = DEFAULT_NUM_BARS;		// total number of bars
int num_beats = DEFUALT_NUM_BEATS;		// total number of beats
int resolution = DEFAULT_RESOLUTION;	// number of beats between each beat


void load_default_samples() {
	
	printf("\nLet's Load Some Sounds\n");
	printf("--------------------------------\n");

    char* file_path = "../samples/kick.wav";
	kickData = retrieve_data(&kick, file_path);
	printf("From here on out, the kick = 0\n");

    char* file_path_2 = "../samples/hihat.wav";
	hihatData = retrieve_data(&hihat, file_path_2);
	printf("From here on out, the hihat = 1\n");

    char* file_path_3 = "../samples/snare.wav";
	snareData = retrieve_data(&snare, file_path_3);
	printf("From here on out, the snare = 2\n");

}

void load_samples() {
	
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


	if (kick.num_channels != hihat.num_channels ||
		kick.num_channels != snare.num_channels ||
		hihat.num_channels != snare.num_channels) 
	{
		printf("\n");
		printf("Some samples are mono and some are stereo...\n");
		printf("Exiting Program...\n\n");
		exit(0);
	}

}

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

	// allocate memory for the beat sequence
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
