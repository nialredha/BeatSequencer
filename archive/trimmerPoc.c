#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int main() {

	// initialize struct containing input data header info and pointer to 
	// input data
	wav_info sample;

	printf("Load Sample for Trimming\n");
	printf("---------------------------\n");
	printf("Enter Relative Path To WAV:");
	float *sampleData = retrieve_data(&sample);

	float trim_time;
	printf("Enter Trim Amount in Seconds: ");
	scanf("%f", &trim_time); 

	// convert the trim time to number of samples to trim
	int num_samples_to_trim = (float)sample.sample_rate * (float)trim_time;


	wav_info output;
	// set output .wav parameters
    output.num_channels = sample.num_channels;		
    output.bits_per_sample = sample.bits_per_sample;
    output.sample_rate = sample.sample_rate; 
    output.num_samples = sample.num_samples - num_samples_to_trim; 

	float *outputData = (float *)malloc(sizeof(float)*(output.num_samples*output.num_channels));

	for(int c=0; c<output.num_channels; c++) 
	{
		for(int n=0; n<output.num_samples; n++)
		{
			outputData[n + output.num_samples*c] = sampleData[n + sample.num_samples*c];
		}
	}
	
	printf("\n");
	printf("Enter relative file path to trimmed .wav file: ");
	create_file_write_data(&output, outputData);

	free(outputData);
}
