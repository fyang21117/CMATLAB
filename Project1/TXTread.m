clc
clear
testdata=[];
temp=[];
data=[];

[file,path]=uigetfile({'*.txt','txt Files (*.txt)'},'选择一个txt文件')
[A,B,C,D,E,F]=textread(file,' %s %s %s %s %s %s',30);
string=[C,D,E,F];
row=size(string,1)
for i=1:row
        temp=string(i,:);
        testdata=[testdata temp];
end

testdata=char(testdata);
row1=size(testdata,1)
temp=[];
for i=1:row1
    temp=testdata(i,:);
    data=[data temp];
end
data

%---------------------------------------------------------
%[A,B,C,D,E,F]=textread('liulian0915.txt',' %d %d %d %d %d %d',30);
%string=[C,D,E,F]
%testdata=num2str(testdata,'%02d');
%a=char(testdata)
