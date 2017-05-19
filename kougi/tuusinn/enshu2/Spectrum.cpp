#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>

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
		complex xi;
		x[i].r < 0.000001 ? (xi.r = 0.0) : (xi.r = x[i].r);
		x[i].i < 0.000001 ? (xi.i = 0.0) : (xi.i = x[i].i);

		ofs << (float)xi.r << "\t" << (float)xi.i << '\n';
	}
}

void output_d(std::string path, double *x, long N){
	std::ofstream ofs(path);

	for (int i = 0; i < N; i++){
		double xi;
		x[i] < 0.000001 ? (xi = 0.0) : (xi = x[i]);

		ofs << (float)xi << '\n';
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

	x_tmp = (complex*)malloc(sizeof(complex)* N);

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

void conv(complex* x, complex* y, complex* z, long N){
	complex *x_tmp, *y_tmp;
	complex rootN;

	int i;

	rootN.r = sqrt(N);
	rootN.i = 0;

	x_tmp = (complex*)malloc(sizeof(complex)* N);
	y_tmp = (complex*)malloc(sizeof(complex)* N);

	for (i = 0; i < N; i++){
		x_tmp[i] = x[i];
		y_tmp[i] = y[i];
	}

	fft(x_tmp, N, 0);
	fft(y_tmp, N, 0);
	for (i = 0; i < N; i++){
		z[i] = complex_mul(rootN, complex_mul(x_tmp[i], y_tmp[i]));
	}
	fft(z, N, 1);
}

void corr(complex* x, complex* y, complex* z, long N){
	complex *y_tmp;
	complex N_complex;
	int i;

	N_complex.r = N;
	N_complex.i = 0;

	y_tmp = (complex*)malloc(sizeof(complex)* N);

	for (i = 0; i < N; i++){
		y_tmp[i].r = y[N - i - 1].r;
		y_tmp[i].i = -y[N - i - 1].i;
	}

	conv(x, y_tmp, z, N);
	for (i = 0; i < N; i++){
		z[i] = complex_div(z[i], N_complex);
	}
}

double energy(complex* x, long N){
	double e = 0.0;
	int i;

	for (i = 0; i < N; i++){
		e += x[i].r * x[i].r + x[i].i * x[i].i;
	}

	return e;
}

void energy_spectrum(complex* x, double* spectrum, long N){
	complex *x_tmp;
	int i;

	x_tmp = (complex*)malloc(sizeof(complex)* N);

	for (i = 0; i < N; i++){
		x_tmp[i] = x[i];
	}

	fft(x_tmp, N, 0);

	for (i = 0; i < N; i++){
		spectrum[i] = x_tmp[i].r * x_tmp[i].r + x_tmp[i].i * x_tmp[i].i;
	}
}

double energy_from_spectrum(double* x, long N){
	double e = 0.0;
	int i;

	for (i = 0; i < N; i++){
		e += x[i];
	}

	return e;
}

void power_spectrum_t(complex* x, double* spectrum, long N){
	complex *x_tmp;
	int i;

	x_tmp = (complex*)malloc(sizeof(complex)* N);

	for (i = 0; i < N; i++){
		x_tmp[i] = x[i];
	}

	fft(x_tmp, N, 0);

	for (i = 0; i < N; i++){
		spectrum[i] = (x_tmp[i].r * x_tmp[i].r + x_tmp[i].i * x_tmp[i].i) / (double)N;
	}
}

void power_spectrum_dft(complex* x, double* spectrum, long N){
	complex *x_tmp, *r_xx;
	int i;

	x_tmp = (complex*)malloc(sizeof(complex)* N);
	r_xx = (complex*)malloc(sizeof(complex)* N);

	for (i = 0; i < N; i++){
		x_tmp[i] = x[i];
	}

	corr(x_tmp, x_tmp, r_xx, N);

	fft(r_xx, N, 0);

	for (i = 0; i < N; i++){
		spectrum[i] = sqrt(r_xx[i].r * r_xx[i].r + r_xx[i].i * r_xx[i].i) / sqrt(N);
	}
}

int main(){
	long N = 128;
	complex x[128], y[128];
	complex z[128], r_xx[128], r_yy[128], r_xy[128];
	double e_spectrum[128];
	double p_spectrum_t[128], p_spectrum_dft[128];

	int i;

	for (i = 0; i < N / 4; i++){
		x[i].r = 1;
		x[i].i = 0;
		y[i].r = 0;
		y[i].i = 0;
	}
	for (i = N / 4; i < N / 2; i++){
		x[i].r = 0;
		x[i].i = 0;
		y[i].r = 1;
		y[i].i = 0;

	}
	for (i = N / 2; i < N; i++){
		x[i].r = 0;
		x[i].i = 0;
		y[i].r = 0;
		y[i].i = 0;
	}

	output("./data_x.txt", x, N);
	output("./data_y.txt", y, N);

	conv(x, y, z, N);
	output("./conv.txt", z, N);

	corr(x, x, r_xx, N);
	output("./corr_xx.txt", r_xx, N);
	corr(y, y, r_yy, N);
	output("./corr_yy.txt", r_yy, N);
	corr(x, y, r_xy, N);
	output("./corr_xy.txt", r_xy, N);

	printf("e_t = %f\n", energy(x, N));
	energy_spectrum(x, e_spectrum, N);
	output_d("./energy_spectrum.txt", e_spectrum, N);
	printf("e_f = %f\n", energy_from_spectrum(e_spectrum, N));

	power_spectrum_t(x, p_spectrum_t, N);
	output_d("./p_spectrum_t.txt", p_spectrum_t, N);
	power_spectrum_dft(x, p_spectrum_dft, N);
	output_d("./p_spectrum_dft.txt", p_spectrum_dft, N);

	printf("\nPress enter.\n");
	char press_enter;
	press_enter = getchar();

	return 0;
}
