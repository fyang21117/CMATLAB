#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"
#define  BUFSIZE 40

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")

int main()
{
	Engine *ep;												
	int i =0, j =0, k =0;
	mxArray *testdata = NULL, *result = NULL;
	char kind[5], level[5], buffer[BUFSIZE + 1],data[240];
	kind[4] = level[4]= '\0';
	if (!(ep = engOpen(NULL)))
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(ep, false);

	char input[] = { "ABCDEFGHIJKLMNABCDEFGHIJKLMN012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903" };
	for (i = 28; i < 269; i++,j++)										//截取气味数据到数组
		data[j] = input[i];

	testdata = mxCreateString(data);
	engPutVariable(ep, "input_data", testdata);							//将testdata传入Matlab工作空间，取名input_data	
	engEvalString(ep, "save ('data.mat','input_data');");				//生成路径D:\Program Files (x86)\SetupDir\MATLAB\R2016b

	buffer[BUFSIZE] =  '\0' ;
	engOutputBuffer(ep, buffer, BUFSIZE);								//结果缓冲区buffer
	engEvalString(ep, "stringtest");									// 调用"stringtest.m"
	engOutputBuffer(ep, NULL, 0);												
	
	if ((result = engGetVariable(ep, "level")) != NULL)
	{
//		printf("The  result of MATLAB is %s", buffer);
		for (i = 0; i < 4; i++)
		{
			kind[i] = buffer[i + 9];
			level[i] = buffer[i+25];					// 0x01(smoke),0x02(jinshuqi), 0x03(xibanshui);
		}
		printf("The kind is %s", kind);
		printf("\nThe level is %s", level);
	}
	else
		 printf("engGetVariable error !\n" );

	mxDestroyArray(testdata);							
	mxDestroyArray(result);
	engClose(ep);
	getchar();	while (1);								
	return EXIT_SUCCESS;
}


//			kind[0] = buffer[9]; kind[1] = buffer[10]; kind[2] = buffer[11]; kind[3] = buffer[12]; kind[4] = '\0';
//			level[0] = buffer[25]; level[1] = buffer[26]; level[2] = buffer[27]; level[3] = buffer[28]; level[4] = '\0';
//			printf("the buffer is %c\n",buffer[i]);

/*char cat[]= "0x",**stop = NULL,hex[120] ;
for (i = 15; i < 135; i++)
{
sprintf(hex, "%s%d",cat,temp[i]);
printf(" hex:%4s ", hex);
cArray[j] = strtol(hex,stop, 16);
printf(" dec:%3.0lf\n",cArray[j]);
j++;
}
*/
//	mexPutArray(testdata,"input_data");
//	testdata = mxCreateDoubleMatrix(1, N, mxREAL);
//	memcpy((double*)mxGetPr(testdata),(double*)cArray, N * sizeof(double));
//	memcpy((char*)mxGetPr(testdata), (char*)cArray, N * sizeof(char));


//	len = sizeof(cArray)/sizeof(double);
//	printf("\nthe length is %d \n",len);
//		printf("The  result of MATLAB is %s", buffer);
//		sprintf(str,"%s%d%s","\"", HEX_data[i],"\"");
//		printf("%d \n", atoi(str));
//	char a = '10';
//		printf("%d",a-'0');
//		printf("%d ", strtol(str, NULL, 10));
//		printf("%d \n",str-'0');
//		cArray[j] = ((int)str / 10) * 16 + ((int)str % 10);
//	printf("%3.0lf ", cArray[j]);
/*
int c[10],hex[10];
char str[10];
double res[10];
for(i=0;i<2;i++)
{
scanf("%s",str);
printf("%s ",str);

sprintf(str, "%d",  hex[i]);
printf(" str:%s ",str);
c[i] = strtol(str, NULL, 10);
printf(" num:%d ", c[i]);
res[i] = (c[i] / 10) * 16 + (c[i] % 10);
printf(" dec:%3.0lf\n",res[i]);
}*/
//		strcat(cat,str);//	printf(" %s ", cat);
//		cArray[j] = (c[j] / 10) * 16 + (c[j] % 10);
//		cArray[j] = c[j];