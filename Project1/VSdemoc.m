function [ output_args ] = test( input_args )
%TEST Summary of this function goes here
%   Detailed explanation goes here
%   测试样本分级
clc
load data.mat;
testdata =input_data(1:end);
%testdata=[ 0,4,10,1,1,7,15,1,1,11,12,1,1,23,14,1,1,25,18,1,1,26,14,1,1,39,26,1,1,36,36,1,1,26,42,1,1,39,36,1,1,38,31,2,1,36,35,2,1,36,35,2,1,48,31,1,1,39,22,1,1,17,11,1,1,33,13,1,2,65,9,1,2,50,17,1,2,74,10,1,1,51,44,1,1,28,62,1,1,17,37,1,1,7,21,2,1,6,12,1	,1,24,12,1,1,39	,16	,1,2,49,13,1,1,29,30,1,1,24,33,2];

[testrow testcol]=size(testdata);
SCORE=xlsread('SCORE.xlsx');
SCORE2=xlsread('SCORE2.xlsx');
SCORE3=xlsread('SCORE3.xlsx');
V=xlsread('V.xlsx');
meanSCORE=mean(SCORE);
meanSCORE2=mean(SCORE2);
meanSCORE3=mean(SCORE3);


col=size(testdata',1);
testdata=(testdata-repmat(mean(testdata'),1,col))./(repmat(std(testdata'),1,col));
testSCORE=testdata*V;

PCNUM=21;
[row col]=size(SCORE);
testdis1=0;

for i=1:PCNUM
testdis1=testdis1+(testSCORE(i)-meanSCORE(i))^2;
end
testdis1=real(sqrt(testdis1));

[row col]=size(SCORE2);
testdis2=0;
for i=1:PCNUM
testdis2=testdis2+(testSCORE(i)-meanSCORE2(i))^2;
end
testdis2=real(sqrt(testdis2));

[row col]=size(SCORE3);
testdis3=0;
for i=1:PCNUM
testdis3=testdis3+(testSCORE(i)-meanSCORE3(i))^2;
end
testdis3=real(sqrt(testdis3));

testdis=[testdis1;testdis2;testdis3];
[minum,kind]=min(testdis)

switch kind
    case 1
[row,col]=size(xlsread('database.xlsx','A1:DP400'));
[row2,col2]=size(xlsread('database.xlsx','A201:DP800'));
[row3,col3]=size(xlsread('database.xlsx','A401:DP1200'));
    case 2
[row,col]=size(xlsread('database2.xlsx','A1:DP400'));
[row2,col2]=size(xlsread('database2.xlsx','A201:DP800'));
[row3,col3]=size(xlsread('database2.xlsx','A401:DP1200'));
    case 3
[row,col]=size(xlsread('database3.xlsx','A1:DP400'));
[row2,col2]=size(xlsread('database3.xlsx','A201:DP800'));
[row3,col3]=size(xlsread('database3.xlsx','A401:DP1200'));
    otherwise
        msgbox('出错');
end

[row col]=size(SCORE);
testdis1=repmat(0,row,1);
for i=1:col
testdis1=testdis1+(repmat(testSCORE(i),row,1)-SCORE(:,i)).^2;
end
testdis1=real(sqrt(testdis1));
[row2 col2]=size(SCORE2);
testdis2=repmat(0,row2,1);
for i=1:col2
testdis2=testdis2+(repmat(testSCORE(i),row2,1)-SCORE2(:,i)).^2;
end
testdis2=real(sqrt(testdis2));
[row3 col3]=size(SCORE3);
testdis3=repmat(0,row3,1);
for i=1:col3
testdis3=testdis3+(repmat(testSCORE(i),row3,1)-SCORE3(:,i)).^2;
end
testdis3=real(sqrt(testdis3));

testdis=[testdis1;testdis2;testdis3];
[mindis,mini]=sort(testdis);
level1=0;
level2=0;
level3=0;
for i=1:5
    if mini(i)<=row
        level1=level1+1;
    elseif mini(i)>row&&mini(i)<=(row+row2)
        level2=level2+1;
    else level3=level3+1;
    end
end
[maxlevel level]=max([level1;level2;level3]);
if level==1
    level='A'
elseif level==2
    level='B'
else
    level='C'
    
        

    end

