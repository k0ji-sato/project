// AWGN.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <math.h>


#define PI 3.14159265358979323846264338327950288

typedef struct {
	double r;
	double i;
} complex;

complex complex_add(complex z1,complex z2)
{
	complex tmp;
	tmp.r = z1.r+z2.r;
	tmp.i = z1.i+z2.i;
	return tmp;
}


complex complex_sub(complex z1,complex z2)
{
	complex tmp;
	tmp.r = z1.r-z2.r;
	tmp.i = z1.i-z2.i;
	return tmp;
}


complex complex_mul(complex z1,complex z2)
{
	complex tmp;
	tmp.r = z1.r*z2.r-z1.i*z2.i;
	tmp.i = z1.r*z2.i+z1.i*z2.r;
	return tmp;
}


complex complex_div(complex z1, complex z2)
{
	complex tmp;
	double den;
	den = z2.r*z2.r+z2.i*z2.i;


	if(den==0){
		printf("Fatal Error:divided by zero!\n");
		exit(1);
	}
	tmp.r = (z1.r*z2.r+z1.i*z2.i)/den;
	tmp.i = (z2.r*z1.i-z1.r*z2.i)/den;
	return tmp;
}


complex complex_jexp(double x)
{
	complex tmp;
	tmp.r = cos(x);
	tmp.i = sin(x);
	return tmp;
}


complex* conjugate(complex *x,long N)
{
	int i;
	complex *tmp;
	tmp = (complex *)malloc(sizeof(complex) * N);
	for(i=0; i<N; i++){
		tmp[i].r = x[i].r;
		tmp[i].i = -x[i].i;
	}
	return tmp;
}


void clear(complex *x,long N)
{
	int i;
	for(i=0; i<N; i++){
		x[i].r = 0;
		x[i].i = 0;
	}
}



void fft(complex *x,long N,int fft_mode)
{
	int i,j,m,n;
	complex a;
	complex *fe,*fo;   //fe:偶、fe:奇
	
	a.r = sqrt(2.0);
	a.i = 0;

	//fe,foそれぞれにN/2バイト分のメモリを確保
	fe = (complex *)malloc(sizeof(complex) * N/2);
	fo = (complex *)malloc(sizeof(complex) * N/2);
	//メモリ不足により指定サイズ分のメモリ確保に失敗
	if((fe == NULL)||(fo == NULL)) {
      printf("メモリが確保できません。\n");
      return;
	}

	//入力データの偶数番目をfe、奇数番目をfoに格納
	for(i=0; i<N; i++){      
			if(i%2 == 0){
				m = i/2;
				fe[m].r = x[i].r;
				fe[m].i = x[i].i;
			} 
			else{
				n = (i-1)/2;
				fo[n].r = x[i].r;
				fo[n].i = x[i].i;
			}
	}

	if(N>2){
		//再起呼び出し
		fft(fe,N/2,fft_mode);
		fft(fo,N/2,fft_mode);
		
		//計算
		for(j=0; j<N; j++){
			//fft_mode=-1の場合FFT、fft_mode=1の場合IFFT
			x[j] = complex_div(complex_add(fe[j%(N/2)],complex_mul(fo[j%(N/2)],complex_jexp((fft_mode * 2.0 * PI * j)/N))),a);
		}
	}
	else{
		x[0] = complex_div(complex_add(fe[0],complex_mul(fo[0],complex_jexp((fft_mode * 2.0 * PI * 0)/2))),a);
		x[1] = complex_div(complex_add(fe[0],complex_mul(fo[0],complex_jexp((fft_mode * 2.0 * PI * 1)/2))),a);
	}

	//メモリ解放
	free(fe);
	free(fo);
}




//**************************************************************************************
// Low Pass Filter:
void LowPassFilter(complex *x, int N)
{	
	double a;
	int b,i;
	a = 44100.0/N;
	b = (int)(2000.0/a);
	
	for(i=b; i<N-b; i++)
	{
		x[i].r = 0;
		x[i].i = 0;
	}
	
	/*for(i=0; i<N/2-b; i++)
	{
		x[i].r = 0.0;
		x[i].i = 0.0;
	}
	for(i=b; i<N/2-b; i++)
	{
		x[i].r = 0.0;
		x[i].i = 0.0;
	}
	*/
	return;
}

//**************************************************************************************
// Hi Pass Filter: 
void HiPassFilter(complex *x, int N)
{	
	double a;
	int c,i;
	a = 44100.0/N;
	c = (int)(3000.0/a);

	for(i=0; i<c; i++)
	{
		x[i].r = 0;
		x[i].i = 0;
	}
	for(i=N-c; i<N; i++)
	{
		x[i].r = 0;
		x[i].i = 0;
	}

	return;
}

//**************************************************************************************
// Band Pass Filter: 
void BandPassFilter(complex *x, int N)
{
	double a;
	int b,c,i;
	a = 44100.0/N;
	b = (int)(2000.0/a);
	c = (int)(3000.0/a);

	for(i=0; i<b; i++)
	{
		x[i].r = 0;
		x[i].i = 0;
	}
	for(i=N-b; i<N; i++)
	{
		x[i].r = 0;
		x[i].i = 0;
	}

	for(i=c; i<N-c; i++)
	{
		x[i].r = 0;
		x[i].i = 0;
	}

	return;
}


/*  Global variables declaration  */
static  unsigned long seed =1; 

unsigned long irnd(void)
{
    seed = seed * 1566083941UL + 1;
   /*  example of a:  69069,1664525,39894229,48828125,1812433253,
       2100005341   */
    return seed;
}

double unrnd(void)    /*  Random variable based on uniform distribution */
  /*  0. <= unrnd() < 1. */
{
   return  (1.0 /( ULONG_MAX +1.0))*irnd();
}

double gran(void)  /*  Random variable based on Gaussian distribution */
{   

   static int sw=0;
   static double r1,r2,s;
  
   if (sw == 0) {
       sw = 1;
       do {
         r1=2*unrnd()-1;
         r2=2*unrnd()-1;
         s=r1*r1+r2*r2;
       } while (s>1 || s==0);
       s=sqrt(-2*log(s)/s);
       return r1*s;
   }else{
      sw =0;
      return r2*s;
   }  
}    

void conv(complex *x, complex *y, complex *z, long N)
{
	int i;
	complex a;

	a.r = sqrt((double) N);
	a.i = 0;
	fft(x,N,-1);
	fft(y,N,-1);

	for(i=0; i<N; i++)
	{
		z[i] = complex_mul(a,complex_mul(x[i],y[i]));
	}

	fft(z,N,1);
}


int main(void)
{
	FILE *fp;
	fp = fopen("out.txt","wt");
	int i,j,k,N;
	N = 1024;
	double A,Eb1,Eb2,Ebh0,Ebh1,Ebh2,Ebh0p,Ebh1p,Ebh2p,SNh0,SNh1,SNh2,Ebh2p2,ZZ,BER;
	complex *h0,*h1,*h2,*p,*x,*Z,*y;
	h0 = (complex *)malloc(sizeof(complex) * N);
	h1 = (complex *)malloc(sizeof(complex) * N);
	h2 = (complex *)malloc(sizeof(complex) * N);
	p = (complex *)malloc(sizeof(complex) * N);
	x = (complex *)malloc(sizeof(complex) * N);
	y = (complex *)malloc(sizeof(complex) * N);
	Z = (complex *)malloc(sizeof(complex) * N);

	clear(h0,N);
	clear(h1,N);
	clear(h2,N);
	clear(p,N);


	//(1)
	Eb1 = 0.0;
	for(i=0; i<100;i++)
	{
		p[i].r = 1.0 - 1.0*i/99.0;
		Eb1 = Eb1 + p[i].r * p[i].r;
	}
	//printf("(1)%f\n",Eb1);
	
	
	//(2)-------------------------------------------------------------------------------------------------
	clear(p,N);
	for(i=0; i<100;i++)
	{
		p[99-i].r = 3.0 - 3.0*i/99.0;
	}
	//フィルタ
	Ebh0p=Ebh1p=Ebh2p=0;
	for(i=0; i<N;i++)
	{
		Ebh0p = Ebh0p + h0[i].r * p[i].r;
		Ebh1p = Ebh1p + h1[i].r * p[i].r;
		Ebh2p = Ebh2p + h2[i].r * p[i].r;
	}
	Ebh0p = Ebh0p * Ebh0p;
	Ebh1p = Ebh1p * Ebh1p;
	Ebh2p = Ebh2p * Ebh2p;

	h0[0].r = 1.0;
	for (i = 0; i<100; i++)
	{
		h1[i].r = 1.0 - 1.0*i / 99.0;
		h2[99 - i].r = 1.0 - 1.0*i / 99.0;
	}
	fft(h0,N,-1);
	fft(h1,N,-1);
	fft(h2,N,-1);
	Ebh0=Ebh1=Ebh2=0;
	for(i=0; i<N;i++)
	{
		Ebh0 = Ebh0 + h0[i].r * h0[i].r + h0[i].i * h0[i].i;
		Ebh1 = Ebh1 + h1[i].r * h1[i].r + h1[i].i * h1[i].i;
		Ebh2 = Ebh2 + h2[i].r * h2[i].r + h2[i].i * h2[i].i;
	}
	
	SNh0 = Ebh0p/Ebh0;
	SNh1 = Ebh1p/Ebh1;
	SNh2 = Ebh2p/Ebh2;
	printf("(2)h0:%f,h1:%f,h2:%f\n",SNh0,SNh1,SNh2);
	

	//(3)--------------------------------------------------------------------------------------------------------------

	//x配列に0or1をランダムに格納
	for(i=0; i<N; i++)
	{
		x[i].r = rand()%2;
	}

	for(j=-10; j<31; j++)
	{
		//振幅計算
		Eb2 = pow(10.0,(double)j/10.0);
	
		clear(y,N);
		clear(Z,N);
		for(i=0; i<N; i++)
		{
			if(x[i].r==0)
			{
				y[i].r = -Eb2;
			}
			else
			{
				y[i].r = Eb2;
			}
		} 
		
		for(i=0; i<100;i++)
		{
			h2[99-i].r = 1.0 - 1.0 * i/99.0;
		}
		
		for(i=0; i<N;i++)
		{
			//雑音設定
			ZZ = 0;
			for(k=0; k<N; k++)
			{
				Z[k].r = gran();
			}
			for(k=0; k<N;k++)
			{
				ZZ = ZZ + h2[k].r * Z[k].r;
			}
			y[i].r = y[i].r + ZZ;
			if(y[i].r<0)
			{
				y[i].r = 0;	
			}
			else
			{
				y[i].r = 1;
			}
		}
		//BER計算
		k = 0;
		for(i=0;i<N;i++)
		{
			if(x[i].r != y[i].r)
			{
				k++;
			}
		}
		BER = (double)k/(double)N;
		//printf("%d\t%f\n",j,BER);	
		//fprintf(fp,"%d\t%f\n",j,BER);	
	}
	fclose(fp);
}