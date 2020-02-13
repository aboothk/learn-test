import torch 
from torch.utils.data import DataLoader
import torchvision.datasets as dsets 
import torchvision.transforms as transforms 
import torch.nn as nn
from torch.autograd import Variable
import numpy as np 

batch_size =100

train_dataset=dsets.MNIST(root ="\\pymnist",train=True,transform=transforms.ToTensor(),download=True)
test_dataset=dsets.MNIST(root="\\pymnist",train=False,transform=transforms.ToTensor(),download=True)

train_loader = torch.utils.data.DataLoader(dataset=train_dataset,batch_size=batch_size,shuffle=True)
test_loader = torch.utils.data.DataLoader(dataset=test_dataset,batch_size=batch_size,shuffle=True)

print("train_data:",train_dataset.data.size())
print("train_labels:",train_dataset.targets.size())
print("test_data:",test_dataset.data.size())
print("test_labels:",test_dataset.targets.size())

print("批次的尺寸：",train_loader.batch_size)
print("load_train_data:",train_loader.dataset.data.shape)
print("load_train_labels:",train_loader.dataset.targets.shape)


input_size=784
hidden_size=500
num_classes=10
class Neural_net(nn.Module):
    def __init__(self,input_num,hidden_size,out_put):
        super(Neural_net,self).__init__()
        self.layer1=nn.Linear(input_num,hidden_size)
        self.layer2=nn.Linear(hidden_size,out_put)
    def forward(self,x):
        out=self.layer1(x)
        out=torch.relu(out)
        out=self.layer2(out)
        return out 
net =Neural_net(input_size,hidden_size,num_classes)
print(net)

learning_rate=1e-1
num_epoches=5
criterion=nn.CrossEntropyLoss()
optimizer=torch.optim.SGD(net.parameters(),lr=learning_rate)
for epoch in range (num_epoches):
    print("current epoch =%d"% epoch)
    for i , (images,labels) in enumerate (train_loader ):
        images =Variable (images.view(-1,28*28))
        labels=Variable(labels)
        output=net(images)
        loss=criterion(output,labels)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if i % 100 == 0 :
            print('current loss =%.5f' % loss.item())
print("finish training")

total=0
correct=0
for images,labels in test_loader:
    images=Variable(images.view(-1,28*28))
    outputs=net(images)
    _, predicts=torch.max(outputs.data,1)
    total+=labels.size(0)
    correct+=(predicts==labels).sum()
print('Accuracy =%.2f' % (100 * correct/total))
