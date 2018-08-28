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
int  init_engine(Engine *p);
void handling(Engine *ep, char temp[]);
int hexstr2dec(char s[]);

int main()
{
	Engine *ep= engOpen(NULL);
	init_engine(ep);

//	char input[] = { "AAAA007C060103012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903020303" };
	char input[255] ;
	for (int i = 0; i < 255; i++)
		input[i] = '0';
	handling(ep,input);

	engClose(ep);
	getchar();
	while (1);								
	return EXIT_SUCCESS;
}
int hexstr2dec(char s[])
{
	int i, m, temp=0, n;
	m = strlen(s);
	for (i = 0; i<m - 1; i++)
	{
		if (s[i] >= 'A'&&s[i] <= 'F')
			n = s[i] - 'A' + 10;
		else if (s[i] >= 'a'&&s[i] <= 'f')
			n = s[i] - 'a' + 10;
		else
			n = s[i] - '0';
		temp = n;
		i++;
		if (s[i] >= 'A'&&s[i] <= 'F')
			n = s[i] - 'A' + 10;
		else if (s[i] >= 'a'&&s[i] <= 'f')
			n = s[i] - 'a' + 10;
		else
			n = s[i] - '0';
		temp = temp * 16 + n;
		printf("%d\n", temp);
	}	
	return temp;
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
	engOutputBuffer(ep, NULL, 0);

	if ((result = engGetVariable(ep, "level")) != NULL)
	{
		//for(i=0;i<30;i++)			printf("The  result of MATLAB is %c\n", buffer[i]);
		for (i = 0; i < 2; i++)
		{
			level[i] = buffer[i + 11];
			level[i+2] = buffer[i + 27];					// 0x01(smoke),0x02(jinshuqi), 0x03(xibanshui);01-05level
		}
		printf("\nThe return is %s", level);
	}
	else
		printf("engGetVariable error !\n");
	mxDestroyArray(testdata);
	mxDestroyArray(result);
//	return level;
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