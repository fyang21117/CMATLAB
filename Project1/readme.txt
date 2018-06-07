在本demo中通过C语言调用MATLAB引擎来完成指令传送、数据读写等操作，主要功能有：

　　★ 向Matlab环境中写入检测数据。

　　★ 向Matlab环境发送命令，调用算法处理数据(算法VSdemoc.m文件在MATLAB路径内)；

　　★ 从Matlab环境中读取结果，返回return_num；


demo运行的结果：（提前约定识别结果，eg：1是烟，2是金属漆，3是洗板水等）


The result of MATLAB is 

maxi =
     2

The return_num is 2

Hit return to continue...



注：
①xlsx文件是已训练样本库，test.m为算法识别文件；测试数据为自截取的30s数据，按1x120排列的数组；
  传感器上传的数据初始化数组 cArray[N]即可。

②运行环境设置：

	MATLAB engine在linux环境要在/bin/csh下执行（服务器当前是/bin/bash）

    gcc -L/usr/local/MATLAB/R2015b/bin/glnxa64 
	-I//usr/local/MATLAB/R2015b/extern/include VSdemoc.c -o demo 
	-lmat -lmx -leng -Wl,-rpath=/usr/local/MATLAB/R2015b/bin/glnxa64

③需要返回APP显示的结果为return_num;即已约定的识别种类（1,2,3,4等等，后面算法部分会继续调整的）

④编译若链接库还出现问题，可能升级gcc就OK了

⑤代码在Windows和Linux两个环境皆可执行，只是MATLAB的链接库有差异（命名分别是.lib和.so，以及所在位置不同的差别）

⑥每次运行，会生成一个data.mat文件，大小为1kb，路径在MATLAB安装路径里面/usr/local/MATLAB/R2015b/bin。（每次都会覆盖）











demo要求：
用c/c++语言读写matlab数据
demo直接和matlab API读写；
硬件上报的数据直接发到matlab处理
demo读取处理结果就可以直接返回APP；
在demo上通过matlab API实现到读取数据；linux环境
