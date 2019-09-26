#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;
typedef struct Node *p;
typedef p List;
typedef p Position;

struct Node
{
    char element;
    Position next;
};

/*struct  Node
{
       int element;
       Position next;
       Position pre;
};*/
/*struct Node
{
       int Coe;
       int Expo;
       Position next;
};
*/
/*栈1<-2<-3<- 需要记录top,
Position createstock()
{
        Position s;
        s=malloc(sizeof(struct Node));
        s->next=NULL;
        return s;
}
Position pop(Position P,char element)
{
        Position temp;
        temp=malloc(sizeof(struct Node));
        temp->element=element;
        temp->next=P;
        return temp;
}
int Isemptystock(Position P)
{
        return P->next==NULL;
}
Position push(Position P)
{     if(Isemptystock(P))
        {return P;}
       else{ Position temp;
             temp=P->next;
             free(P);
             return temp;}
}
*、
//
/*Position Insert(int x, Position P)
 {

    Position Temple;
    Temple=malloc(sizeof(struct Node));
    Temple->element=x;
    Temple->next=P->next;
    P->next=Temple;
    return Temple;
}*/
/*int Islast(Position PP)
{
        return PP->next==NULL;
}
int Isempty(List L)
{
        return L->next==NULL;
}
Position findre(int x, List L)
{
        Position pp;
        pp=L;
        while(pp->next!=NULL && pp->next->element!=x)
        {
                pp->next=pp->next;
        }
        return pp;
}
Position Delete(int x,List L)
{
       Position temp,pp;
       pp=findre(x,L);
       if (!Islast(pp))
         {
                 temp=pp->next;
                 pp->next=temp->next;
                 free(temp);
         }
}
*/
/*
List insertPlo(Position P,List ll,Position PP )
{
    if(!Isempty(ll))
    { Position temp;
      temp=malloc(sizeof(struct Node));
      PP->next=temp;
      temp->Coe=P->Coe;
      temp->Expo=P->Expo;
      temp->next=NULL;
      return temp;}
     else {PP->Expo=P->Expo;
           PP->Coe=P->Coe;
           return PP;}
}
List combine(List L1,List L2)
{       List result,resultplos;
        result=malloc(sizeof(struct Node));
        result->next=NULL;
        resultplos=result;
        Position temp;
        while(L1!=NULL&&L2!=NULL)
          {if(L1->Expo>L2->Expo)
            {temp=L1;
            L1=L1->next;}
           else if(L1->Expo<L2->Expo)
            {temp=L2;
            L2=L2->next;}
           else{temp=L1;
                temp->Coe=L1->Coe+L2->Coe;
                L1=L1->next;L2=L2->next;}//L1中coe会改变
           resultplos=insertPlo(temp,result,resultplos);}
        return result;
}
*3.5求并集/
/* 3.1
void main()
{
        List L;
        Position p;
        L=malloc(sizeof(struct Node));
        L->element=1;
        L->next=NULL;
        p=L;
        for(int i=1;i<11;i++)
        {
                p=Insert(i,p);
        }
        p=L;
        while(p->next!=NULL)
        {
                printf("%d\n",p->element);
                p=p->next;
        }
}
*/
/* 3.3
void main()
{
        List L;
        Position P,PP,PPP;
        L=malloc(sizeof(struct Node));
        P=malloc(sizeof(struct Node));
        PP=malloc(sizeof(struct Node));
        PPP=malloc(sizeof(struct Node));
        L->element=1;
        L->next=P;
        P->element=2;
        P->next=PP;
        PP->element=3;
        PP->next=PPP;
        PPP->element=4;
        PPP->next=NULL;
        Position temp;
        temp=L->next;
        L->next=L->next->next;
        temp->next=L->next->next;
        L->next->next=temp;
        Position l;
        l=L;
        while (l!=NULL)
        {
            printf("%d\n",l->element);
            l=l->next;
        }

}
*/

/*3.3b
void main()
{
        List L;
        Position P,PP,PPP;
        L=malloc(sizeof(struct Node));
        P=malloc(sizeof(struct Node));
        PP=malloc(sizeof(struct Node));
        PPP=malloc(sizeof(struct Node));
        L->element=1;
        L->next=P;
        L->pre=NULL;
        P->element=2;
        P->next=PP;
        P->pre=L;
        PP->element=3;
        PP->next=PPP;
        PP->pre=P;
        PPP->element=4;
        PPP->next=NULL;
        PPP->pre=PP;
        Position temp;
        temp=P;
        P=P->next;
        P->pre=temp->pre;
        temp->pre=P;
        temp->next=P->next;
        temp->next->pre=temp;
        P->next=temp;
        P->pre->next=P;
        Position l;
        l=L;
        while (l!=NULL)
        {
            printf("%d\n",l->element);
            l=l->next;
        }

}
*/

/*中缀表达式变后缀
void main()
{  int i;
   Position opera;
   char strs[]="(1+(2*1)-2";
   printf("%s\n",strs);
   opera=createstock();
   //printf("%d",strlen(strs));
  // printf("%c",strs[0]);
   char str;
   for(i=0;i<(strlen(strs));i++)
   {
       str=strs[i];
      // printf("--%c--",str);
       if(str == ')'|| str == ']')
       {  while(opera->element!='('&& opera->element!='[')
          {
                printf("%c",opera->element);
                opera=push(opera);
           }
          opera=push(opera);
       }
       else if (str=='['|| str=='(' )
       { opera=pop(opera,str);}
       else {
               if((str=='+'||str=='-')&&(opera->element=='*'||opera->element=='/'))
               {
                       while(opera->element=='+'||opera->element=='-')
                           {printf("%c",opera->element);}               //压入低级，栈内高级
                        printf("%c",opera->element);
                        opera=push(opera);
                        opera=pop(opera,str);
                  }
               else{  //压入同级或高级
                       if(str=='*'||str=='/')
                       {
                               opera=pop(opera,str);//压入高级
                       }
                       else if(str=='+'||str=='-')
                       {      if(opera->element =='('||opera->element =='[')
                               { opera=pop(opera,str);}
                              else{
                                 printf("%c",opera->element);
                                 opera=push(opera);  //压入同级
                                 opera=pop(opera,str);}
                       }
                       else//数字
                       {       if(i==1)
                           {printf("***%d",i);
                            printf("%c",str);}
                               else{printf("%c",str);}
                             
                       }
                  }
            }
   }
  while(opera->element !=NULL)
      {if(opera->element=='['||opera->element=='('||opera->element==')'|| opera->element==']')
           {opera=push(opera);}
        else {
               printf("%c",opera->element);
                opera=push(opera);
        }
      }
  free(opera);

}*/


