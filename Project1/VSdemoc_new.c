#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"
#define  BUFSIZE 2600//40

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")
int  init_engine(Engine *p);
void handling(Engine *ep, char temp[]);

int main()
{
	Engine *ep= engOpen(NULL);
	init_engine(ep);

	//3榴莲:2
	  char input0[] = { "AAAA007C060103016516030265160202651602036516020365160201661603016616030266160202661602036716020367160201671603016716030268170202681702026817030268170301681703016817030368170203681702026817030268170301681702016817020368160203681602026816030268160302681602D9" };
	  handling(ep, input0);
	//2香水
	char input1[] = { "AAAA007C06010300D08E9600D08E9600D08E9600D08E9500D08E9500D18E9500D18E9500D18E9400D18E9400D18E9400D18E9400D08E9300D08E9300D08D9200D08D9200D08D9200D08D9200D08D9100D08D9100D08D9200D08D9200D08D9100D08D9100D08D9100D08D9100D08D9100D08D9100D08C9200D08C9200D08C92D9"};
	handling(ep, input1);
	//4喷漆
	char input2[] = { "AAAA007C060103028F8900028F8900028E8902028E8902018D8902018D89020292890002928900009A8903009A8903019F8900019F890002A2891102A2891101A3890301A3890302A38A0002A38A0000A28A0300A28A0301A18A0201A18A02029F8B11029F8B11019D8B03019D8B03029B8B00029B8B0000998C0200998C02D9"};
	handling(ep, input2);
	//1烟:4
	char input3[] = { "AAAA007C0601030F87670607866B0A07866B0A0885730F0885730F0B84740F0B84740F08826F0E08826F0E0F816F100F816F10077E6F0E077E6F0E087B6D0C087B6D0C07796F0B07796F0B177C740C177C740C127F7B15127F7B15077D7911077D79110679740E0679740E0677700D0677700D0075700B0075700B0E73720CD9"};
	 handling(ep,input3);
	 //0
	 char input[] = { "AAAA007C0601020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000D9"};
	 handling(ep, input);
	
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
	engEvalString(ep, "laomatestnew");									// 调用"hextest.m"
	engOutputBuffer(ep, NULL, 0);

//	printf("The  result of MATLAB is %s\n",buffer);
	if ((result = engGetVariable(ep, "level")) == NULL)
	{
		for (i = 0; i < sizeof(buffer); i++)printf("The  result of MATLAB【%d】 is %c\n",i, buffer[i]);
			for (i = 0; i < 2; i++)
			{
				level[i] = buffer[i + 11 ];
				level[i + 2] = buffer[i + 27 ];					// 0x01(smoke),0x02(jinshuqi), 0x03(xibanshui);01-05level
			}
			printf("\nThe return is %s", level);
			printf("\nthe size of buffer is %d",strlen(buffer));
	}
	else
	{
	printf("engGetVariable error !\n");
	//for (i = 0; i < 80;i++)printf("The  result of MATLAB【%d】 is %c\n",i, buffer[i]);
	}
	
	mxDestroyArray(testdata);
	mxDestroyArray(result);
//	return level;
}


//	mexPutArray(testdata,"input_data");
//	testdata = mxCreateDoubleMatrix(1, N, mxREAL);
//	memcpy((double*)mxGetPr(testdata),(double*)cArray, N * sizeof(double));
//	memcpy((char*)mxGetPr(testdata), (char*)cArray, N * sizeof(char));