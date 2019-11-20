#include<stdio.h>
void main()
{  
     struct Node
      {
        int x;
        char y;
      };
   struct test
   {
    struct Node *node;
    struct test *next;
   };
   struct test *test1=(struct test *)malloc(sizeof(struct test));
   test1->next=NULL;
   test1->node->x=1;
   test1->node->y='1';
   struct Node *node2=(struct Node *)malloc(sizeof(struct Node));
   node2->y='2';
   node2->x=2;
   struct test *temp;
   temp=test1;
   test
   
   
   
    
}
