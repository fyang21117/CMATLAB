#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 30
#define  N 120

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")
void init_engine();

int main()
{
	Engine *ep;
	if (!(ep = engOpen(NULL)))
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(ep, false);

	char returns[8] , buffer[BUFSIZE + 1];
	int i = 0, j = 0, temp, len, cArray[N];
	mxArray *testdata = NULL, *result = NULL;
	
	unsigned int	HEX_data[180] = {
		12	,	34	,	00	,	00     ,  0x1D ,	05	,
		12	,	34	,	0x1E,    00		,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	0x2A	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05	,
		12	,	34	,	00	,	0x1F	,	00	,	06	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1E	,	00	,	05	,
		12	,	34	,	00	,	0x1D	,	00	,	05
	};
//	printf("\n0x1D/16= %d  \n", 0x1D /16);
	printf("change data to dec is :\n");
	for (i=0; i<180; i++)
	{
		if(i%6!=0  && (i-1)%6!=0  )
		{
			cArray[j++] = HEX_data[i];
			if(HEX_data[i] % 16 < '9')
				cArray[j]= (HEX_data[i] / 16) * 16 + (HEX_data[i] % 16);
			else
			{
				switch (HEX_data[i] % 16)
				{
				case 'A':temp = 10; break;
				case 'B':temp = 11; break;
				case 'C':temp = 12; break;
				case 'D':temp = 13; break;
				case 'E':temp = 14; break;
				case 'F':temp = 15; break;
				default:break;
				}
				cArray[j] = (HEX_data[i] / 16) * 16 + temp;
			}
		printf("%3d  ", cArray[j]);
		}
	}j = 0;
	len = sizeof(cArray)/sizeof(int);
	printf("\nthe length is %d \n",len);
	
	testdata = mxCreateDoubleMatrix(1, N, mxREAL);
	memcpy((void*)mxGetPr(testdata), (void *)cArray, N * sizeof(int));
	engPutVariable(ep, "input_data", testdata);									//将testdata写入Matlab工作空间，取名input_data									
	engEvalString(ep, "save ('data.mat','input_data');");						//生成路径D:\Program Files (x86)\SetupDir\MATLAB\R2016b

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);										//结果缓冲区buffer
	engEvalString(ep, "newtest");												// 调用"VSdemoc.m"
	engOutputBuffer(ep, NULL, 0);												//stop saving output
	
	if ((result = engGetVariable(ep, "output")) != NULL)		
	{
//		printf("The  result of MATLAB is %s", buffer);
//		printf("size of buffer is :%ld\n", sizeof(buffer) / sizeof(char));
		for (i = 11; i<18; i++)
		{
			returns[j++] = buffer[i];
		/*	if (buffer[i] == '=')
			{
				i += 2;
				for (j = 0; j <= 4; j++)
					returns[j] = buffer[++i];
			}*/
		}
		printf("\nThe returns is %s\n", returns);// 1(smoke),2(jinshuqi),or 3(xibanshui),the level is A,B or C
	}
	else
	{
		 printf("engGetVariable error !\n" );
	}
	mxDestroyArray(testdata);							
	mxDestroyArray(result);
	getchar();											
	engClose(ep);										
	return EXIT_SUCCESS;
}

void init_engine()
{
	

}

