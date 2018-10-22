clc
clear
load net;
load std2;
load data.mat;

string(1,:)=input_data(1:end);
string(2,:)=input_data1(1:end);
string(3,:)=input_data2(1:end);
string(4,:)=input_data3(1:end);
string(5,:)=input_data4(1:end);
%string=input_data1(1:end);

for i=1:1:5
col=size(string(i,:),2);
ch1=string(i,1:8:col);
ch2=string(i,2:8:col);
ch3=string(i,3:8:col);
ch4=string(i,4:8:col);
ch5=string(i,5:8:col);
ch6=string(i,6:8:col);
ch7=string(i,7:8:col);
ch8=string(i,8:8:col);
str1=[ch1',ch2'];
str2=[ch3',ch4'];
str3=[ch5',ch6'];
str4=[ch7',ch8'];
col1=hex2dec(str1);
col2=hex2dec(str2);
col3=hex2dec(str3);
col4=hex2dec(str4);
testdata=[col1 col2 col3 col4];%30*4,矩阵行拼接

[row,col]=size(testdata);%30,4
% temp=[];
% for i=1:4:col-3
%     temp=[temp;testdata(i:i+3)]
% end
% testdata=temp;
testdata=(testdata-repmat(meandata,row,1))./(repmat(stddata,row,1));
meantestdata=mean(testdata);
vartestdata=var(testdata);
mediantestdata=median(testdata);

data=[meantestdata vartestdata mediantestdata];%1*12
data=data*V;%1*12

input=data(1:4)';%取data的1-4列元素转置给input,4*1

y=sim(net,input);
[row,col]=size(y);
for i=1:row
    for j=1:col
if y(i,j)>=0.5
    y(i,j)=1;
else
    y(i,j)=0;
end
    end
end
y=y';
if y==[0 0 0 1]
    kind='0x01';
elseif y==[0 0 1 0]
    kind='0x02';
elseif y==[0 1 0 0]
    kind='0x03';
elseif y==[1 0 0 0]
    kind='0x04';
else
    kind='0x00';
end

if strcmp(kind,'0x01')
    if meantestdata(2)>=40
        level='0x05';
    elseif meantestdata(2)>=30
        level='0x04';
    elseif meantestdata(2)>=20
        level='0x03';
    elseif meantestdata(2)>=10
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x02')
    if meantestdata(2)>=40
        level='0x05';
    elseif meantestdata(2)>=30
        level='0x04';
    elseif meantestdata(2)>=20
        level='0x03';
    elseif meantestdata(2)>=10
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x03')
    if meantestdata(2)>=40
        level='0x05';
    elseif meantestdata(2)>=30
        level='0x04';
    elseif meantestdata(2)>=20
        level='0x03';
    elseif meantestdata(2)>=10
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x04')
    if meantestdata(2)>=40
        level='0x05';
    elseif meantestdata(2)>=30
        level='0x04';
    elseif meantestdata(2)>=20
        level='0x03';
    elseif meantestdata(2)>=10
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x00')
    if meantestdata(2)>=40
        level='0x05';
    elseif meantestdata(2)>=30
        level='0x04';
    elseif meantestdata(2)>=20
        level='0x03';
    elseif meantestdata(2)>=10
        level='0x02';
    else
        level='0x01';
    end
end
kind
level
end



