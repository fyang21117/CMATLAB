clc
clear
load net1029;
V = load( 'data.mat');
a = struct2cell(V);
a=char(a);
row=size(a,1);
string=[a(1,:);a(2,:);a(3,:);a(4,:);a(5,:)];
DATA=[];
for i=1:1:row
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
target=0;
testdata=[col1 col2 col3 col4];

[row,col]=size(testdata);
if mean(testdata(2))<=1
    target=1;
end

testdata=(testdata-repmat(meandata,row,1))./(repmat(stddata,row,1));
meantestdata=mean(testdata);
vartestdata=var(testdata);
mediantestdata=median(testdata);
data=[meantestdata vartestdata mediantestdata];
DATA=[DATA;data];
end

input=DATA';
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
kind=[];
for i=1:1:col
if y(i,:)==[0 0 0 1]
    kind=[kind 1];
elseif  y(i,:)==[0 0 1 0]
    kind=[kind 2];
elseif  y(i,:)==[0 1 0 0]
    kind=[kind 3];
elseif  y(i,:)==[1 0 0 0]
    kind=[kind 4];
else
    kind=[kind 0];
end
end

if target==1
   kind=[kind 0];
end

level=[];
for i=1:1:size(kind,2)
    if kind(i)==1
        if meantestdata(2)>=40
            level=[level 5];
        elseif meantestdata(2)>=30
            level=[level 4];
        elseif meantestdata(2)>=20
            level=[level 3];
        elseif meantestdata(2)>=10
            level=[level 2];
        else
            level=[level 1];
            end
    elseif kind(i)==2
        if meantestdata(2)>=40
            level=[level 5];
        elseif meantestdata(2)>=30
            level=[level 4];
        elseif meantestdata(2)>=20
            level=[level 3];
        elseif meantestdata(2)>=10
            level=[level 2];
        else
            level=[level 1];
            end        
    elseif kind(i)==3
        if meantestdata(2)>=40
            level=[level 5];
        elseif meantestdata(2)>=30
            level=[level 4];
        elseif meantestdata(2)>=20
            level=[level 3];
        elseif meantestdata(2)>=10
            level=[level 2];
        else
            level=[level 1];
                end
    elseif kind(i)==4
        if meantestdata(2)>=40
            level=[level 5];
        elseifmeantestdata(2)>=30
            level=[level 4];
        elseif meantestdata(2)>=20
            level=[level 3];
        elseif meantestdata(2)>=10
            level=[level 2];
        else
            level=[level 1];
            end
    else
        level=[level 0];        
    end
end  

kind
level


