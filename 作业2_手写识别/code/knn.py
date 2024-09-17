#coding=utf-8
# -*- coding: utf-8 -*-  

from numpy import *  # 导入科学计算包NumPy
from os import listdir  # 从os中导入函数，列出给定目录的文件名
import operator# 导入运算符模块

# 创建数据集和标签
def createTrainDataSet():
    traindataset = array([[1.0,1.1], [1.0,1.0],[0,0],[0,0.1]])
    labels = ['A','A','B','B']
    return traindataset,labels

trdataset,labels = createTrainDataSet()
print 'Dataset: \n', trdataset
print 'Label: \n', labels
print 'Num of Instance: ', trdataset.shape[0]  # 返回数据集的行数，即样本个数
	
def kNN(newInput, dataSet, labels, k): ## inX是待分类测试样本，dataSet是训练样本，labels是训练样本标签
    dataSetSize = dataSet.shape[0] ## 行数，即样本个数   
    
    ## step 1: calculate Euclidean distance  
    # tile(A, reps): Construct an array by repeating A reps times  
    # the following copy numSamples rows for dataSet  
    diff = tile(newInput, (dataSetSize, 1)) - dataSet # Subtract element-wise  
    squaredDiff = diff ** 2 # squared for the subtract  
    squaredDist = sum(squaredDiff, axis = 1) # sum is performed by row  
    distances = squaredDist ** 0.5 # squared for the subtract  
    
    ## step 2: sort the distance  
    # argsort() returns the indices that would sort an array in a ascending order  
    ## 按距离排序的索引
    sortedDistIndicies = distances.argsort()  
    
    classCount = {}# define a dictionary (can be append element)    
    for i in range(k):  
        ## step 3: choose the min k distance  ## 选择距离最小的k个点
        voteIlabel = labels[sortedDistIndicies[i]]
        ## step 4: count the times labels occur  
        # when the key voteLabel is not in dictionary classCount, get()  
        # will return 0  
        classCount[voteIlabel] = classCount.get(voteIlabel,0) + 1
    
    ## step 5: the max voted class will return 
    sortedClassCount = sorted(classCount.iteritems(),key=operator.itemgetter(1),reverse=True) ##排序
    return sortedClassCount[0][0]
	


# 新测试样本为[0.6,0.3]
print 'Given test instance: [0.6, 0.3] \n', kNN([0.6,0.3],trdataset, labels, 3)

# 新测试样本为[1.2,0.8]
print 'Given test instance: [1.2, 0.8] \n', kNN([1.2,0.8],trdataset, labels, 3)