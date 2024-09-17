#coding=utf-8
# -*- coding: utf-8 -*-  
#!/usr/bin/env python2.7

import numpy as np  
from numpy import *  # 导入科学计算包NumPy
from os import listdir  # 从os中导入函数，列出给定目录的文件名
import operator# 导入运算符模块

# 导入sklearn中的kNN算法
from sklearn import neighbors  
#from sklearn.metrics import precision_recall_curve  
#from sklearn.metrics import classification_report  
#from sklearn.cross_validation import train_test_split  
#import matplotlib.pyplot as plt  
 

## 将数据处理成分类器可以识别的格式 
## 将32×32的二进制图像矩阵转换为1×1024的向量
def img2vect(filename):  
	returnVect = zeros((1, 1024))   ##首先创建1×1024的Numpy数组
	fr = open(filename)
	for i in range(32):   ## 循环读出文件的前32行，并将每行的前32个字符值存储在Numpy数组中
		lineStr = fr.readline()
		for j in range(32):
			returnVect[0,32*i + j] = int(lineStr[j])
	return returnVect ## 最后返回数组



## 手写数字识别系统的测试代码
def handwritingClassTest(k):
	hwLabels = []
	trainingFileList = listdir('trainingDigits') ## 获取训练目录的内容
	m = len(trainingFileList) ## 获取训练样本个数
	trainingMat = zeros((m, 1024)) ## 矩阵每行存储一个train图像
	for i in range(m):
		fileNameStr = trainingFileList[i]  ##从训练数据文件名解析分类数字
		fileStr = fileNameStr.split('.')[0]
		classNumStr = int(fileStr.split('_')[0])
		hwLabels.append(classNumStr)
		trainingMat[i,:] = img2vect('trainingDigits/%s' % fileNameStr)

		## 训练KNN分类器  
	clf = neighbors.KNeighborsClassifier(algorithm='kd_tree', n_neighbors = k)  
	clf.fit(trainingMat, hwLabels)  	

	## 解析测试数据文件
	testFileList = listdir('testDigits')
	errorCount = 0.0  ## 统计识别错误的文件个数
	mTest = len(testFileList)  ## 测试样本个数
	for i in range(mTest):
		fileNameStr = testFileList[i]
		fileStr = fileNameStr.split('.')[0]
		classNumStr = int(fileStr.split('_')[0])
		vectorUnderTest= img2vect('testDigits/%s' % fileNameStr) ## 二进制图像转成向量
		##进行kNN分类
		classifierResult = clf.predict(vectorUnderTest)  	 
		print "the classifier came back with: %d, the real answer is %d" % (classifierResult, classNumStr)
		if (classifierResult != classNumStr): errorCount += 1.0
	
	print "\nthere are %d test instances " % mTest
	print "\nthe total number of errors is: %d " % errorCount
	print "\nthe total error rate is: %f " % (errorCount/float(mTest))
	print "\nAccuracy is: %2.2f%%" % ((1-errorCount/float(mTest))*100)	
	
