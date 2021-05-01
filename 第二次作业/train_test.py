import random

with open('news.csv','r',encoding='utf-8') as f:
    news_list = [e.strip() for e in f.readlines()[1:]]
train = []
test = []


for e in news_list:
    a = random.random()
    if a > 0.1:
        train.append(e)
    else:
        test.append(e)

def data_write(filename,filelist):
    with open(filename,'w',encoding='utf-8') as f:
        for file in filelist:
            f.write(file+'\n')
data_write('train.txt',train)
data_write('test.txt',test)