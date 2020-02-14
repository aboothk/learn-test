import torch
from torch.utils.data import DataLoader
import torchvision.datasets as dsets 
import torchvision.transforms as transforms 
from torch.autograd import Variable
import torch.nn as nn 
import numpy as np 

batch_size=100

train_dataset=dsets.CIFAR10(root ="ml/pycifar",train=True,transform=transforms.ToTensor(),download=True)
test_dataset=dsets.CIFAR10(root ="ml/pycifar",train=False,transform=transforms.ToTensor(),download=True)

train_loader=torch.utils.data.DataLoader(dataset=train_dataset,batch_size=batch_size,shuffle=True)
test_loader=torch.utils.data.DataLoader(dataset=test_dataset,batch_size=batch_size,shuffle=True)

input_size=3072
hidden_size=500
hidden_size2=200
num_classes=10
num_epochs=5
batch_size=100
learning_rate=0.001

class Net (nn.Module):
    def __init__(self,input_size,hidden_size,hidden_size2,num_classes):
        super (Net,self).__init__()
        self.layer1=nn.Linear(input_size,hidden_size)
        self.layer2=nn.Linear(hidden_size,hidden_size2)
        self.layer3=nn.Linear(hidden_size2,num_classes)
    def forward(self,x):
        out=torch.relu(self.layer1(x))
        out=torch.relu(self.layer2(out))
        out=self.layer3(out)
        return out
net =Net(input_size,hidden_size,hidden_size2,num_classes)
print(net)

learning_rate=1e-3
num_epoches=5
criterion =nn.CrossEntropyLoss()
optimizer=torch.optim.SGD(net.parameters(),lr=learning_rate)
for epoch in range(num_epoches):
    print('current epoch=%d' %epoch)
    for i, (images,labels) in enumerate (train_loader):
        images=Variable(images.view(images.size(0),-1))
        labels=Variable(labels)
        optimizer.zero_grad()
        outputs=net(images)
        loss=criterion(outputs,labels)
        loss.backward()
        optimizer.step()
        if i %100 ==0:
            print('current loss =%.5f' %loss.item())
print("finish training")

total=0
correct=0
for images,labels in test_loader:
     images=Variable(images.view(images.size(0),-1))
     outputs=net(images)
     _,predicts=torch.max(outputs.data,1)
     total +=labels.size(0)
     correct+=(predicts==labels).sum()
print('Accuracy = %.2f'% (100*correct/total)) 
    