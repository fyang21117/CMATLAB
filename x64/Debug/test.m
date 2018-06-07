
function [ output_args ] = test( input_args )
%TEST Summary of this function goes here
%   Detailed explanation goes here
%   测试样本分级
clc
SCORE=xlsread('SCORE.xlsx');
SCORE2=xlsread('SCORE2.xlsx');
SCORE3=xlsread('SCORE3.xlsx');
SCORE4=xlsread('SCORE4.xlsx');
V=xlsread('V.xlsx');

% testdata={ 0,4,10,1,1,7,15,1,1,11,12,1,1,23,14,1,1,25,18,1,1,26,14	,1,1,39,26,1,1,36,36,1,1,26,42,1,1,39,36,1,1,38,31,2,1,36,35,2,1,36,35,2,1,48,31,1,1,39,22,1,1,17,11,1,1,33,13,1,2,65,9,1,2,50,17,1,2,74,10,1,1,51,44,1,1,28,62,1,1,17,37,1,1,7,21	,2,1,6,12,1	,1,24,12,1,1,39	,16	,1,2,49,13,1,1,29,30,1,1,24,33,2};

%[testdata,testname]=xlsread('testdata.xlsx');
% [testrow, testcol]=size(testdata);
% if isempty(testdata)
%     msgbox('测试样本不能为空');
% else
% temp=[];
% for i=1:testrow
% temp=[temp testdata(i,:)];
% end
% testdata=temp;
col=size(testdata);
testdata=(testdata-repmat(mean(testdata),[1,col]))./(repmat(std(testdata),[1,col]));
testSCORE=testdata*V;
[row col]=size(SCORE);
testdis1=real(sqrt((repmat(testSCORE(1),row,1)-SCORE(:,1)).^2+(repmat(testSCORE(2),row,1)-SCORE(:,2)).^2));
[row2 col2]=size(SCORE2);
testdis2=real(sqrt((repmat(testSCORE(1),row2,1)-SCORE2(:,1)).^2+(repmat(testSCORE(2),row2,1)-SCORE2(:,2)).^2));
[row3 col3]=size(SCORE3);
testdis3=real(sqrt((repmat(testSCORE(1),row3,1)-SCORE3(:,1)).^2+(repmat(testSCORE(2),row3,1)-SCORE3(:,2)).^2));
[row4 col4]=size(SCORE4);
testdis4=real(sqrt((repmat(testSCORE(1),row4,1)-SCORE4(:,1)).^2+(repmat(testSCORE(2),row4,1)-SCORE4(:,2)).^2));
testdis=[testdis1;testdis2;testdis3;testdis4];
[mindis mini]=sort(testdis);
kindnum=0;
kindnum2=0;
kindnum3=0;
kindnum4=0;
for i=1:5
    if mini(i)<=row
        kindnum=kindnum+1;
    elseif mini(i)>row&&mini(i)<=(row+row2)
        kindnum2=kindnum2+1;
    elseif mini(i)>(row+row2)&&mini(i)<=(row+row2+row3)
        kindnum3=kindnum3+1;
    else
        kindnum4=kindnum4+1;
    end
end
[maxnum maxi]=max([kindnum;kindnum2;kindnum3;kindnum4]);
maxi
end

%end

