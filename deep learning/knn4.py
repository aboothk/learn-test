import torch
from torch.utils.data import DataLoader
import torchvision.datasets as dsets 
import torchvision.transforms as transforms 
import matplotlib.pyplot as plt
import operator
import numpy as np

class  Knn:
    def __int__(self):
        pass
    def fit(self,X_train,y_train):
        self.Xtr=X_train
        self.ytr=y_train
    def predict(self,k,dis,X_test):
        assert dis == 'E',or dis=='M' ,'dis must E or M'
        num_test=X_test.shape[0]
        labellist=[]
        if(dis=='E'):
            for i in range(num_test):
                distance=np.sqrt(np.sum(((self.Xtr-np.tile(X_test[i],(self.Xtr.shape[0],1)))**2),axis=1))
                nearest_k=np.argsort(distance)
                topK=nearset_k[:k]
                classCount={}
                for i in topK:
                    classCount[self.ytr[i]]=classCount.get(self.ytr[i],0)+1
                sortedClassCount=sorted(classCount.items(),key=operator.itemgetter(1),reverse=True)
                labellist.append(sortedClassCount[0][0])
            return np.array(labellist)
        if(dis=='M'):
            for i in range(num_test):
                distance=np.sum(np.abs(self.Xtr-np.tile(X_test[i],(self.Xtr.shape[0],1))),axis=1)
                nearest_k=np.argsort(distance)
                topK=nearset_k[:k]
                classCount={}
                for i in topK:
                    classCount[self.ytr[i]]=classCount.get(self.ytr[i],0)+1
                sortedClassCount=sorted(classCount.items(),key=operator.itemgetter(1),reverse=True)
                labellist.append(sortedClassCount[0][0])
            return np.array(labellis)

X_train=train_loader.dataset.train_data
X_train=X_train.reshape(X_train,shape[0],-1)
mean_image=getXmean(X_train)
X_train=centralized(X_train,mean_image)
y_train=train_loader.dataset.train_labels
y_train=np.array(y_train)
X_test=test_loader.dataset.test_data
X_test=X_test.reshape(X_test,shape[0],-1)
X_test=centralized(X_test,mean_image)
y_test=test_loader.dataset.test_labels
y_test=np.array(y_test)
print(X_train.shape)
print(y_train.shape)
print(X_test.shape)
print(y_test.shape)

num_folds=5
k_chioces=[1,3,5,8,10,12,15,20]
num_training=X_train.shape[0]
X_train_folds=[]
y_train_folds=[]
indices=np.array_split(np.arange(num_training),indices_or_sections=num_folds)
for i in indices:
    X_train_folds.append(X_train[i])