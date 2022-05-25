#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

#define NL printf("\n")

/* Brainstorm:
1. User define number of steps in beat and the number of loops
2. User define the sequence (for now only one sound can be on at a time)
	a. Later I can make it so you define the sequence for each instrument
		and then sum the waves 
3. Then Write it to a WAV file, simple right?


Currently, using the duration of each sample to drive the BPM, but I will
need to figure out how that is going to work.
*/

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

	int num_steps = 0;
	int num_loops = 0;

	// user input the number of steps they want in the sequence 
	NL;
	printf("Enter # of Sequence Steps: ");
	scanf("%d", &num_steps); 
	printf("Enter # of Sequence Loops: ");
	scanf("%d", &num_loops); 
	NL;
	printf("You Chose a %d-step sequence looped %d times\n", num_steps, num_loops);

	int sequence[num_steps];

	int num_kicks = 0, num_hihats = 0, num_snares = 0;

	for(int i = 0; i < num_steps; i++)
	{
		printf("Enter Sample For Index %d: ", i);
		scanf("%d", &sequence[i]);

		if(sequence[i] == 0) { num_kicks++; }

		else if(sequence[i] == 1) { num_hihats++; }

		else if(sequence[i] == 2) { num_snares++; }

		else { printf("ERROR ----------\n"); return 1; }

	}

	// initialize struct for output file to store basic info
	struct wav_info output;

	// set output .wav parameters
    output.num_channels = kick.num_channels;		
    output.bits_per_sample = kick.bits_per_sample;
    output.sample_rate = kick.sample_rate; 
    output.num_samples = num_loops*(
						 num_kicks*kick.num_samples + 
						 num_hihats*hihat.num_samples +
						 num_snares*snare.num_samples);

	NL;
	printf("Number of Samples = %d\n", output.num_samples / num_loops);

	float *outputData = (float *)malloc(sizeof(float)*(output.num_samples*output.num_channels));
	if(outputData == NULL) { return 0; }

	int outputDataPtr = 0;
	int temp;

	for(int c=0; c<output.num_channels; c++) 
	{
		for(int i=0; i<num_steps; i++)
		{
			if(sequence[i] == 0)	// Kick
			{
				for(int n=outputDataPtr; n<outputDataPtr+kick.num_samples; n++)
				{
					int nK = n - outputDataPtr;
					outputData[n + output.num_samples*c] = kickData[nK + kick.num_samples*c];

					temp = n;	
				}
				outputDataPtr = temp+1;
			}
			else if(sequence[i] == 1)	// HiHat
			{
				for(int n=outputDataPtr; n<outputDataPtr+hihat.num_samples; n++)
				{
					int nHH = n - outputDataPtr;
					outputData[n + output.num_samples*c] = hihatData[nHH + hihat.num_samples*c];

					temp = n;
				}
				outputDataPtr = temp+1;
			}
			else if(sequence[i] == 2)	// Snare
			{
				for(int n=outputDataPtr; n<outputDataPtr+snare.num_samples; n++)
				{
					int nS = n - outputDataPtr;
					outputData[n + output.num_samples*c] = snareData[nS + snare.num_samples*c];

					temp = n;
				}
				outputDataPtr = temp+1;
			}
		}

		if((c+1) != output.num_channels)
		{
			outputDataPtr = 0;
		}
	}

	NL;
	printf("Number of Samples = %d\n", outputDataPtr);

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

	printf("\n");
	printf("Enter relative file path to delayed .wav file: ");
	create_file_write_data(&output, outputData);

	free(outputData);

	return 0;
}

