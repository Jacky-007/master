%边缘检测
I=imread('circuit.tif'); %读入图像
%进行边缘检测
BW1=edge(I,'prewitt'); %采用prewitt算子进行边缘检测
BW2=edge(I,'canny'); %采用canny算子进行边缘检测
subplot(1,3,1),imshow('circuit.tif')%显示
subplot(1,3,2),imshow(BW1);%显示
subplot(1,3,3),imshow(BW2);%显示



%Harris角点
%确定待检测的图像区域并显示
I=imread('pout.tif');
I=I(1:150,1:120);
subplot(1,2,1);
imshow(I);
title('输入图像');

%对图像进行Harris角点提取
CM=cornermetric(I);

%查找矩阵中最大值并显示
corner_peaks=imregionalmax(CM);
corner_idx=find(corner_peaks==true);
[r g b]=deal(I);
r(corner_idx)=255;
g(corner_idx)=255;
b(corner_idx)=0;
RGB=cat(3,r,g,b);
subplot(1,3,3);
imshow(RGB);
title('图像中的角点');



%SURF特征提取
%读入图像;
I=imread('cameraman.tif');
%对输入的图像检测SURF特征;
points=detectSURFFeatures(I);
%显示最强的十个SURF特征点;
imshow(I);hold on;
plot(points.selectStrongest(10));
