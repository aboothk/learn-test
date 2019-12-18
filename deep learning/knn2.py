import torch
from torch.utils.data import DataLoader
import torchvision.datasets as dsets 
import torchvision.transforms as transforms 
import matplotlib.pyplot as plt
import operator
import numpy as np


def getXmean(x_train):
    x_train = np.reshape(x_train, (x_train.shape[0], -1)) 
    mean_image = np.mean(x_train, axis=0)  
    return mean_image


def centralized(x_test, mean_image):
    x_test = np.reshape(x_test, (x_test.shape[0], -1))
    x_test = x_test.astype(np.float)
    x_test -= mean_image  
    return x_test



def createDataset():
    group=np.array([[1.0,2.0],[1.2,0.1],[0.1,1.4],[0.3,3.5],[1.1,1.0],[0.5,1.5]])
    labels=np.array(['A','A','B','B','A','B'])
    return group,labels

def kNN_classify(k,dis,X_train,x_train,Y_test):
    assert dis == 'E' or dis =='M', 'dis must E or M ,E代表欧式距离，M代表曼哈顿距离'
    num_test =Y_test.shape[0]
    labellist =[]
    if (dis == 'E'):
        for i in range(num_test):
            distances =np.sqrt(np.sum(((X_train-np.tile(Y_test[i],(X_train.shape[0],1)))**2),axis=1))
            nearest_k=np.argsort(distances)
            topK=nearest_k[:k]
            classCount ={}
            for i in topK:
                classCount[x_train[i]]=classCount.get(x_train[i],0)+1
            sortedClassCount = sorted(classCount.items(),key=operator.itemgetter(1),reverse=True)
            labellist.append(sortedClassCount[0][0])
        return np.array(labellist)
    else :
        for i in range(num_test):
           distances =np.sum(abs(X_train-np.tile(Y_test[i],(X_train.shape[0],1))),axis=1)
           nearest_k=np.argsort(distances)
           topK=nearest_k[:k]
           classCount ={}
           for i in topK:
                classCount[x_train[i]]=classCount.get(x_train[i],0)+1
           sortedClassCount = sorted(classCount.items(),key=operator.itemgetter(1),reverse=True)
           labellist.append(sortedClassCount[0][0])
        return np.array(labellist)
 


if __name__=='__main__':
    batch_size =100 
    train_dataset = dsets.MNIST(root = '/ml/pymnist',train=True,transform=None,download=True)
    test_dataset = dsets.MNIST(root ='/ml/pymnist',train=False,transform=None,download=True)
    train_loader = torch.utils.data.DataLoader(dataset=train_dataset,batch_size=batch_size,shuffle=True)
    test_loader=torch.utils.data.DataLoader(dataset=test_dataset,batch_size=batch_size,shuffle =True)
    X_train=train_loader.dataset.data.numpy()
    mean_image=getXmean(X_train)
    X_train=centralized(X_train,mean_image)
    y_train=train_loader.dataset.targets.numpy()
    X_test=test_loader.dataset.data[:1000].numpy()
    X_test=centralized(X_test,mean_image)
    y_test=test_loader.dataset.targets[:1000].numpy()
    num_test=y_test.shape[0]
    y_test_pred=kNN_classify(5,'M',X_train,y_train,X_test)
    num_correct=np.sum(y_test_pred==y_test)
    accuracy=float(num_correct)/num_test
    print('Go %d / %d correct =>accuracy : %f' %(num_correct,num_test,accuracy))