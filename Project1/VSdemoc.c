#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 160
#define  NUM 1
#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")

int main()
{
	Engine *ep = engOpen(NULL);
	char level[41] = {'0'}, returns[10][4], buffer[BUFSIZE + 1];
	int i = 0, j = 0, k = 0, flag = 0;
	char data[10][241];
	char inputdata[10][3] = { "t0" ,"t1","t2","t3","t4","t5","t6","t7","t8","t9"};
	char savedata[10][100] = {
		"save ('data.mat','t0');",
		"save ('data.mat','t0','t1');",
		"save ('data.mat','t0','t1','t2');",
		"save ('data.mat','t0','t1','t2','t3');",
		"save ('data.mat','t0','t1','t2','t3','t4');",
		"save ('data.mat','t0','t1','t2','t3','t4','t5');",
		"save ('data.mat','t0','t1','t2','t3','t4','t5','t6');",
		"save ('data.mat','t0','t1','t2','t3','t4','t5','t6','t7');",
		"save ('data.mat','t0','t1','t2','t3','t4','t5','t6','t7','t8');" ,
		"save ('data.mat','t0','t1','t2','t3','t4','t5','t6','t7','t8','t9');" };
	mxArray *testdata[10] = { NULL };
	mxArray *result = NULL;
	level[40] = '\0';
	buffer[BUFSIZE] = '\0';
	if (!ep){
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(ep, false);

/*	//1烟:1029
	char input0[] = { "AAAA007C0601030C4239070C443D080B4440070A43420708444306074443050845430508444304064443050744430507444204094642040B4A43050D4E44080F5246091255480A12584A0C12584C0D10584D0C0F574E0B0C554E0A09534E0809504D07094F4C0509514B050A534B060B544B070A534B0609524A0608524906D9" };
	//2香水1029
	char input1[] = { "AAAA007C060103064B9701084E9801095199010A539A000A549A010B559A010C579B010D579A000D5799010D5698010D5597010E5596010E5495010E5394010E5293010E5192010F5091010E4F8F010E4D8E010E4C8C010E4A8A010E4988010E4787010D4685010D4483010D4382010D4280010D417F010D3F7D010D3E7B01D9" };
	//3橘子1029
	char input2[] = { "AAAA007C060103020C3301E2000E01020C3602020C3701020C3801020C3801010C3901020D3901020D3A01020C3A01020C3A01020C3A01020C3A01020C3A01020C3A01020C3901020C3901020C3901020B3801020B3801020B3801020B3801020B3701020B3701020A3601020A3601020A3601020A3501020A3501020A3601D9" };
	//4纸巾1029
	char input3[] = { "AAAA007C06010303000001040000010400000103000001030000010400000104000001030000010300000104000001E2000E0103000001030000010400000104000001030000010300000104000001040000010300000103000001030000010400000103000001030000010400000104000001030000010300000104000001D9" };
	//4喷漆1029
	char input4[] = { "AAAA007C060103022936010229360102293601032936010229360102293601022836010328350103283500022734010227340102263301032633010325320003243101022431010223300103222F0103222E0103222E0102212D0102212D0102222C0103222C0002222C0102222C0102222C0102222C0103222C0102212B01D9" };
*/
	char input[10][258] = {"AAAA007C0601030C4239070C443D080B4440070A43420708444306074443050845430508444304064443050744430507444204094642040B4A43050D4E44080F5246091255480A12584A0C12584C0D10584D0C0F574E0B0C554E0A09534E0809504D07094F4C0509514B050A534B060B544B070A534B0609524A0608524906D9",
		"AAAA007C060103064B9701084E9801095199010A539A000A549A010B559A010C579B010D579A000D5799010D5698010D5597010E5596010E5495010E5394010E5293010E5192010F5091010E4F8F010E4D8E010E4C8C010E4A8A010E4988010E4787010D4685010D4483010D4382010D4280010D417F010D3F7D010D3E7B01D9",
		"AAAA007C060103020C3301E2000E01020C3602020C3701020C3801020C3801010C3901020D3901020D3A01020C3A01020C3A01020C3A01020C3A01020C3A01020C3A01020C3901020C3901020C3901020B3801020B3801020B3801020B3801020B3701020B3701020A3601020A3601020A3601020A3501020A3501020A3601D9",
		"AAAA007C06010303000001040000010400000103000001030000010400000104000001030000010300000104000001E2000E0103000001030000010400000104000001030000010300000104000001040000010300000103000001030000010400000103000001030000010400000104000001030000010300000104000001D9" ,
		"AAAA007C060103022936010229360102293601032936010229360102293601022836010328350103283500022734010227340102263301032633010325320003243101022431010223300103222F0103222E0103222E0102212D0102212D0102222C0103222C0002222C0102222C0102222C0102222C0103222C0102212B01D9",
		"0000","0000","0000","0000","0000"
	};

	for (i = 0; i < NUM; i++) {
		for (j = 14, k = 0; j < 254; j++, k++) {	//前面14位固定字符，后面连着气味数据120个(240位)是截取部分
			data[i][k] = input[i][j];
		}
		data[i][240] = '\0';

		testdata[i] = mxCreateString(data[i]);
		
		if (flag != engPutVariable(ep, inputdata[i], testdata[i])){//将变量发到MATLAB工作区间
			printf("f2ff\n");
		}
		if (flag != engEvalString(ep, savedata[i])){		//检查存数据情况
			printf("f3ff\n");
		}
	}
	/*	testdata1 = mxCreateString(data1);
		testdata2 = mxCreateString(data2);
		testdata3 = mxCreateString(data3);
		testdata4 = mxCreateString(data4);*/
	/*if (flag != engPutVariable(ep, "input_data", testdata))
			printf("f2f0\n");
		if (flag != engPutVariable(ep, "input_data1", testdata1))
			printf("f2f1\n");
		if (flag != engPutVariable(ep, "input_data2", testdata2))
			printf("f2f2\n");
		if (flag != engPutVariable(ep, "input_data3", testdata3))
			printf("f2f3\n");
		if (flag != engPutVariable(ep, "input_data4", testdata4))
			printf("f2f4\n");

		if (flag != (engPutVariable(ep, "input_data", testdata)
			|| engPutVariable(ep, "input_data1", testdata1)
			|| engPutVariable(ep, "input_data2", testdata2)
			|| engPutVariable(ep, "input_data3", testdata3)
			|| engPutVariable(ep, "input_data4", testdata4)

			|| engPutVariable(ep, "input_data5", testdata)
			|| engPutVariable(ep, "input_data6", testdata1)
			|| engPutVariable(ep, "input_data7", testdata2)
			|| engPutVariable(ep, "input_data8", testdata3)))
			printf("f2ff\n");
			*/
	/*	if(flag != engEvalString(ep, "save ('data.mat','input_data');"))	//检查存数据情况
	{
	printf("f3ff\n");
	}*/
	engOutputBuffer(ep, buffer, BUFSIZE);
	if (flag != engEvalString(ep, "rdiot1029")){		//检查算法文件执行
		printf("f4ff\n");
	}
	engOutputBuffer(ep, NULL, 0);

	printf("The  result of MATLAB is %s\n", buffer);
	if ((result = engGetVariable(ep, "kind")) != NULL)
	{
		//for (i = 0; i < sizeof(buffer); i++)printf("The  result of MATLAB【%d】 is %c\n", i, buffer[i]);
		// 0x01(smoke),0x02(xiangshui), 0x03(juzi), 0x04(penqi|zhijin);01-05level

		for (i = 0; i < NUM; i++){
			level[i * 2 + 0] = buffer[14 + i * 6];
			for (j = 20;j < sizeof(buffer);j++) {
				if (buffer[j] == '=' && buffer[j - 4] == 'v') {
					j = j + 2;
					level[i * 2 + 1] = buffer[j+ (i+1) * 6];
				}
			}
		}

		for (i = 0; i < NUM; i++){
			returns[i][0] = '0';
			returns[i][1] = level[i * 2];
			returns[i][2] = '0';
			returns[i][3] = level[i * 2 + 1];
			returns[i][4] = '\0';
			printf("\nThe returns[%d] is %s", i, returns[i]);
		}
	}
	else
		printf("engGetVariable error !\n");
	for (i = 0; i < NUM; i++) {
		mxDestroyArray(testdata[i]);
	}
	mxDestroyArray(result);
	engClose(ep);
	while (1);
	return EXIT_SUCCESS;
}
