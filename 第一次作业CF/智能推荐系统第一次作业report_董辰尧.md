# 智能推荐系统第一次编程作业实验报告

## 																												-------------基于内存的协同过滤

[TOC] 

## 1. 算法简介

### **1.1 简介**

协同过滤推荐算法，（英文名：Collaborative Filtering，简称CF），其核心思想是物以类聚，人以群分。具有相同或相似的价值观、思想观、知识水平和兴趣偏好的用户，其对信息的需求也是相似的。

跟你喜好相似的人喜欢的东西你也很有可能喜欢 ：基于用户的协同过滤推荐（User-based CF）跟你喜欢的东西相似的东西你也很有可能喜欢 ：基于物品的协同过滤推荐（Item-based CF）。本次实验我用的是基于用户的协同过滤算法。

### 1.2 算法实现简单描述 

+ 对于某一个我们想要进行推荐or预测用户（以下称之为目标用户），我们需要先找到和他比较像的人（他的邻居）

  > 在这里比较像指的是目标用户和其他用户对相同物品做出过评价，并且对于目标物品来说，目标用户尚未作出评价，但是邻居做出了评价

+ 根据他和他邻居的相似度（在这里我用了皮尔森相似度）计算预测结果

## 2. 核心代码注解

### 1.1 数据读取以及预处理 

+ 先读取数据，结果发现给的数据类型是这样的

  ```python
  # 使用read_csv来读取csv，默认分隔符为逗号
  pd.read_csv('train.csv')
  
  
  user_id	business_id	date	stars
  0	A2JGzkvNjckSmps_4FbKWw	Xg5qEQiB-7L6kGJ5F4K3bQ	2014-03-18 01:14:10	5.0
  1	rypcWiSNGM0suWsiSLh9xA	4RoTEeqB_MNn6yaqZmlZHg	2015-08-29 18:32:15	4.0
  2	Dgk0Wdoh7HPjhKQEPBU_jQ	ZOmf-3NN4Z59b2Fw6VAM7g	2015-09-14 16:33:03	3.0
  3	FIk4lQQu1eTe2EpzQ4xhBA	HK2Ki-PvnNN-YMTlX1uSVA	2012-09-29 02:03:42	4.0
  4	VizhcyMWWPz3UDXEBeix4w	UPIYuRaZvknINOd1w8kqRQ	2011-06-10 20:35:42	3.0
  ...	...	...	...	...
  7927	1O638BDK_fWuxgTVJwff-A	ZIUs7gncPOX0OXr1ZYviAQ	2008-05-01 22:52:19	5.0
  7928	rypcWiSNGM0suWsiSLh9xA	sk0stgY4NDJYOX1MbNJ3Pg	2016-07-13 00:18:24	4.0
  7929	qibGLHABNReGeJr2w4_8yQ	LtNgP4FqXp5nMFOHErK8cw	2012-06-16 02:15:50	3.0
  7930	1dWLN4Mr4hKhu8MQUCKqXQ	o597EK6uvR5RuPMZEwYCUg	2013-12-06 16:57:33	4.0
  7931	pQdIIsbV5dGOVz_kWfMRTw	nzV7HlERvD_v1DEfL_oiGQ	2008-03-31 01:08:57	1.0
  7932 rows × 4 columns
  ```

  

+ 为了更好地使用这些数据，我把他转换成了一个矩阵，纵索引是user_id，横索引是business_id，内容（key值）是用户的打分item。

  ```python
  data_path = 'train.csv'
  dtype = {"user_id":np.string_, "business_id":np.string_, "stars":np.float32}
  # 加载数据，我们只用三列数据，分别是用户ID，商品ID，评分
  ratings = pd.read_csv(data_path, dtype=dtype, usecols=[0,1,3])
  ratings_matrix = ratings.pivot_table(index=["user_id"], columns=["business_id"], values="stars")
  ratings_matrix        
  ```
  
  

* 之后我用新矩阵ratings_matrix，计算了两个新矩阵，分别是平均值矩阵ratings_matrix_mean，皮尔森相关系数矩阵similarity，其中平均值矩阵用来计算没有任何邻居的用户的评分，皮尔森相关系数矩阵用于后面计算有邻居用户的评分。

  ```python
  ratings_matrix_mean = ratings_matrix.mean(axis=1)
  #平均值矩阵，用于预测没有“朋友”的用户的评分
  ratings_matrix_mean
  ```

  ```python
  similarity = ratings_matrix.T.corr(method = 'pearson')
  similarity #相似矩阵，里面有所有用户之间的person相似度，用于最后predict函数计算
  ```

### 2.2 计算预测值 

这一部分是核心部分，我用了一个函数实现，函数输入是目标用户id还有物品id ，以及刚刚计算出的ratings_matrix、similarity矩阵。在函数开头部分寻找目标用户的邻居的集合，如果没有邻居就输出-1，表示没有。如果该用户有邻居，就可以进行最终的预测计算，这里注意根据不同的相似度，需要进行加权平均。

+ 找邻居的部分

  ```python
  def predict(uid, iid, ratings_matrix, user_similar):
      '''
      预测给定用户对给定物品的评分值
      :param uid: 用户ID
      :param iid: 物品ID
      :param ratings_matrix: 用户-物品评分矩阵
      :param user_similar: 用户两两相似度矩阵
      :return: 预测的评分值
      '''
      # 找出uid用户的相似用户
      similar_users = user_similar[uid].drop([uid]).dropna()
      similar_users = similar_users.where(similar_users>0).dropna()
      if similar_users.empty is True:  #当该用户没有邻居输出0
          return -1 
  
      # 从uid用户的近邻相似用户中筛选出对iid物品有评分记录的近邻用户
      ids = set(ratings_matrix[iid].dropna().index)&set(similar_users.index)
      finally_similar_users = similar_users.ix[list(ids)]
      if finally_similar_users.empty: #当该用户邻居没有评分输出0
          return -1
      # 结合uid用户与其近邻用户的相似度预测uid用户对iid物品的评分
  ```

+ 计算预测值部分

  ```python
   	sum_up = 0    
      sum_down = 0   
      for sim_uid, similarity in finally_similar_users.iteritems():
          # 近邻用户的评分数据
          sim_user_star = ratings_matrix.ix[sim_uid].dropna()
          # 近邻用户对iid物品的评分
          sim_user_rating_for_item = sim_user_star[iid]
          # 计算分子的值
          sum_up += similarity * sim_user_rating_for_item
          # 计算分母的值
          sum_down += similarity
  
      # 计算预测的评分值并返回
      predict_rating = sum_up/sum_down
      return round(predict_rating, 2)
  ```

### 2.3 对test集的预测，以及后续处理 

+ 读取test集 

  ```python
  data_path = 'test.csv' #读取test集
  ratings2 = pd.read_csv(data_path, dtype=dtype, usecols=[0,1])
  ratings2
  ```

+ 打印结果 

  ```python
  #打印结果
  for row in ratings2.itertuples():
      uid = getattr(row, 'user_id')
      iid = getattr(row, 'business_id')
      outcome = predict(uid, iid,ratings_matrix, similarity)
      if outcome != -1:
          print(uid,iid,outcome)# 如果有预测值就输出
      else:
          print(uid,iid,ratings_matrix_mean[uid]) #如果没有预测值就输出历史平均值
  ```

  

+ 将结果保存 

  ```python
  # 写入结果，保存在result.csv上
  import csv
  
  # 创建文件对象
  f = open('result.csv','w',encoding='utf-8',newline='' "")
  
  # 基于文件对象构建 csv写入对象
  csv_writer = csv.writer(f)
  
  # 构建列表头
  csv_writer.writerow(["user_id","business_id","stars"])
  
  # 写入csv文件内容
  for row in ratings2.itertuples():
      uid = getattr(row, 'user_id')
      iid = getattr(row, 'business_id')
      outcome = predict(uid, iid,ratings_matrix, similarity)
      if outcome != -1:
          csv_writer.writerow([uid,iid,outcome])# 如果有预测值就输出
      else:
          csv_writer.writerow([uid,iid,ratings_matrix_mean[uid]]) #如果没有预测值就输出历史平均值
  # 5. 关闭文件
  f.close()
  ```
  
  

## 3. 对结果的分析

### 3.1 皮尔森相关系数的意义

如果有两个变量：X、Y，最终计算出的相关系数的含义可以有如下理解：

1. 当相关系数为0时，X和Y两变量无关系。
2. 当X的值增大（减小），Y值增大（减小），两个变量为正相关，相关系数在0.00与1.00之间。
3. 当X的值增大（减小），Y值减小（增大），两个变量为负相关，相关系数在-1.00与0.00之间。

本次实验算出的相关系数都是正数，说明是正相关。

相关系数的绝对值越大，相关性越强，相关系数越接近于1或-1，相关度越强，相关系数越接近于0，相关度越弱。
通常情况下通过以下取值范围判断变量的相关强度：

+ 0.8-1.0   极强相关
+ 0.6-0.8   强相关
+ 0.4-0.6   中等程度相关
+ 0.2-0.4   弱相关
+ 0.0-0.2   极弱相关或无相关

### 3.2 矩阵稀疏问题

很遗憾的是本次数据集转换成ratings_matrix出现了大片大片的'NaN'，说明矩阵过于稀疏，有大部分的用户都找不到邻居。

> 降低数据的稀疏性问题给推荐系统带来的影响，人们专门研究了很多的解决方法。其中从不同角度对用户和产品信息进行分析、处理、降低数据的稀疏程度。基于项目的协同过滤推荐、降维法、智能Agent方法可以在一定程度上缓解数据稀疏性问题。BP神经网络缓解协同过滤推荐算法的稀疏性问题，将奇异值分解应用到协同过滤推荐算法，通过奇异值分解算法得到低维正交矩阵，较好地解决了数据稀疏性问题，但是推荐的准确性会有一定的下降。在采用神经网络模型进行聚类处理的总思路下，通过寻找基于对象属性信息的项目类间隐性联系化解数据稀疏性对高维数据聚类的影响。此外，应用聚类算法是解决用户—项目评分矩阵稀疏性的比较有效的方法。

我对矩阵的分解等做了简单的尝试，但都以失败告终。期待老师公布答案的做法。

### 3.3 时间数据利用问题

本次实验并没有对训练样本中给出的时间进行任何处理，这是因为我并不知道应该怎么利用。但是关于时间的处理我有一定的构思。

+ 时间离现在越近的评分，我们可以认为他比时间离现在更远的评分更加具有代表意义。所以可以设置一个和距现在时间长度正相关的衰减系数。
+ test数据集并不是让你预测现在时间的评分，而是某个特定时间，所以可以根据时间衰减系数算出每一年的相似矩阵，根据test数据集里时间的年份来确定使用哪一年的相似矩阵。

## 4.总结

### 4.1 心得

这次实验学到了很多东西，我花了不少时间在研究如何处理数据上，pandas使用更加熟练。初步实现了一个简单的入门级智能推荐系统算法，尽管代码中还有很多可以加强的地方，但是仍然使我对智能推荐系统有了更深刻的理解。

### 4.2 作业上交内容

+ 实验报告

  > 智能推荐系统第一次作业report_董辰尧.md

+ 可运行的代码

  > CF.ipynb

+ 训练集，测试集

  > train.csv、test.csv为了确保提交的代码可运行

+ 最终结果

  > result.csv

### 4.3 参考文献

https://blog.csdn.net/chaiqunxing51/article/details/50977195

> 稀疏矩阵处理

https://www.cnblogs.com/hxsyl/p/4000756.html

> 皮尔森相关系数的理解

https://blog.csdn.net/zolalad/article/details/51104745

> 皮尔森相关系数推荐

