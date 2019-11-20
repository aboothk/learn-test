#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TYPE htNode *
#define MAX_SZ 256

typedef struct _htNode{
    char symbol;
    struct _htNode *left,*right;
}htNode;

typedef struct _pQueueNode{
    TYPE val;//哈夫曼节树节点
    unsigned int priority;//优先级
    struct  _pQueueNode *next; //指向队列下一个元素，队列尾指向头指针
}pQueueNode;

//哈夫曼队列的结构 一个队列长度；一个头指针指向后面队列
typedef struct _pQueue{
    unsigned int size;
    pQueueNode *first;
}pQueue;

//哈夫曼树根节点
typedef struct _htTree
{
    htNode *root;
}htTree;

//哈夫曼表节点
typedef struct _hlNode
{
   char symbol;
   char *code;
   struct _hlNode *next;
}hlNode;

//哈夫曼表根节点
typedef struct _htTable
{
   hlNode *first;
   hlNode *last;
}hlTable;

//初始化哈夫曼队列
void initPQueue (pQueue **queue)
{     
     (*queue)=(pQueue *)malloc(sizeof(pQueue));
     (*queue)->first=NULL;
     (*queue)->size= 0;
     printf("1");
     return;
}
//哈夫曼队列
void addPQueue(pQueue **queue, TYPE val,unsigned int priority)
{
    if((*queue)->size == MAX_SZ)
    {
        printf("\nQueue is full.\n");
        return;
    }

    pQueueNode *aux=(pQueueNode *)malloc(sizeof (pQueueNode));
    aux->priority=priority;
    aux->val=val;
    
    //队列为空直接放与队列头
    if((*queue)->size==0||(*queue)->first==NULL)
    {
        aux->next= NULL;
        (*queue)->first=aux;
        (*queue)->size=1;
        return;}
    //否则排序小到大放入队列
    else
    {  if(priority<=(*queue)->first->priority)
        {//如果比队列头小的话，直接放到队列头
          aux->next=(*queue)->first;
          (*queue)->first=aux;
          (*queue)->size++;
          return;
    }
      else//否则迭代直到比它小的项
       {
       pQueueNode *iterator = (*queue)->first;
       while(iterator->next!=NULL)
       {
           if(priority<=iterator->next->priority)
           {
               aux->next=iterator->next;
               iterator->next=aux;
               (*queue)->size++;
               return;
           }
           iterator=iterator->next;
       }
          
        if(iterator->next==NULL)
           {
           aux->next=NULL;
           iterator->next=aux;
           (*queue)->size++;
           return;
           }
       } 
    }
}
//提取哈夫曼队列的第一个
TYPE getPQueue(pQueue **queue)
{
    TYPE returnValue;
    
    if((*queue)->size>0)
    {
        returnValue=(*queue)->first->val;
        (*queue)->first=(*queue)->first->next;
        (*queue)->size--;
    }
    else
    {
        printf("\nQueue is empty.\n");
    }
    return returnValue;
}  

//把哈夫曼树转变成哈夫曼表（1.使用递归遍历，左->右->节点顺序
void traverseTree(htNode *treeNode, hlTable **table, int k, char code[256])
{
    //递归终止条件,找到叶
    if(treeNode->left==NULL && treeNode->right == NULL)
    {
        code[k]='\0';
        hlNode *aux =(hlNode *)malloc(sizeof(hlNode));
        aux->code =(char *)malloc(sizeof(char)*(strlen(code)+1));
        strcpy(aux->code,code);
        aux->symbol=treeNode->symbol;
        aux->next =NULL;

        if((*table)->first ==NULL)
        {
            (*table)->first =aux;
            (*table)->last=aux;
        }
        else
        {
            (*table)->last->next=aux;
            (*table)->last=aux;
        }
    }
    //不是叶节点，继续寻找左子树
    if(treeNode->left!=NULL)
    {
        code[k]='0';
        traverseTree(treeNode->left,table,k+1,code);
    }
    //左子树遍历完毕，遍历右子树
    if(treeNode->right!=NULL)
    {
        code[k]='1';
        traverseTree(treeNode->right,table,k+1,code);
    }
}
//构建哈夫曼树函数
htTree *buildTree(char *inputstr)
{
    int *probability=(int *)malloc(sizeof(int)*256);
    //初始化probabilit数组的值
    for(int i=0;i<256;i++)
    {
        probability[i]=0;
    }
    //统计待编码的字符串各个字符出现的次数
    for(int j=0;inputstr[j]!='\0';j++)
    {
        probability[(unsigned char) inputstr[j]]++;
    
    }
    //构建哈夫曼队列
    pQueue *huffmanQueue; 
    initPQueue(&huffmanQueue);//初始化队列

    for(int k=0;k<256;k++)
    {
        if(probability[k]!=0)
        {
            htNode *aux= (htNode *)malloc(sizeof(htNode));
            aux->left=NULL;
            aux->right=NULL;
            aux->symbol=(char) k;

            addPQueue(&huffmanQueue,aux,probability[k]);
        }
    }
    //稀饭权重数组，已无用！
    free(probability);
    
    //生成哈夫曼树
    while(huffmanQueue->size!=1)
    {
        int priority= huffmanQueue->first->priority;
        priority+=huffmanQueue->first->next->priority;

        htNode *left=getPQueue(&huffmanQueue);
        htNode *right=getPQueue(&huffmanQueue);

        htNode *newNode =(htNode *)malloc(sizeof (htNode));
        newNode->left=left;
        newNode->right =right;

        addPQueue(&huffmanQueue,newNode,priority);
    }
    htTree *tree =(htTree *)malloc(sizeof (htTree));

    tree->root=getPQueue(&huffmanQueue);
    return tree;
}

//构建哈夫曼表函数
hlTable *buildTable(htTree *huffmanTree)
{
    hlTable *table=(hlTable *)malloc(sizeof(hlTable));
    table->first=NULL;
    table->last=NULL;

    char code[256];
    int k=0;

    traverseTree(huffmanTree->root,&table,k,code);
    return table;
}

//encode函数，编码
void encode(hlTable *table,char *stringToEncode)
{
    hlNode *traversal;
    printf("Encoding.......\n\nInput string : \n%s\nEncode string: \n",stringToEncode);

    for(int i=0; stringToEncode[i]!='\0';i++)
    {
        traversal =table->first;
        while(traversal->symbol!=stringToEncode[i])
            traversal=traversal->next;
        printf("%s",traversal->code);
    }
    printf("\n");
}

//decode函数，解码
void decode(htTree *tree,char *stringToDecode)
{
    htNode *traversal =tree->root;
    printf("\n\nDecoding.......\n\nInput string : \n%s\nDeconding string : \n",stringToDecode);
    
    //按编码找到第一个叶点，traversal指针重新指向根结点，直到编码数组遍历到最后一个
    for(int i=0;stringToDecode[i]!='\0';i++)
    {
        if(traversal->left ==NULL&&traversal->right ==NULL)
        {
            printf("%c",traversal->symbol);
            traversal=tree->root;
        }
        if(stringToDecode[i]=='0')
            traversal=traversal->left;
        if(stringToDecode[i]=='1')
           traversal=traversal->right;
        if(stringToDecode[i] !='0'&&stringToDecode[i]!='1')
        {
            printf("The input string is not coded correctly!\n");
            return;
        }
    }
    //树是空的话，报错
    if(traversal->left==NULL&&traversal->right ==NULL)
    {
        printf("The tree is wrong !");
    }
    return;
}

void main()
{  
   // char str;
    //getstr(str);
    htTree *codeTree=buildTree("I love fishC.com!");

    hlTable *codeTable=buildTable(codeTree);

    encode(codeTable,"I love fishC.com!");

    decode(codeTree,"0011111000111");
    
}