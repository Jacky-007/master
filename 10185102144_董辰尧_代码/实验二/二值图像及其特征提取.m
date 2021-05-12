%函数im2bw：把图像转换成二值图像
load trees;
BW=im2bw(X,map,0.4);
subplot(121),imshow(X,map),title('原图像');
subplot(122),imshow(BW),title('二值图像');

%函数bwarea:获取二值图像的面积
%计算图像circbw.tif在膨胀运算前后图像面积的改变
BW=imread('circbw.tif');
SE=ones(5);
BW1=imdilate(BW,SE);
subplot(121),imshow(BW),title('膨胀前图像');
subplot(122),imshow(BW1),title('膨胀后图像');
increase=(bwarea(BW1)-bwarea(BW))/bwarea(BW)


%函数bweuler:计算图像的欧拉数
%计算circles.png的欧拉数
BW = imread('circles.png');
imshow(BW);
bwarea(BW)