//AVL树，按顺序插入2,1,4,5,9,3,6,7

#include<stdio.h>
#include<stdlib.h>

int Max(int a,int b)
{
return a>=b?a:b;
}
typedef struct _avltree
{
     int element;
     struct  _avltree *lchild;
     struct  _avltree *rchild;
     int height;    
}tree;

int Height( tree *P)
{
    if(P==NULL)
        return -1;
    else 
        return P->height;
}

//左右单旋转
//            [K2]                                 [K1]
//           /   \                                /   \ 
//          /     \                              /     \ 
//        K1      ZZ  ----------------->       XX       K2
//       /  \     ZZ                           xX      /  \ 
//      /    \                                 XX     /    \ 
//    XX     YY                                XX    YY    ZZ
//    Xx     YY                                      YY    ZZ
//    XX
//    XX
//    左
//      [K1]                                             [K2]
//      /  \                                             /  \ 
//     /    \                                           /    \ 
//   xx      K2 ---------------------->               K1      ZZ
//   xx     / \                                      / \      ZZ
//         /   \                                    /   \     ZZ
//        YY   ZZ                                  XX    YY   zZ
//        YY   ZZ                                  XX    YY
//             ZZ
//             ZZ
//右
//
//
tree *Singleft(tree * K2)
{
    tree *K1;
    K1=K2->lchild;
    K2->lchild=K1->rchild;
    K1->rchild=K2;

    K2->height=Max(Height(K2->lchild),Height(K2->rchild)) +1;
    K1->height=Max(Height(K1->lchild),K2->height) +1;
    return K1;
}

tree *Singright(tree * K1)
{
    tree *K2;
    K2=K1->rchild;
    K1->rchild=K2->lchild;
    K2->lchild=K1;
    K1->height=Max(Height(K1->lchild),Height(K1->rchild)) +1;
    K2->height=Max(Height(K2->lchild),K1->height) +1;
    return K1;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
tree *doubleleft(tree *K3)
{
     K3->lchild=Singright(K3->lchild);
     return Singleft(K3);
}

tree *doubright(tree *K1)
{
    K1->rchild=Singleft(K1->rchild);
    return Singright(K1);
}

tree *insert(int x,tree *T)
{
    if(T==NULL)
    {
        T=(tree *)malloc(sizeof(tree));
        if(T==NULL)
              printf("out of space!");
        else 
        {
            T->element=x;
            T->height=0;
            T->lchild=NULL;
            T->rchild=NULL;
        }
    }
    else if(x < T->element)
    {
        T->lchild=insert(x,T->lchild);
        if(Height(T->lchild)-Height(T->rchild)==2)
           if(x<T->lchild->element)
                T=Singleft(T);
            else
                T=doubleleft(T);
    }
    else
    if (x >T->element)
    {
        T->rchild=insert(x,T->rchild);
        if(Height(T->rchild)-Height(T->lchild)==2)
            if(x >T->rchild->element)
               T=Singright(T);
            else
               T=doubright(T);
    }
    T->height=Max(Height(T->lchild),Height(T->rchild)) +1;
    return T;
}

void printree(tree * root)
{
    if(root!=NULL)
    {
    printree(root->lchild);
    printree(root->rchild);
    printf("\n%d",root->element);
    }
    return;
}
void main()
{     //int s;
      //scanf("%d",&s);
      tree * Tree;
      Tree=NULL;
      int s[8]={2,1,4,5,9,3,6,7};
      for(int j=0;j<8;j++)
      {
         Tree=insert(s[j],Tree);
         if(j==4)
           printf("%d",Tree->rchild->element);
      }
      printree(Tree);
      
}