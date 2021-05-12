close all;clear all;clc;
% 纹理图像的灰度差分统计特征
J = imread('qiang.jpg');
A = double(J);
[m,n] = size(A);
B = A;
C = zeros(m,n);
for i=1:m-1
    for j=1:n-1
        B(i,j) = A(i+1,j+1);
        C(i,j) = abs(round(A(i,j)-B(i,j)));
    end
end
h = imhist(mat2gray(C))/(m*n);
mean = 0;con=0;ent=0;  %均值mean，对比度con，熵ent
for i=1:256
    mean = mean + (i*h(i))/256;
    con = con+i*i*h(i);
    if(h(i)>0)
        ent = ent-h(i)*log2(h(i));
    end
end
mean,con,ent