#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "sequencer.h"
#include "filters.h"
#include "fft.h"

int sig_caught = 0;

void signal_handler(int sig) {
	if(sig == SIGINT) 
	{
		sig_caught = 1;
	}
}

int do_something() {
	return 0;
}

int add_effects_main() {
	int state = 0;

	printf("\n");
	printf("Choose Effect:\n");
	
	printf("\n");
	printf("(1) Delay Line\n"
		   "(2) Feed-Forward Comb Filter\n"
		   "(3) Feed-Back Comb Filter\n"
		   "(4) All-Pass Comb Filter\n"
		   "(5) Shroeder Reverberator\n"
		   "(6) Convolution Reverb\n");

	printf("\n");
	printf("Enter number corresponding to effect: ");
	scanf("%X", &state);

	printf("\n");
	switch(state) {
		case 1:
			printf("You Chose The Delay Line\n");
			delay_line_main();
			break;
		case 2:
			printf("You Chose The Feed-Forward Comb Filter\n");
			ff_comb_filter_main();
			break;
		case 3:
			printf("You Chose The Feed-Back Comb Filter\n");
			fb_comb_filter_main();
			break;
		case 4:
			printf("You Chose The All-Pass Comb Filter\n");
			ap_comb_filter_main();
			break;
		case 5:
			printf("You Chose The Shroeder Reverberator\n");
			shroeder_reverberator_main();
			break;
		case 6:
			printf("You Chose The Convolution Reverb\n");
			convolution_reverb_main();
			break;
	}

	printf("\n");

	return 0;
}

int main() {

	if(signal(SIGINT, signal_handler) == SIG_ERR) 
	{ 
		fprintf(stderr, "signal func registration failed\n"); 
		return 1; 
	} 

	int command = 0;

	printf("\nCOMMANDS:\n");
	printf("1	- Load DEFAULT Samples:\n");
	printf("2	- Load WAV Samples:\n");
	printf("3	- Set Beat Per Minute:\n");
	printf("4	- Set Time Signature:\n");
	printf("5	- Set Number of Bars:\n");
	printf("6	- Set Resolution:\n");
	printf("7	- Set Sequence:\n");
	printf("8	- Add Effects:\n");
	printf("9	- Export to WAV:\n");
	printf("10	- Quit Program:\n");

	for(;;)	// Main Loop
	{

		if(sig_caught)
		{
			printf("\nCaught Signal --- Exiting\n");
			return 0;
		}
	
		printf("\n");
		printf("Enter Command: ");
		scanf("%d", &command);
	
		printf("\n");
		switch(command) {
			case 1:	// load default samples
				printf("You Chose Command #%d - Load DEFAULT Samples\n", command);
				load_default_samples();
				break;
			case 2:	// load wav samples
				printf("You Chose Command #%d - Load WAV Samples\n", command);
				load_samples();
				break;
			case 3:	// set beats per minute
				printf("You Chose Command #%d - Set BPM\n", command);
				set_bpm();
				break;
			case 4:	// set time signature 
				printf("You Chose Command #%d - Set Time Sig\n", command);
				set_time_sig();
				break;
			case 5:	// set number of bars 
				printf("You Chose Command #%d - Set Number of Bars\n", command);
				set_num_bars();
				break;
			case 6:	// set resolution
				printf("You Chose Command #%d - Set Resolution\n", command);
				set_resolution();
				break;
			case 7: // set sequence
				printf("You Chose Command #%d - Set Sequence\n", command);
				set_sequence();
				break;
			case 8:	// add effects
				printf("You Chose Command #%d - Add Effects\n", command);
				add_effects_main();
				break;
			case 9:	// export to WAV
				printf("You Chose Command #%d - Export to WAV\n", command);
				export_to_wav();
				break;
			case 10:	// quit program
				printf("You Chose Command #%d - Quit Program\n", command);
				return 0;
				break;
		}
	
	}

	return 0;
}
