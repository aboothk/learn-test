import numpy as np 
import matplotlib.pyplot as plt
import operator
def createDataset():
    group=np.array([[1.0,2.0],[1.2,0.1],[0.1,1.4],[0.3,3.5],[1.1,1.0],[0.5,1.5]])
    labels=np.array(['A','A','B','B','A','B'])
    return group,labels
'''if __name__== "__main__":
    group,labels =createDataset()
    plt.scatter(group[labels=='A',0],group[labels=='A',1],color= 'r',marker='*')
    plt.scatter(group[labels=='B',0],group[labels=='B',1],color='g',marker='+')
    plt.show()'''

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

if __name__=='__main__':
    group,labels =createDataset()
    plt.scatter(group[labels=='A',0],group[labels=='A',1],color='r',marker='*')
    plt.scatter(group[labels=='B',0],group[labels=='B',1],color = 'g',marker='+')
    plt.show()
    y_test_pred=kNN_classify(1,'E',group,labels,np.array([[1.0,2.1],[0.4,2.0]]))
    print(y_test_pred)