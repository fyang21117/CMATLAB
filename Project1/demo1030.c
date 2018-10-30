#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 160
#define  NUM 10
int main()
{

/***************************************************************
 * 变量初始化
 * *************************************************************/

	Engine *ep;
	int i = 0, j = 0, k = 0, flag = 0;
	char data[10][241], returns[10][4];	
	char level[41] = {'0'}, buffer[BUFSIZE + 1];
	mxArray *result = NULL，*testdata[10] = { NULL };	
	
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
	level[40] = '\0';
	buffer[BUFSIZE] = '\0';

	if (!(ep = engOpen("")))
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(ep, false);

/***************************************************************
 * 同时处理1-10组数据，赋值覆盖即可
 * 下面数据分别是0x01(烟),0x02(香水),0x03(橘子),0x04(喷漆),0值;
 * *************************************************************/	

	char input[10][258] = {
		"AAAA007C0601030C4239070C443D080B4440070A43420708444306074443050845430508444304064443050744430507444204094642040B4A43050D4E44080F5246091255480A12584A0C12584C0D10584D0C0F574E0B0C554E0A09534E0809504D07094F4C0509514B050A534B060B544B070A534B0609524A0608524906D9",
		"AAAA007C060103064B9701084E9801095199010A539A000A549A010B559A010C579B010D579A000D5799010D5698010D5597010E5596010E5495010E5394010E5293010E5192010F5091010E4F8F010E4D8E010E4C8C010E4A8A010E4988010E4787010D4685010D4483010D4382010D4280010D417F010D3F7D010D3E7B01D9",
		"AAAA007C060103020C3301E2000E01020C3602020C3701020C3801020C3801010C3901020D3901020D3A01020C3A01020C3A01020C3A01020C3A01020C3A01020C3A01020C3901020C3901020C3901020B3801020B3801020B3801020B3801020B3701020B3701020A3601020A3601020A3601020A3501020A3501020A3601D9",
		"AAAA007C06010303000001040000010400000103000001030000010400000104000001030000010300000104000001E2000E0103000001030000010400000104000001030000010300000104000001040000010300000103000001030000010400000103000001030000010400000104000001030000010300000104000001D9" ,
		"AAAA007C060103022936010229360102293601032936010229360102293601022836010328350103283500022734010227340102263301032633010325320003243101022431010223300103222F0103222E0103222E0102212D0102212D0102222C0103222C0002222C0102222C0102222C0102222C0103222C0102212B01D9",
		"0000",
		"0000",
		"0000",
		"0000",
		"0000"
	};

/***************************************************************
 * 数据处理过程：
  * mxCreateString构建变量
   * engPutVariable传输变量
    * engEvalString发送指令
	 * engOutputBuffer结果缓存
 * *************************************************************/	

	for (i = 0; i < NUM; i++) {
		
	   for (j = 14, k = 0; j < 254; j++, k++) {	//这个内部for循环，在整合时删除
			data[i][k] = input[i][j];
		}
		
	    data[i][240] = '\0';
	    testdata[i] = mxCreateString(data[i]);
        if(flag != engPutVariable(ep, inputdata[i], testdata[i]))
			printf("f2ff\n");
	    
	    if(flag != engEvalString(ep, savedata[i]))
			printf("f3ff\n");
	}

	engOutputBuffer(ep, buffer, BUFSIZE);						

	if(flag != engEvalString(ep, "Mtest"))		//算法执行 
		printf("f4ff\n");

	engOutputBuffer(ep, NULL, 0);
/***************************************************************
 * 数据返回
 * *************************************************************/	
	if((result = engGetVariable(ep, "kind")) !=NULL)
	{
	    for (i = 0; i < NUM; i++)
		{
		    level[i * 2 + 0] = buffer[17 + i * 6];
		    for(j = 20;j < sizeof(buffer);j++) {
			
			if(buffer[j] == '=' && buffer[j - 4] == 'v') {
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
			printf("The returns[%d] is %s\n", i, returns[i]);
	    }
		
	}else
		 printf("engGetVariable error !\n" );
	
	for (i = 0; i < NUM; i++) 
	     mxDestroyArray(testdata[i]);	

	mxDestroyArray(result);										
	engClose(ep);		
	return EXIT_SUCCESS;
}


