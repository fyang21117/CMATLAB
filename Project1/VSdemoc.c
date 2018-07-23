#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 100
#define  N 120

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")

int main()
{
	Engine *ep;											// 定义Matlab引擎指针
	char buffer[BUFSIZE + 1],level;
	int i = 25 ,return_num;
	mxArray *testdata = NULL, *result = NULL;
	double cArray[N]=									//xibanshui8
	{
	0	,	0	,	0	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0.009765625	,	0.009765625	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0.009765625	,	0	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0.009765625	,	0	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0.009765625	,	0	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0.009765625	,	0	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0.009765625	,	0.009765625	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0	,	0	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0.009765625	,	0.009765625	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0	,	0.009765625	,	0.009765625	,
0	,	0.009765625	,	0.009765625	,	0.009765625	,
0	,	0	,	0.01953125	,	0.009765625	,
0	,	0.009765625	,	0.01953125	,	0.01953125	,
0	,	0	,	0.01953125	,	0.009765625	

	};
	/*double cArray[N] = {							//yan,1
		0	,	4	,	10	,	1	,
		1	,	7	,	15	,	1	,
		1	,	11	,	12	,	1	,
		1	,	23	,	14	,	1	,
		1	,	25	,	18	,	1	,
		1	,	26	,	14	,	1	,
		1	,	39	,	26	,	1	,
		1	,	36	,	36	,	1	,
		1	,	26	,	42	,	1	,
		1	,	39	,	36	,	1	,
		1	,	38	,	31	,	2	,
		1	,	36	,	35	,	2	,
		1	,	36	,	35	,	2	,
		1	,	48	,	31	,	1	,
		1	,	39	,	22	,	1	,
		1	,	17	,	11	,	1	,
		1	,	33	,	13	,	1	,
		2	,	65	,	9	,	1	,
		2	,	50	,	17	,	1	,
		2	,	74	,	10	,	1	,
		1	,	51	,	44	,	1	,
		1	,	28	,	62	,	1	,
		1	,	17	,	37	,	1	,
		1	,	7	,	21	,	2	,
		1	,	6	,	12	,	1	,
		1	,	24	,	12	,	1	,
		1	,	39	,	16	,	1	,
		2	,	49	,	13	,	1	,
		1	,	29	,	30	,	1	,
		1	,	24	,	33	,	2
	};*/

	if (!(ep = engOpen(NULL)))
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	
	engSetVisible(ep,false);
	testdata = mxCreateDoubleMatrix(1, N, mxREAL);								//MATLAB引擎函数使用mxArray数据类型
	memcpy((double *)mxGetPr(testdata), (double *)cArray, N * sizeof(double));			
	engPutVariable(ep, "input_data", testdata);									//将testdata写入Matlab工作空间，取名input_data									
	engEvalString(ep, "save data.mat input_data");								//生存路径D:\Program Files (x86)\SetupDir\MATLAB\R2016b

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);										//结果缓冲区buffer
	engEvalString(ep, "VSdemoc");												// 调用"VSdemoc.m"
	engOutputBuffer(ep, NULL, 0);												//stop saving output
	
	if ((result = engGetVariable(ep, "return_num")) == NULL)		
	{
		printf("The  result of MATLAB is %s.\n", buffer);
		for (; !(buffer[i] >= 'A' && buffer[i] <= 'Z'); i++)
		{
			if(buffer[i] >= '0' && buffer[i] <= '9')
				return_num = (int)(buffer[i] - 48);
		}
		level = (char)(buffer[i]);
		printf("The return_num is %d\n\n", return_num);				// 1(smoke)，2(jinshuqi)，or 3(washing water)
		printf("The level is %c\n\n", level);						//the level is A，B or C
	}
	else
	{
		 printf("engGetVariable error !\n" );
	}

	mxDestroyArray(testdata);							
	mxDestroyArray(result);

	//printf("\nHit return to continue...");
	getchar();											
	engClose(ep);										//关闭Matlab引擎。

	return EXIT_SUCCESS;
}


