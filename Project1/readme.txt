�ڱ�demo��ͨ��C���Ե���MATLAB���������ָ��͡����ݶ�д�Ȳ�������Ҫ�����У�

������ ��Matlab������д�������ݡ�

������ ��Matlab����������������㷨��������(�㷨VSdemoc.m�ļ���MATLAB·����)��

������ ��Matlab�����ж�ȡ���������return_num��


demo���еĽ��������ǰԼ��ʶ������eg��1���̣�2�ǽ����ᣬ3��ϴ��ˮ�ȣ�


The result of MATLAB is 

maxi =
     2

The return_num is 2

Hit return to continue...



ע��
��xlsx�ļ�����ѵ�������⣬test.mΪ�㷨ʶ���ļ�����������Ϊ�Խ�ȡ��30s���ݣ���1x120���е����飻
  �������ϴ������ݳ�ʼ������ cArray[N]���ɡ�

�����л������ã�

	MATLAB engine��linux����Ҫ��/bin/csh��ִ�У���������ǰ��/bin/bash��

    gcc -L/usr/local/MATLAB/R2015b/bin/glnxa64 
	-I//usr/local/MATLAB/R2015b/extern/include VSdemoc.c -o demo 
	-lmat -lmx -leng -Wl,-rpath=/usr/local/MATLAB/R2015b/bin/glnxa64

����Ҫ����APP��ʾ�Ľ��Ϊreturn_num;����Լ����ʶ�����ࣨ1,2,3,4�ȵȣ������㷨���ֻ���������ģ�

�ܱ��������ӿ⻹�������⣬��������gcc��OK��

�ݴ�����Windows��Linux���������Կ�ִ�У�ֻ��MATLAB�����ӿ��в��죨�����ֱ���.lib��.so���Լ�����λ�ò�ͬ�Ĳ��

��ÿ�����У�������һ��data.mat�ļ�����СΪ1kb��·����MATLAB��װ·������/usr/local/MATLAB/R2015b/bin����ÿ�ζ��Ḳ�ǣ�











demoҪ��
��c/c++���Զ�дmatlab����
demoֱ�Ӻ�matlab API��д��
Ӳ���ϱ�������ֱ�ӷ���matlab����
demo��ȡ�������Ϳ���ֱ�ӷ���APP��
��demo��ͨ��matlab APIʵ�ֵ���ȡ���ݣ�linux����
