#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <string>
#include <fstream>

#define M 1024 
#define PI 3.14159265359

typedef struct {
	double r, i;
} complex;

complex complex_add(complex z1, complex z2){
	complex tmp;
	tmp.r = z1.r + z2.r;
	tmp.i = z1.i + z2.i;
	return tmp;
}

complex complex_sub(complex z1, complex z2){
	complex tmp;
	tmp.r = z1.r - z2.r;
	tmp.i = z1.i - z2.i;
	return tmp;
}

complex complex_mul(complex z1, complex z2){
	complex tmp;
	tmp.r = z1.r * z2.r - z1.i * z2.i;
	tmp.i = z1.r * z2.i + z1.i * z2.r;
	return tmp;
}

complex complex_div(complex z1, complex z2){
	complex tmp;
	double den;
	den = z2.r * z2.r + z2.i * z2.i;

	if (den == 0.0){
		printf("Fatal error: divided by zero!\n");
		exit(1);
	}
	tmp.r = (z1.r * z2.r + z1.i * z2.i) / den;
	tmp.i = (z2.r * z1.i - z1.r * z2.i) / den;
	return tmp;
}

complex complex_jexp(double x){
	complex tmp;
	tmp.r = cos(x);
	tmp.i = sin(x);
	return tmp;
}

void show_f(complex *f, long N){
	int i;
	for (i = 0; i < N; i++){
		printf("f[%d] = %f + j%f\n", i, f->r, f->i);
		f++;
	}
	return;
}

void output(std::string path, complex *x, long N){
	std::ofstream ofs(path);

	for (int i = 0; i < N; i++){
		ofs << (float)x[i].r << "\t" << (float)x[i].i << '\n';
	}
}

void dft(complex *x, long N, int dft_mode){
	int i;
	int a, b;

	complex w;
	complex tmp;
	complex *x_tmp;

	if (N == 0){
		printf("Fatal error: divided by zero!\n");
		exit(1);
	}

	x_tmp = (complex*)malloc(sizeof(complex) * N);

	for (i = 0; i < N; i++){
		x_tmp[i] = x[i];
		x[i].r = 0;
		x[i].i = 0;
	}

	for (a = 0; a < N; a++){
		tmp.r = 0;
		tmp.i = 0;

		for (b = 0; b < N; b++){
			if (dft_mode == 0){
				w = complex_jexp(-2 * a * b * PI / N);
			}
			else{
				w = complex_jexp(2 * a * b * PI / N);
			}

			tmp = complex_mul(x_tmp[b], w);
			x[a] = complex_add(x[a], tmp);
		}

		tmp.r = sqrt((double)N);
		tmp.i = 0;

		x[a] = complex_div(x[a], tmp);
	}
}

void fft(complex *x, long N, int fft_mode){
	complex *x_e, *x_q;
	complex w, w_0, w_1;
	complex x_tmp;
	complex root2;

	int i;

	if (N % 2 == 1){
		printf("FFT error.\n");
		exit(1);
	}

	root2.r = sqrt(2.0);
	root2.i = 0;

	if (N > 2){
		x_e = (complex*)malloc(sizeof(complex)* N / 2);
		x_q = (complex*)malloc(sizeof(complex)* N / 2);

		for (i = 0; i < N / 2; i++){
			x_e[i] = x[i * 2];
			x_q[i] = x[i * 2 + 1];
		}

		fft(x_e, N / 2, fft_mode);
		fft(x_q, N / 2, fft_mode);

		for (i = 0; i < N / 2; i++){
			if (fft_mode == 0){
				w = complex_jexp(-2 * i * PI / N);
			}
			else{
				w = complex_jexp(2 * i * PI / N);
			}

			x[i] = complex_div(complex_add(x_e[i], complex_mul(w, x_q[i])), root2);
		}
		for (i = N / 2; i < N; i++){
			if (fft_mode == 0){
				w = complex_jexp(-2 * i * PI / N);
			}
			else{
				w = complex_jexp(2 * i * PI / N);
			}

			x[i] = complex_div(complex_add(x_e[i - N / 2], complex_mul(w, x_q[i - N / 2])), root2);
		}
	}
	else {
		w_0 = complex_jexp(0);
		if (fft_mode == 0){
			w_1 = complex_jexp(-1 * PI);
		}
		else{
			w_1 = complex_jexp(PI);
		}

		x_tmp = x[0];
		x[0] = complex_div(complex_add(x[0], complex_mul(w_0, x[1])), root2);
		x[1] = complex_div(complex_add(x_tmp, complex_mul(w_1, x[1])), root2);
	}
}

int main(int argc, char* argv[]){
	long N = M;
	complex f[M], f_d[M], f_f[M];
	complex g[M], g_d[M], g_f[M];
	complex fg[M];
	
	complex z1,z2,ans;
	int i;
	std::chrono::system_clock::time_point start, end;

	z1.r = 2;
	z1.i = 1;
	z2.r = 1;
	z2.i = 2;
	
	ans = complex_add(z1,z2);
	printf("complex_add\n");
	printf("%lf+j%lf + %lf+j%lf = %lf+j%lf\n", z1.r, z1.i, z2.r, z2.i, ans.r, ans.i);
	ans = complex_sub(z1,z2);
	printf("complex_sub\n");
	printf("%lf+j%lf - %lf+j%lf = %lf+j%lf\n", z1.r, z1.i, z2.r, z2.i, ans.r, ans.i);
	ans = complex_mul(z1,z2);
	printf("complex_mul\n");
	printf("%lf+j%lf × %lf+j%lf = %lf+j%lf\n", z1.r, z1.i, z2.r, z2.i, ans.r, ans.i);
	ans = complex_div(z1,z2);
	printf("complex_div\n");
	printf("%lf+j%lf ÷ %lf+j%lf = %lf+j%lf\n", z1.r, z1.i, z2.r, z2.i, ans.r, ans.i);
	




	for (i = 0; i < N; i++){
		f[i].r = cos(2 * i * PI / N);
		f[i].i = cos((2 * i * PI / N) + PI);

		g[i].r = sin(2 * i * PI / N);
		g[i].i = sin((2 * i * PI / N) + PI);

		f_d[i] = f[i];
		f_f[i] = f[i];
		g_d[i] = g[i];
		g_f[i] = g[i];
	}

	output("./data_f.txt", f, N);
	output("./data_g.txt", g, N);

	printf("DFT\n");
	start = std::chrono::system_clock::now();
	dft(f_d, N, 0);
	end = std::chrono::system_clock::now();
	printf("time = %d μsec\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
	output("./DFT.txt", f_d, N);
	
	printf("\nIDFT\n");
	start = std::chrono::system_clock::now();
	dft(f_d, N, 1);
	end = std::chrono::system_clock::now();
	printf("time = %d μsec\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
	output("./IDFT.txt", f_d, N);
	
	printf("\nFFT\n");
	start = std::chrono::system_clock::now();
	fft(f_f, N, 0);
	end = std::chrono::system_clock::now();
	printf("time = %d μsec\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
	output("./FFT.txt", f_f, N);

	printf("\nIFFT\n");
	start = std::chrono::system_clock::now();
	fft(f_f, N, 1);
	end = std::chrono::system_clock::now();
	printf("time = %d μsec\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
	output("./IFFT.txt", f_f, N);

	for (i = 0; i < N; i++){
		f_d[i] = f[i];
		f_f[i] = f[i];
	}

	printf("\nf*g DFT\n");
	start = std::chrono::system_clock::now();
	dft(f_d, N, 0);
	dft(g_d, N, 0);
	output("./fg_DFT_f.txt", f_d, N);
	output("./fg_DFT_g.txt", g_d, N);
	for (i = 0; i < N; i++){
		fg[i] = complex_mul(f_d[i], g_d[i]);
	}
	output("./fg_DFT.txt", fg, N);
	dft(fg, N, 1);
	end = std::chrono::system_clock::now();
	printf("time = %d μsec\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
	output("./fg_IDFT.txt", fg, N);

	printf("\nf*g FFT\n");
	start = std::chrono::system_clock::now();
	fft(f_f, N, 0);
	fft(g_f, N, 0);
	output("./fg_FFT_f.txt", f_f, N);
	output("./fg_FFT_g.txt", g_f, N);
	for (i = 0; i < N; i++){
		fg[i] = complex_mul(f_f[i], g_f[i]);
	}
	output("./fg_FFT.txt", fg, N);
	fft(fg, N, 1);
	end = std::chrono::system_clock::now();
	printf("time = %d μsec\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
	output("./fg_IFFT.txt", fg, N);

	printf("\nPress enter.\n");
	char press_enter;
	press_enter = getchar();

	return 0;
}
