#ifndef FFT_H_	// include guard
#define FFT_H_

#include "complex.h"

/* Contains basic DFT, FFT, and IFFT. Supports both real and complex inputs
   but only floating point. 
*/ 

// Function Declarations 

int	reverse_bits(int num);
/* Given a number, reverse the bits. Uses log(N) to determine how many bits
   there are. */

void dft(float* data, float* amp, int N);
/* Compute the discrete fourier transform using real input data. */

void cdft(Complex *input,  Complex *output, int N);	
/* Compute the discrete fourier transform using complex input and
   output data. */

void fft(float* data, int N);
/* Compute the fast fourier transform, using the Radix-2 algorithm. Currently,
   it accepts real input data and re-writes the data buffer with the 
   transformed data. */

void cfft(Complex *input, Complex *output, int N);
/* Compute the fast fourier transform, using the Radix-2 algorithm. Currently,
   it accepts complex input data and writes the transformed data into output
   in complex form. This was originally created for the IFFT */

void ifft(Complex *input, Complex *output, int N);						
/* Compute the inverse fast fourier transform, using the feedforward fast 
   fourier transform. Accepts complex input data and writes the time-domain
   data into output in complex form. */

#endif // FFT_H_
