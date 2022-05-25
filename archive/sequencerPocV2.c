#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

#define NL printf("\n")

int main() {

	// initialize struct containing input data header info and pointer to 
	// input data
	struct wav_info kick;
	struct wav_info hihat;
	struct wav_info snare;
	
	// TODO: Edit retrieve_data to accept a file dir so that I don't have to
	//		 input the relatiove dirs everytime while I am testing code
	printf("Let's Load Some Sounds\n");
	printf("--------------------------------\n");
	printf("Enter Relative Path To Kick WAV:");
	float *kickData = retrieve_data(&kick);
	printf("Enter Relative Path To HiHat WAV:");
	float *hihatData = retrieve_data(&hihat);
	printf("Enter Relative Path To Snare WAV:");
	float *snareData = retrieve_data(&snare);

	// so.. get beats per minute into bars per minute, then multiply by the 
	// amount of bars, then multiply by 60 to get it into seconds

	// 4 beats/bar / 60 beats/minute = 1/15 minutes/bar
	// 1/15 minutes/bar * 16 bars = 16/15 minutes 
	// 16/15 minutes * 60 seconds/minute = 64 seconds

	// Now we know how to compute total time, but does that really matter?
	// Number of samples and the sample rate will drive the time anyways..
	// We need to find the amount of time OR really the number of samples in
	// between each beat..

	// If you know the total time and total beats then divide? So...
	// 64 seconds/64 beats is 1 second per beat


	// Let's try this for 5 beats/bar / 83 beats/minute = 5/83 minutes/bar
	// 5/83 minutes/bar * 16 bars = 80/83 minutes
	// SKIP THIS: 80/83 minutes * 60 seconds/minute = ~57.83 seconds
	// 80/83 seconds / 80 beats = 1/83 second per beat

	int num_bars = 0;	// total number of bars
	int time_sig = 0;	// beats per bar
	int bpm = 0;		// beats per minute

	// user input the number of steps they want in the sequence 
	NL;
	printf("Enter Number of Bars: ");
	scanf("%d", &num_bars); 
	NL;
	printf("Enter Time Signature: ");
	scanf("%d", &time_sig); 
	NL;
	printf("Enter BPM: ");
	scanf("%d", &bpm); 
	NL;
	printf("You Chose %d bars at a %d beats/bar time signature and %d bpm!\n", num_bars, time_sig, bpm);

	float min_per_beat = 1.0 / (float)bpm;
	float sec_per_beat = min_per_beat * 60.0;

	int num_beats = num_bars * time_sig;
	float duration = min_per_beat * (float)num_beats * 60.0;

	int sequence[num_beats];

	int num_kicks = 0, num_hihats = 0, num_snares = 0;

	NL;
	for(int i = 0; i < time_sig; i++)
	{
		printf("Enter Sample For Index %d: ", i);
		scanf("%d", &sequence[i]);

		if(sequence[i] == 0) { num_kicks++; }

		else if(sequence[i] == 1) { num_hihats++; }

		else if(sequence[i] == 2) { num_snares++; }

		// need to write something better than this, I'm just lazy.
		else { printf("ERROR ----------\n"); return 1; }

	}

	for(int bar=1; bar<num_bars; bar++)
	{
		for(int i = time_sig*bar; i < time_sig*(bar+1); i++)
		{
			sequence[i] = sequence[i-(time_sig*bar)];

			if(sequence[i] == 0) { num_kicks++; }

			else if(sequence[i] == 1) { num_hihats++; }
	
			else if(sequence[i] == 2) { num_snares++; }
		}
	}
	
	// initialize struct for output file to store basic info
	struct wav_info output;

	// set output .wav parameters
    output.num_channels = kick.num_channels;		
    output.bits_per_sample = kick.bits_per_sample;
    output.sample_rate = kick.sample_rate; 
    output.num_samples = (int)((float)output.sample_rate * duration);

	int samples_per_beat = (int)(sec_per_beat * (float)output.sample_rate);

	// Example: 5  beats/bar at 83 beats/minute
	// 5 beats/bar / 83 beats/minute = 5/83 minutes/bar
	// 5/83 minutes/bar * 16 bars = 80/83 minutes
	// SKIP THIS: 80/83 minutes * 60 seconds/minute = ~57.83 seconds
	// 80/83 seconds / 80 beats = 1/83 second per beat

	// float min_per_bar = (float)time_sig / (float)bpm;
	// float duration = min_per_bar * (float)num_bars * 60.0;	// time in sec

	// float min_per_beat = (min_per_bar * (float)num_bars) / (float)num_beats;
	// float sec_per_beat = min_per_beat * 60.0;

	/*
	NL;
	printf("%d Number of Beats\n", num_beats);
	printf("%f Duration\n", duration);
	printf("%d Number of Samples\n", output.num_samples);
	printf("%f Minutes per Beat\n", min_per_beat);
	printf("%f Seconds per Beat\n", sec_per_beat);
	printf("%d Samples per Beat\n", samples_per_beat);
	NL;
	*/

	float *outputData = (float *)malloc(sizeof(float)*(output.num_samples*output.num_channels));
	if(outputData == NULL) { return 0; }

	int outputDataPtr = 0;
	int temp;

	NL;
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

					temp = n;	
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

					temp = n;
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

					temp = n;
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

	NL;
	printf("Number of Samples = %d\n", outputDataPtr);

/*
	for (int c=0; c<output.num_channels; c++)
	{
		for(int i=1; i<num_loops; i++)
		{
			// memcpy - first input is the destination, second is the source
			//			and third is the number of bytes. 
			//			2-Channel WAV, so have to copy and paste memory to the
			//			first-half and second-half of the 1D array. The number
			//			of bytes is equal to 4 times the number of samples, 
			//			since a floating point number is 4 bytes.
			memcpy(&outputData[outputDataPtr*i + output.num_samples*c], &outputData[0 + output.num_samples*c], outputDataPtr*4);
		}
	}
*/

	printf("\n");
	printf("Enter relative file path to delayed .wav file: ");
	create_file_write_data(&output, outputData);

	free(outputData);

	return 0;
}

