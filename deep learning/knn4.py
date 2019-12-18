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
y_train_folds.append(y_train[i])
k_to_accuracies={}
for k in k_choices:
    acc=[]
    for i in range(num_folds):
        x=X_train_folds[0:i]+X_train_folds[i+1:]
        x=np.concatenate(x,axis=0)

        y=y_train_folds[0:i]+y_train_folds[i+1:]
        y=np.concatenate(y)
        test_x=X_train_folds[i]
        test_y=y_train_folds[i]

        classifier=Knn()
        classifier.fit(x,y)
        y_pred=classifier.predict(k,'M',test_x)
        accuracy=np.mean(y_pred==test_y)
        acc.append(accuracy)
k_to_accuracies[k]=acc

for k in sorted(k_to_accuracies):
    for accuracy in k_to_accuracies[k]:
        print('k=%d,accuracy=%f' %(k,accuracy))

for k in k_chioces:
    accuracies=k_to_accuracies[k]
    plt.scatter([k]*len(accuracies),accuracies)

accuracies_mean=np.array([np.mean(v) for k,v in sorted(k_to_accuracies.items())])
accuracies_std=np.array([np.std(v) for k,v in sorted(k_to_accuracies.items())])
plt.errorbar(k_chioces,accuracies_mean,yerr=accuracies_std)
plt.title('Cross-validation on k')
plt.xlabel('k')
plt.ylabel('Cross-validation accuracy')
plt.show()