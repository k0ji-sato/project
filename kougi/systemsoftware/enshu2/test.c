
#include<stdio.h>

int main()
{
	float n = 1;
	int i;
	for(i=1;i<30;i++)
	{
		n = n * 15/9;
		printf("15/9の%d乗は%f\n",i,n);
	}

	return 0;
}
