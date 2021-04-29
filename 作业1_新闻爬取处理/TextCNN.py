#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   TextCNN.py
@Time    :   2021/04/26 22:39:29
@Author  :   SleepyPiggy 
@Blog    :   sleepypiggy.life
'''
# here put the import lib

import jieba
import torch
import torch.nn as nn
import torch.nn.functional as F
from tqdm import trange, tqdm

# 数据预处理
vocab = {}
vocab['[PAD]'] = 0
# 参数设置
device = 'cuda' if torch.cuda.is_available() else 'cpu'
seq_len = 25  # 每句话的长度
embedding_size = 150  # word2vec的维度
kernel_num = 75  # 每一种卷积核的个数
Kernel_list = [2, 3, 4, 5,6]  # N-gram
class_num = 9  # 分类的个数
epoches = 1500  #训练次数
lr = 0.001  # 学习率


def pro_vocab(path):
    with open(path, 'r', encoding='utf-8') as f:
        L = [e.strip() for e in f.readlines()]
        for news in L:
            news = news[2:]
            for word in news:
                if word not in vocab:
                    vocab[word] = len(vocab)


pro_vocab('train.txt')
pro_vocab('test.txt')

vocab_size = len(vocab)


def word2ids(text):  # 将数据转化成数字id 并多退少补
    ids = [vocab[word] for word in text]
    if len(ids) < seq_len:
        ids += [0] * (seq_len - len(ids))
        return ids
    else:
        return ids[:seq_len]


def load_data(path):  # 读取训练集和测试集
    with open(path, 'r', encoding='utf-8') as f:
        turples = [(int(sentence[0]), word2ids(sentence[2:].strip()))
                   for sentence in f.readlines()]
    labels = []
    texts = []
    for turple in turples:
        labels.append(turple[0])
        texts.append(turple[1])
    # 返回标签和经过预处理的文本
    return texts, labels


train_x, train_y = load_data('train.txt')
test_x, test_y = load_data('test.txt')
train_x = torch.LongTensor(train_x).to(device)
train_y = torch.LongTensor(train_y).to(device)
test_x = torch.LongTensor(test_x).to(device)


class TextCNN(nn.Module):
    def __init__(self):
        super(TextCNN, self).__init__()
        V = vocab_size
        E = embedding_size
        Ci = 1  # 输入数据的通道数
        Co = kernel_num  # 每一种卷积核的数目
        Kl = Kernel_list  # N-gram
        C = class_num  #输出的维度

        self.embed = nn.Embedding(V, E)
        self.convs = nn.ModuleList([nn.Conv2d(Ci, Co, (K, E)) for K in Kl])
        self.fc = nn.Linear(len(Kl) * Co, C)

    def forward(self, x):
        x = self.embed(x)  # (N, seq_len, E)

        x = x.unsqueeze(1)  # (N, Ci = 1, seq_len, E)

        x = [F.relu(conv(x)).squeeze(3)
             for conv in self.convs]  # [(N, Co, seq_len-ki+1), ...]*len(Ks)

        x = [F.max_pool1d(i, i.size(2)).squeeze(2)
             for i in x]  # [(N, Co), ...]*len(Ks)
        x = torch.cat(x, 1)
        out = F.softmax(self.fc(x), dim=1)
        return out


model = TextCNN().to(device)  #实例化模型
criterion = nn.CrossEntropyLoss().to(device)  #定义损失函数，为交叉熵损失
optimizer = torch.optim.Adam(model.parameters(), lr=lr)  #使用随机梯度下降算法，学习率为lr

for epoch in trange(epoches):
    pred = model(train_x)
    loss = criterion(pred, train_y)
    if (epoch + 1) % 100 == 0:
        print(loss.item())
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

pred_y = model(test_x)
L = pred_y.tolist()
total = len(L)
acc = 0
for i, pred in enumerate(L):
    max_index = pred.index(max(pred))
    if max_index == test_y[i]:
        acc += 1

print(acc / total * 100, '%')
