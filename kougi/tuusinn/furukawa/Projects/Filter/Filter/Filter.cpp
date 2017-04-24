#include "stdafx.h"
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

void output(std::string path, complex *x, long N){
	std::ofstream ofs(path);

	for (int i = 0; i < N; i++){
		complex xi;
		(x[i].r < 0.000001 && x[i].r > -0.000001) ? (xi.r = 0.0) : (xi.r = x[i].r);
		(x[i].i < 0.000001 && x[i].i > -0.000001) ? (xi.i = 0.0) : (xi.i = x[i].i);

		ofs << (float)xi.r << "\t" << (float)xi.i << '\n';
	}
}

void output_s(std::string path, short *x, long N){
	std::ofstream ofs(path);

	for (int i = 0; i < N; i++){
		if (i % 16 == 15){
			ofs << x[i] << '\n';
		}
		else {
			ofs << x[i] << '\t';
		}
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

	free(x_tmp);
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

		free(x_e);
		free(x_q);
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

//**************************************************************************************
// Low Pass Filter:
void LowPassFilter(complex *x, unsigned long N, unsigned long threshold){
	unsigned long i;
	complex* h;

	h = (complex*)malloc(sizeof(complex)* N);
	for (i = 0; i < N; ++i){
		h[i].r = 0.0;
		h[i].i = 0.0;
	}

	for (i = 0; i < threshold; ++i){
		h[i].r = 1.0;
		h[i].i = 0.0;
	}
	for (i = N - 1; i > N - threshold; --i){
		h[i].r = 1.0;
		h[i].i = 0.0;
	}

	for (i = 0; i < N; ++i){
		x[i] = complex_mul(x[i], h[i]);
	}

	free(h);

	return;
}

//**************************************************************************************
// High Pass Filter: 
void HighPassFilter(complex *x, unsigned long N, unsigned long threshold){
	unsigned long i;
	complex* h;

	h = (complex*)malloc(sizeof(complex)* N);
	for (i = 0; i < N; ++i){
		h[i].r = 0.0;
		h[i].i = 0.0;
	}

	for (i = threshold; i < N / 2; ++i){
		h[i].r = 1.0;
		h[i].i = 0.0;
	}
	for (i = N - threshold; i >= N / 2; --i){
		h[i].r = 1.0;
		h[i].i = 0.0;
	}

	for (i = 0; i < N; ++i){
		x[i] = complex_mul(x[i], h[i]);
	}

	free(h);

	return;
}

//**************************************************************************************
// Band Pass Filter: 
void BandPassFilter(complex *x, unsigned long N, unsigned long threshold_l, unsigned long threshold_h){
	unsigned long i;
	complex* h;

	h = (complex*)malloc(sizeof(complex)* N);
	for (i = 0; i < N; ++i){
		h[i].r = 0.0;
		h[i].i = 0.0;
	}

	for (i = threshold_l; i < threshold_h; ++i){
		h[i].r = 1.0;
		h[i].i = 0.0;
	}
	for (i = N - threshold_l; i > N - threshold_h; --i){
		h[i].r = 1.0;
		h[i].i = 0.0;
	}

	for (i = 0; i < N; ++i){
		x[i] = complex_mul(x[i], h[i]);
	}

	free(h);

	return;
}

//**************************************************************************************
// Filter Interface: 
void PassFilterInterface(complex *x, unsigned long data_size, unsigned long f, unsigned long filter_degree, unsigned long sampling_degree, int filter, unsigned long f_threshold_l, unsigned long f_threshold_h){
	unsigned long loop_num;
	complex* processing_part;
	complex* original_x;

	unsigned long i, j;
	unsigned long adjuster;

	unsigned long threshold_l, threshold_h;

	//エラー回避
	if (filter_degree <= sampling_degree){
		printf("Parameter error.\n");
		exit(-1);
	}
	if (f <= f_threshold_h || f <= f_threshold_l || f_threshold_h < f_threshold_l){
		printf("Parameter error.\n");
		exit(-1);
	}

	i = filter_degree;
	while (true){
		if (i % 2 > 0){
			printf("Parameter error.\n");
			exit(-1);
		}
		else if (i / 2 == 1){
			break;
		}

		i = i / 2;
	}

	//領域準備
	processing_part = (complex*)malloc(sizeof(complex)* filter_degree);
	original_x = (complex*)malloc(sizeof(complex)* data_size);
	for (i = 0; i < data_size; ++i){
		original_x[i].r = x[i].r;
		original_x[i].i = x[i].i;
		x[i].r = 0.0;
		x[i].i = 0.0;
	}

	//切り出しと処理
	threshold_l = f_threshold_l * filter_degree / f;
	threshold_h = f_threshold_h * filter_degree / f;

	loop_num = data_size / sampling_degree;

	printf("(%lu): ", loop_num);
	for (i = 0; i <= loop_num; ++i){
		if (i % 100 == 0){
			printf("%lu,", i);
		}

		adjuster = (filter_degree - sampling_degree) / 2;

		for (j = 0; j < filter_degree; ++j){
			processing_part[j].r = 0.0;
			processing_part[j].i = 0.0;
		}
		for (j = 0; j < sampling_degree; ++j){
			if (i * sampling_degree + j >= data_size){
				break;
			}

			processing_part[j + adjuster].r = original_x[i * sampling_degree + j].r;
			processing_part[j + adjuster].i = original_x[i * sampling_degree + j].i;
		}

		if (i == 1000){
			output("./sample.txt", processing_part, filter_degree);
		}

		fft(processing_part, filter_degree, 0);

		if (i == 1000){
			output("./fft.txt", processing_part, filter_degree);
		}

		switch (filter){
		case 0:
			LowPassFilter(processing_part, filter_degree, threshold_l);
			break;
		case 1:
			HighPassFilter(processing_part, filter_degree, threshold_h);
			break;
		case 2:
			BandPassFilter(processing_part, filter_degree, threshold_l, threshold_h);
			break;
		default:
			break;
		}

		if (i == 1000){
			output("./filter.txt", processing_part, filter_degree);
		}

		fft(processing_part, filter_degree, 1);

		if (i == 1000){
			output("./ifft.txt", processing_part, filter_degree);
		}

		for (j = 0; j < filter_degree; ++j){
			if (i * sampling_degree + j - adjuster >= data_size){
				break;
			}
			else if (i * sampling_degree + j - adjuster < 0){
				continue;
			}

			x[i * sampling_degree + j - adjuster].r += processing_part[j].r;
			x[i * sampling_degree + j - adjuster].i += processing_part[j].i;
		}
	}
	printf("\n");

	free(processing_part);
	free(original_x);

	return;
}

//**************************************************************************************
// ファイルから４バイト読む
unsigned long get_ulong(FILE *fp)
{
	unsigned char s[4];

	if (fread(s, 4, 1, fp) != 1) {
		fprintf(stderr, "Read error\n");
		exit(1);
	}

	return s[0] + 256LU * (s[1] + 256LU * (s[2] + 256LU * s[3]));
}

//**************************************************************************************
// ファイルから２バイト読む
unsigned short get_ushort(FILE *fp){
	unsigned char s[2];

	if (fread(s, 2, 1, fp) != 1) {
		fprintf(stderr, "Read error\n");
		exit(1);
	}

	return s[0] + 256U * s[1];
}

//**************************************************************************************
// ファイルから符号付きで２バイト読む
short get_short(FILE *fp){
	unsigned char s[2];
	short tmp;

	if (fread(s, 2, 1, fp) != 1) {
		fprintf(stderr, "Read error\n");
		exit(1);
	}

	tmp = s[0] + 256U * s[1];
	if (tmp > 32767){
		tmp = ~(tmp - 1);
	}

	return tmp;
}

// Wave File fp_inのヘッダーを取り出して、fp_outに書き込む
void retrieve_header(FILE *fp_in, FILE *fp_out, unsigned long* f, unsigned long* data_size){
	int i, channels, bits;
	unsigned long len;
	unsigned char s[10];

	printf("\nRetrieving Wave File Header: \n\n");

	if (fread(s, 4, 1, fp_in) != 1) { // "RIFF"の読み書き
		printf("Read error\n");
		exit(1);
	}
	if (memcmp(s, "RIFF", 4) != 0) {
		printf("Not a 'RIFF' format\n");
		exit(1);
	}
	fwrite("RIFF", 4, 1, fp_out);

	len = get_ulong(fp_in);
	printf("[RIFF] (%lu bytes)\n", len);
	fwrite(&len, 4, 1, fp_out);

	if (fread(s, 8, 1, fp_in) != 1) { // "WAVEfmt "の読み書き
		printf("Read error\n");
		exit(1);
	}
	if (memcmp(s, "WAVEfmt ", 8) != 0) {
		printf("Not a 'WAVEfmt ' format\n");
		exit(1);
	}
	fwrite("WAVEfmt ", 8, 1, fp_out);

	len = get_ulong(fp_in); // 10 00 00 00 (16)を読み込書き
	printf("[WAVEfmt ] (%lu bytes)\n", len);
	if (len != 16) {
		printf("Length of 'WAVEfmt ' must be 16!\n");
		return;
	}
	fwrite(&len, 4, 1, fp_out);

	len = get_ushort(fp_in);
	printf("  Data type = %u (1 = PCM)\n", len);	// データ形式：PCM 01 00 を読み書き
	fwrite(&len, 2, 1, fp_out);

	channels = get_ushort(fp_in);					// チャンネル数を読み書き
	printf("  Number of channels = %u (1 = mono, 2 = stereo)\n", channels);
	fwrite(&channels, 2, 1, fp_out);

	len = get_ulong(fp_in);
	*f = len;
	printf("  Sampling rate = %luHz\n", len);		// Sampling Rate を読み書き
	fwrite(&len, 4, 1, fp_out);

	len = get_ulong(fp_in);
	printf("  Bytes / second = %lu\n", len);		// Bytes/Second を書き込む
	fwrite(&len, 4, 1, fp_out);

	len = get_ushort(fp_in);
	printf("  Bytes x channels = %u\n", len);		// Bytes x Channel を書き込む
	fwrite(&len, 2, 1, fp_out);

	bits = get_ushort(fp_in);						// Bits/Second を書き込む
	printf("  Bits / sample = %u\n", bits);
	fwrite(&bits, 2, 1, fp_out);


	// ファイルのフォーマットをチェックする: モノ、16ビット/サンプルだけ
	if ((channels != 1) || (bits != 16)) {
		printf("Wrong File Format!\n");
		exit(1);
	}

	while (fread(s, 4, 1, fp_in) == 1) {
		len = get_ulong(fp_in);
		s[4] = 0;
		printf("[%s] (%lu bytes)\n", s, len);
		if (memcmp(s, "data", 4) == 0){
			*data_size = len;
			break;
		}// "data" チャンクを探す
		for (i = 0; i < (int)len; i++)
			printf("%02x ", fgetc(fp_in));
		printf("\n");
	}

	fwrite("data", 4, 1, fp_out); // "data"を書き込む

	fwrite(&len, 4, 1, fp_out); // data size を書き込む

	return;
}


int _tmain(int argc, _TCHAR* argv[]){
	char in_file_name[20] = "aaa.wav"; // サンプルデータのファイル名

	char out_file_name[3][20] = { "low_pass_aaa.wav", "high_pass_aaa.wav", "band_pass_aaa.wav" };

	FILE *in_file;
	FILE *out_file;

	errno_t error;

	unsigned long f;
	unsigned long data_size;
	unsigned long s_data_size;
	short* data_chunck;
	complex* processing_data;
	unsigned short len;

	int i, phase;

	for (phase = 0; phase <= 2; ++phase){
		printf("----------------\n\"%s\"\n", out_file_name[phase]);

		if (error = fopen_s(&in_file, in_file_name, "rb") != 0) {
			printf("Can not open file\n");
			exit(1);
		}

		if (error = fopen_s(&out_file, out_file_name[phase], "wb") != 0) {
			printf("Can not open file\n");
			exit(1);
		}


		//読み込み
		retrieve_header(in_file, out_file, &f, &data_size);
		s_data_size = data_size / 2;

		data_chunck = (short*)malloc(sizeof(short)* s_data_size);
		for (i = 0; i < (int)s_data_size; i++) {
			data_chunck[i] = get_short(in_file);
		}

		//printf("\nSaving data chuncks.\n");
		//output_s("./data_chunck.txt", data_chunck, s_data_size);

		//複素データ化
		processing_data = (complex*)malloc(sizeof(complex)* s_data_size);
		for (i = 0; i < (int)s_data_size; i++) {
			processing_data[i].r = (double)data_chunck[i];
			processing_data[i].i = 0.0;
		}

		//フィルタ処理
		printf("\nFilter processing.\n");
		PassFilterInterface(processing_data, s_data_size, f, 1024, 512, phase, 2000, 3000);

		//出力
		//printf("\nOutputting.\n");
		//output("./processed_data.txt", processing_data, s_data_size);

		for (i = 0; i < (int)s_data_size; i++){
			if (processing_data[i].r >= 32767){
				len = 32767;
			}
			else if (processing_data[i].r <= -32768){
				len = 32768;
			}
			else{
				len = (unsigned short)processing_data[i].r;
			}

			fwrite(&len, 2, 1, out_file);
		}


		//終了
		free(data_chunck);
		free(processing_data);

		fclose(in_file);
		fclose(out_file);

		printf("\n");
	}

	printf("\nPress enter.\n");
	char press_enter;
	press_enter = getchar();

	return 0;
}
