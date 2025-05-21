#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

double d_rand() {
	return(((double)(rand() % 32767) / 32767.0 - 0.5) * 2.0);
}

int main()
{
	char ch;
	int i, j, p, l, out[10], jum, ERR[10];
	int x[10][8] =
	{   //a b c d e f g 1 
		{ 1,1,1,1,1,1,0,1 },//0
		{ 0,1,1,0,0,0,0,1 },//1
		{ 1,1,0,1,1,0,1,1 },//2
		{ 1,1,1,1,0,0,1,1 },//3
		{ 0,1,1,0,0,1,1,1 },//4
		{ 1,0,1,1,0,1,1,1 },//5
		{ 0,0,1,1,1,1,1,1 },//6
		{ 1,1,1,0,0,0,0,1 },//7
		{ 1,1,1,1,1,1,1,1 },//8
		{ 1,1,1,0,0,1,1,1 } //9
	};
	int T[10][10] =
	{      //0 1 2 3 4 5 6 7 8 9
		{ 1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,0,1 }
	};
	float w[10][8], O[10], LR = 0.1f, init = 0.15f, error;
	//inisialisasi bobot
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 8; i++)
		{
			w[j][i] = init * d_rand();
			printf("%.2f ", w[j][i]);
		}
		printf("\n");
	}
	//traning
	for (l = 0; l < 100; l++)
	{
		error = 0.0f; jum = 1;
		for (p = 0; p < 10; p++)
		{
			for (j = 0; j < 10; j++)
			{
				O[j] = 0.0;
				for (i = 0; i < 8; i++)
				{
					O[j] = O[j] + x[p][i] * w[j][i];
				}
				if (O[j] > 0.0)
					out[j] = 1;
				else
					out[j] = 0;
				ERR[j] = T[p][j] - out[j];
				error = fabs(error + ERR[j]);
				jum++;
				if (ERR[j] != 0)
				{
					for (i = 0; i < 8; i++)
					{
						w[j][i] = w[j][i] + LR * x[p][i] * ERR[j];
					}
				}
			}
		}
		error = error / jum;
		printf("error=%.5f\n", error);
	}
	for (;;) {
		//running
		for (i = 0; i < 7; i++)
		{
			printf("Input X[%d]:", i);
			scanf_s("%d", &x[0][i]);
		}
		for (j = 0; j < 10; j++)
		{
			O[j] = 0.0;
			for (i = 0; i < 8; i++)
			{
				O[j] = O[j] + x[0][i] * w[j][i];
			}
			if (O[j] > 0.0)
				out[j] = 1;
			else
				out[j] = 0;
			printf("Output[%d]:%d\n", j, out[j]);
		}
		if ((out[0] == 1) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 0\n");
		if ((out[0] == 0) && (out[1] == 1) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 1\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 1) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 2\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 1) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 3\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 1) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 4\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 1) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 5\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 1) && (out[7] == 0) && (out[8] == 0) && (out[9] == 0))printf("Output: 6\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 1) && (out[8] == 0) && (out[9] == 0))printf("Output: 7\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 1) && (out[9] == 0))printf("Output: 8\n");
		if ((out[0] == 0) && (out[1] == 0) && (out[2] == 0) && (out[3] == 0) && (out[4] == 0) && (out[5] == 0) && (out[6] == 0) && (out[7] == 0) && (out[8] == 0) && (out[9] == 1))printf("Output: 9\n");
	}
}