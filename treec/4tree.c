// 表达式树，读入一个后缀表达式，生成一个表达树，采用后序遍历重新生成一个后缀表达式
#include<stdio.h>
#include<stdlib.h>

typedef struct _htNode
{
    char symbol;
    struct  _htNode *lchild, *rchild;
}htNode;

typedef struct Strock
{
    htNode *root;
    struct Strock *next;
}htstock;

//出栈
htNode *pushstock(htstock **stockfir)
{   htstock *temp;
    temp=*stockfir;
    *stockfir=(*stockfir)->next;
    return temp->root;
}

//入栈
void  popstock(htstock **stockfir, htNode *nodetemp)
{
    htstock *temp=(htstock *)malloc(sizeof(htstock));
    temp->root=nodetemp;
    temp->next=*stockfir;
    *stockfir=temp;
}

htNode *getTree(char *express)
{   //生成栈头
    htstock *stockfirst =(htstock *)malloc(sizeof(htstock));
    stockfirst->next=NULL;
    stockfirst->root=NULL;  

    //遍历字符串，如果是操作数压入栈中，如果是操作符从栈中弹出两个元素，
    //生成一个新树，然后压入栈中,然后返回根节点
    for(int j=0;express[j]!='\0';j++)
    {   printf("%c",express[j]);
        if(express[j]=='+'||express[j]=='-'||express[j]=='*'||express[j]=='/')
        {
            htNode *Node=(htNode *)malloc(sizeof(htNode));
            Node->symbol=express[j];
            Node->rchild=pushstock(&stockfirst);
            Node->lchild=pushstock(&stockfirst);//出栈，入栈
            popstock(&stockfirst,Node);
        }
        else
        {
            htNode *Node=(htNode *)malloc(sizeof(htNode));
            Node->symbol=express[j];
            Node->rchild=NULL;
            Node->lchild=NULL;
            popstock(&stockfirst,Node);
        }
    }
    return stockfirst->root;
}

void printtree(htNode *tree)
{
    if(tree!=NULL)
    {
    printtree(tree->lchild);
    printtree(tree->rchild);
    printf("\n%c",tree->symbol);
    }
    return;
}



void main()
{ 
    htNode *Treeroot=getTree("ab+cde+**");
    printtree(Treeroot);
}