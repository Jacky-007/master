# -*- coding: utf-8 -*-  
from numpy import *  # 导入科学计算包NumPy
from os import listdir  # 从os中导入函数，列出给定目录的文件名
import operator# 导入运算符模块

######################################
## 构建使用kNN的手写数字识别系统
######################################


## kNN 算法，计算一个输入测试数据inX与已知样本的距离，并返回类别标签
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
def handwritingClassTest():
    hwLabels = []
    trainingFileList = listdir('trainingDigits') ## 获取训练目录的内容
    m = len(trainingFileList) ## 获取训练样本个数
    trainingMat = zeros((m, 1024)) ## 矩阵每行存储一个图像
    for i in range(m):
        fileNameStr = trainingFileList[i]  ##从训练数据文件名解析分类数字
        fileStr = fileNameStr.split('.')[0]
        classNumStr = int(fileStr.split('_')[0])
        hwLabels.append(classNumStr)
        trainingMat[i,:] = img2vect('trainingDigits/%s' % fileNameStr)
    
    ## 解析测试数据文件
    testFileList = listdir('testDigits')
    errorCount = 0.0  ## 统计识别错误的文件个数
    mTest = len(testFileList)  ## 测试样本个数
    for i in range(mTest):
        fileNameStr = testFileList[i]
        fileStr = fileNameStr.split('.')[0]
        classNumStr = int(fileStr.split('_')[0])
        vectorUnderTest = img2vect('testDigits/%s' % fileNameStr) ## 二进制图像转成向量
        classifierResult = kNN(vectorUnderTest, trainingMat, hwLabels, 3) ##进行kNN分类
        print "the classifier came back with: %d, the real answer is %d" % (classifierResult, classNumStr)
        if (classifierResult != classNumStr): errorCount += 1.0
    print "\nthere are %d test instances " % mTest
    print "\nthe total number of errors is: %d " % errorCount
    print "\nthe total error rate is: %f " % (errorCount/float(mTest))
    print "\nAccuracy is: %2.2f%%" % ((1-errorCount/float(mTest))*100)  
        
    

    
