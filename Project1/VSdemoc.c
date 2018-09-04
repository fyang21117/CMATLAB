#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"
#define  BUFSIZE 40//40

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")
int  init_engine(Engine *p);
void handling(Engine *ep, char temp[]);

int main()
{
	Engine *ep= engOpen(NULL);
	init_engine(ep);

	//char input[] = { "AAAA007C060103012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903020303" };
	char input[] = { "AAAA007C0601020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000D9"};
	handling(ep,input);

	engClose(ep);
	getchar();
	while (1);								
	return EXIT_SUCCESS;
}

int init_engine(Engine *p)
{
	if (!p)
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(p, false);
	return 0;
}

void handling(Engine *ep, char temp[])
{
	int i = 0, j = 0;
	mxArray *testdata = NULL, *result = NULL;
	char  level[5], buffer[BUFSIZE + 1], data[241];
	level[4] = '\0';
	for (i = 14; i < 255; i++, j++)										//截取气味数据到数组
		data[j] = temp[i];
	data[240] = '\0';

	testdata = mxCreateString(data);
	engPutVariable(ep, "input_data", testdata);							//将testdata传入Matlab工作空间，取名input_data	
	engEvalString(ep, "save ('data.mat','input_data');");				//生成路径D:\Program Files (x86)\SetupDir\MATLAB\R2016b

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);								//结果缓冲区buffer
	engEvalString(ep, "hextest");									// 调用"hextest.m"
	//engOutputBuffer(ep, NULL, 0);

	if ((result = engGetVariable(ep, "level")) != NULL)
	{
		printf("The  result of MATLAB is %s\n",buffer);
		for (i = 0; i < 2; i++)
		{
			level[i] = buffer[i + 11];
			level[i+2] = buffer[i + 27];					// 0x01(smoke),0x02(jinshuqi), 0x03(xibanshui);01-05level
		}
		printf("\nThe return is %s", level);
	}
	else
	{
	printf("engGetVariable error !\n");
	//for (i = 0; i < 80;i++)printf("The  result of MATLAB【i】 is %c\n", buffer[i]);
	}
	
	mxDestroyArray(testdata);
	mxDestroyArray(result);
//	return level;
}


//	mexPutArray(testdata,"input_data");
//	testdata = mxCreateDoubleMatrix(1, N, mxREAL);
//	memcpy((double*)mxGetPr(testdata),(double*)cArray, N * sizeof(double));
//	memcpy((char*)mxGetPr(testdata), (char*)cArray, N * sizeof(char));