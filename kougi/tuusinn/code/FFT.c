//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	double r,i;
} complex;

complex complex_add(complex z1, complex z2)
{
	complex tmp;
	tmp.r = z1.r + z2.r;
	tmp.i = z1.i + z2.i;
	return tmp;
}

complex complex_sub(complex z1, complex z2)
{
	complex tmp;
	tmp.r = z1.r - z2.r;
	tmp.i = z1.i - z2.i;
	return tmp;
}

complex complex_mul(complex z1, complex z2)
{
	complex tmp;
	tmp.r = z1.r * z2.r - z1.i * z2.i;
	tmp.i = z1.i * z2.r + z1.r * z2.i;
	return tmp;
}

complex complex_div(complex z1, complex z2)
{
	complex tmp;
	double den;
	den = z2.r * z2.r + z2.i * z2.i;

	if (den == 0){
		printf("Fatal Error: divided by zero!\n");
		exit(1);
	}
	tmp.r = (z1.r*z2.r + z1.i* z2.i)/den;
	tmp.i = (z1.r*z2.i - z1.r* z2.i)/den;
	return tmp;
}

complex complex_jexp(double x)
{
	complex tmp;
	tmp.r = cos(x);
	tmp.i = sin(x);
	return tmp;
}

void dft(complex *x, long N, int fft_mode)
{

}

void fft(complex *x, long N,int fft_mode)
{

}

int main(void)
{
	complex z1,z2,z3;
	
	z1.r = 1;
	z1.i = 1;
	z2.r = 1;
	z2.i = 2;
	z3 = complex_add (z1,z2);
	printf("z1 + z2 = %f +j%f\n", z3.r,z3.i);

	return 0;
}
