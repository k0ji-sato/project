//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>


#define SIZE 128

FILE *fp;

typedef struct {
	double r, i;
}complex;

complex complex_add(complex z1, complex z2)		//z1 + z2
{
	complex tmp;
	tmp.r = z1.r + z2.r;
	tmp.i = z1.i + z2.i;
	return tmp;
}

complex complex_sub(complex z1, complex z2)		//z1 - z2
{
	complex tmp;
	tmp.r = z1.r - z2.r;
	tmp.i = z1.i - z2.i;
	return tmp;
}

complex complex_mul(complex z1, complex z2)		//z1 * z2
{
	complex tmp;
	tmp.r = z1.r * z2.r - z1.i * z2.i;
	tmp.i = z1.r * z2.i + z1.i * z2.r;
	return tmp;
}

complex complex_div(complex z1, complex z2)		//z1 / z2
{
	complex tmp;
	double den;
	den = z2.r * z2.r + z2.i * z2.i;

	if (den == 0) {
		printf("Fatal Error: divided by zero\n");
		exit(1);
	}

	tmp.r = (z1.r * z2.r + z1.i * z2.i) / den;
	tmp.i = (z2.r * z1.i - z1.r * z2.i) / den;
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
	complex tmp[SIZE];
	complex cpyx[SIZE];
	complex rootN;

	rootN.r = sqrt(N);
	rootN.i = 0;

	for (int i = 0; i < N; i++)
	{
		cpyx[i].r = x[i].r;
		cpyx[i].i = x[i].i;
		x[i].r = 0;
		x[i].i = 0;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tmp[j] = complex_mul(cpyx[j], complex_jexp((-1 * 2 * M_PI * fft_mode * i * j) / N));
			x[i] = complex_add(x[i], tmp[j]);
		}
		x[i] = complex_div(x[i], rootN);
	}

}

void fft(complex *x, long N, int fft_mode)
{
	complex *fe = (complex *)malloc(sizeof(complex)*N);
	complex *fo = (complex *)malloc(sizeof(complex)*N);
	complex root2;
	complex tmp;


	//??????????//
	root2.r = sqrt(2);
	root2.i = 0;

	if (N > 2)
	{
		for (int i = 0; i < N / 2; i++)
		{
			fe[i].r = x[2 * i].r;
			fe[i].i = x[2 * i].i;

			fo[i].r = x[(2 * i) + 1].r;
			fo[i].i = x[(2 * i) + 1].i;
		}

		fft(fe, N / 2, fft_mode);
		fft(fo, N / 2, fft_mode);

		for (int i = 0; i < N / 2; i++)
		{
			x[i] = complex_div(complex_add(fe[i], complex_mul(complex_jexp((fft_mode * (-1) * 2 * M_PI * i) / N), fo[i])), root2);
			x[(N / 2) + i] = complex_div(complex_add(fe[i], complex_mul(complex_jexp((fft_mode * (-1) * 2 * M_PI * ((N / 2) + i)) / N), fo[i])), root2);
		}

	}
	else
	{
		tmp = x[0];
		x[0] = complex_div(complex_add(x[0], complex_mul(complex_jexp((fft_mode * (-1) * 2 * M_PI * 0) / 2), x[1])), root2);
		x[1] = complex_div(complex_add(tmp, complex_mul(complex_jexp((fft_mode * (-1) * 2 * M_PI * 1) / 2), x[1])), root2);
	}

	free(fe);
	free(fo);
}

void conv(complex *x, complex *y, complex *z, long N) {

	complex tmp;
	tmp.r = sqrt(N);
	tmp.i = 0;

	fft(x, N, 1);
	fft(y, N, 1);

	for (int i = 0; i < N; i++)
	{
		z[i] = complex_mul(complex_mul(x[i], y[i]),tmp);
	}

	fft(z, N, -1);

	/*for (int i = 0; i < N; i++)
	{
		printf("F[%d] = %f	%f\n", i, z[i].r, z[i].i);
		fprintf(fp,"F[%d],%f,%f\n",i, z[i].r, z[i].i);
	}*/

}

void corr(complex *x,complex *y, complex *z, long N) {

	complex tmp;
	tmp.r = N;
	tmp.i = 0;

	complex t[SIZE];

	for (int i = 0; i < N; i++)
	{
		t[i].r = y[N-i-1].r;
		t[i].i = -y[N-i-1].i;
	}

	conv(x, t, z, N);

	for (int i = 0; i < N; i++)
	{
		z[i] = complex_div(z[i], tmp);
	}

	for (int i = 0; i < N; i++)
	{
		printf("F[%d] = %f	%f\n", i, z[i].r, z[i].i);
		fprintf(fp,"F[%d],%f,%f\n", i, z[i].r, z[i].i);
	}
}

void espectl(complex *x, double *y, long N) {

	fft(x, N, 1);
	for (int i = 0; i < N; i++)
	{
		y[i] = (x[i].r * x[i].r) + (x[i].i * x[i].i);
	}
	/*for (int i = 0; i < SIZE; i++)
	{
		printf("F[%d] = %f\n",i, y[i]);
		fprintf(fp,"%f\n", y[i]);
	}*/
}

void t_pow(complex *x, long N) {

	double tmp = 0.0;

	for (int i = 0; i < N; i++)
	{
		tmp += (x[i].r * x[i].r) + (x[i].i * x[i].i);
	}
	printf("?G?l???M?[ = %f\n",tmp);
}

void e_pow(double *x, long N) {
	double tmp = 0.0;

	for (int i = 0; i < N; i++)
	{
		tmp += x[i];
	}
	
	printf("?G?l???M?[ = %f\n", tmp);
}

void pspectl(complex *x, double *y, long N) {

	fft(x, N, 1);

	/*for (int i = 0; i < N; i++)
	{
		y[i] = (x[i].r * x[i].r) + (x[i].i * x[i].i);
		y[i] = y[i] / N;
		printf("P[%d] =	%f\n", i,y[i]);
		fprintf(fp,"%f\n",y[i]);
	}*/
}

void pspectl2(complex *x, double *y, long N) {
	
	complex tmp[SIZE];

	corr(x, x, tmp, SIZE);
	fft(tmp, SIZE, 1);
	for (int i = 0; i < SIZE; i++)
	{
		tmp[i].r = tmp[i].r / sqrt(SIZE);
		tmp[i].i = tmp[i].i / sqrt(SIZE);
		y[i] = sqrt((tmp[i].r * tmp[i].r) + (tmp[i].i * tmp[i].i));
		printf("P[%d] =	%f\n",i, y[i]);
		fprintf(fp,"%f\n",y[i]);
	}
}

int main(void)
{
	
	fp = fopen("d_data.csv","w");

	//data?????
	complex data[SIZE], data1[SIZE], data2[SIZE], result[SIZE];
	double espctl[SIZE], pspctl[SIZE];

	for (int i = 0; i < SIZE; i++) {
		if (i < SIZE/4)
		{
			data1[i].r = 1;
			data1[i].i = 0;
		}
		else
		{
			data1[i].r = 0;
			data1[i].i = 0;
		}

		if (SIZE/4 <= i && i < SIZE/2)
		{
			data2[i].r = 1;
			data2[i].i = 0;
		}
		else
		{
			data2[i].r = 0;
			data2[i].i = 0;
		}

		result[i].r = 0;
		result[i].i = 0;

		data[i].r = sin(2 * M_PI * i / SIZE);
		data[i].i = 0;
		
	}

	//dft(data, SIZE, 1);				//DFT
	//dft(data, SIZE, -1);				//IDFT
	//fft(data, SIZE, 1);				//FFT
	//fft(data, SIZE, -1);				//IFFT

	//conv(data1, data2, result, SIZE);	//??????v?Z
	//corr(data1, data1, result, SIZE);	//??????
	espectl(data, espctl, SIZE);		//?G?l???M?[?X?y?N?g??
	e_pow(espctl, SIZE);				//?G?l???M?[from?G?l???M?[?X?y?N?g??
	//t_pow(data1, SIZE);				//?G?l???M?[from??????
	//pspectl(data1, pspctl, SIZE);		//?d??X?y?N?g??
	//pspectl2(data1, pspctl, SIZE);		//?d??X?y?N?g??from??????

	fclose(fp);

	return 0;
}
