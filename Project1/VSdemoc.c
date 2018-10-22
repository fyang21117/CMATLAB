#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 160
#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")

int main()
{
	Engine *ep = engOpen(NULL);
	char level[21],returns[5][5],buffer[BUFSIZE + 1],data[241], data1[241], data2[241], data3[241], data4[241];
	int i = 0, j = 0,flag = 0;
	mxArray *testdata = NULL, *testdata1 = NULL, *testdata2 = NULL, *testdata3 = NULL, *testdata4 = NULL, *result = NULL;
	level[20] = '\0';

	if (!ep)
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(ep, false);

	//0
	char input[]  = { "AAAA007C060102000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000D9" };
	//1烟:4
	char input1[] = { "AAAA007C0601030F87670607866B0A07866B0A0885730F0885730F0B84740F0B84740F08826F0E08826F0E0F816F100F816F10077E6F0E077E6F0E087B6D0C087B6D0C07796F0B07796F0B177C740C177C740C127F7B15127F7B15077D7911077D79110679740E0679740E0677700D0677700D0075700B0075700B0E73720CD9" };
	//2香水
	char input2[] = { "AAAA007C06010300D08E9600D08E9600D08E9600D08E9500D08E9500D18E9500D18E9500D18E9400D18E9400D18E9400D18E9400D08E9300D08E9300D08D9200D08D9200D08D9200D08D9200D08D9100D08D9100D08D9200D08D9200D08D9100D08D9100D08D9100D08D9100D08D9100D08D9100D08C9200D08C9200D08C92D9" };
	//3榴莲:2
	char input3[] = { "AAAA007C060103016516030265160202651602036516020365160201661603016616030266160202661602036716020367160201671603016716030268170202681702026817030268170301681703016817030368170203681702026817030268170301681702016817020368160203681602026816030268160302681602D9" };
	//4喷漆
	char input4[] = { "AAAA007C060103028F8900028F8900028E8902028E8902018D8902018D89020292890002928900009A8903009A8903019F8900019F890002A2891102A2891101A3890301A3890302A38A0002A38A0000A28A0300A28A0301A18A0201A18A02029F8B11029F8B11019D8B03019D8B03029B8B00029B8B0000998C0200998C02D9" };

	for (i = 14; i < 254; i++, j++) {	//前面14位固定字符，后面连着气味数据120个(240位)是截取部分
		data[j]  = input[i];
		data1[j] = input1[i];
		data2[j] = input2[i];
		data3[j] = input3[i];
		data4[j] = input4[i];
	}
	data[240]='\0';
	data1[240] = '\0';	
	data2[240] = '\0';
	data3[240] = '\0';
	data4[240] = '\0';
	testdata = mxCreateString(data);
	testdata1 = mxCreateString(data1);
	testdata2 = mxCreateString(data2);
	testdata3 = mxCreateString(data3);
	testdata4 = mxCreateString(data4);

	if(flag != engPutVariable(ep, "input_data", testdata))			
		printf("f2f0\n");			
	if (flag != engPutVariable(ep, "input_data1", testdata1))			
		printf("f2f1\n");
	if (flag != engPutVariable(ep, "input_data2", testdata2))			
		printf("f2f2\n");
	if (flag != engPutVariable(ep, "input_data3", testdata3))			
		printf("f2f3\n");
	if (flag != engPutVariable(ep, "input_data4", testdata4))			
		printf("f2f4\n");

	if (flag != engEvalString(ep, "save 'data.mat';"))//检查存数据情况
	{
		printf("f3ff\n");
	}

/*	if(flag != engEvalString(ep, "save ('data.mat','input_data');"))	//检查存数据情况
	{
		printf("f3ff\n");
	}*/
	
	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);						
	if(flag != engEvalString(ep, "laomatest"))		//检查算法文件执行，错误输出f4ff 
	{
		printf("f4ff\n");
	}
	engOutputBuffer(ep, NULL, 0);

	//printf("The  result of MATLAB is %s\n",buffer);
	if ((result = engGetVariable(ep, "level")) !=NULL)
	{
		//for (i = 0; i < sizeof(buffer); i++)printf("The  result of MATLAB【%d】 is %c\n", i, buffer[i]);
		for (i = 0; i < 5; i++)
		{
			level[i*4 + 0] = buffer[11 + i * 31];
			level[i*4 + 1] = buffer[12 + i * 31];
			level[i*4 + 2] = buffer[27 + i * 31];
			level[i*4 + 3] = buffer[28 + i * 31];// 0x01(smoke),0x02(jinshuqi), 0x03(xibanshui);01-05level
		}
		//printf("\nThe buffer is %s", level);
		for (i = 0; i < 5; i++)
		{
			returns[i][0] = level[i * 4];
			returns[i][1] = level[i * 4 + 1];
			returns[i][2] = level[i * 4 + 2];
			returns[i][3] = level[i * 4 + 3];
			returns[i][4] = '\0';
			printf("\nThe returns[%d] is %s",i,returns[i]);
		}
		
	}else
		 printf("engGetVariable error !\n" );
	
	mxDestroyArray(testdata);					
	mxDestroyArray(result);										
	engClose(ep);		
	while (1);
	return EXIT_SUCCESS;
}


