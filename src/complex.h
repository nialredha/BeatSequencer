#ifndef COMPLEX_H_	// include guard
#define COMPLEX_H_

/*	Holds my own complex data type and any complex operations I 
	end up needing.
*/

typedef struct Complex
{
	float* r;	// real component
	float* i;	// imaginary component
} Complex;

void complex_multiply(Complex *a, Complex *b, Complex *o, int length);

#endif // COMPLEX_H_
