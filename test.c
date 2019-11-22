#include<stdio.h>
void main()
<<<<<<< HEAD
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
   
   
   
    
=======
{
    int a[59];
    for(int i=0;i<58;i++)
    {
        a[i]=i;
    }
    char b[]="1234";
    printf("%c",b[2]);
    printf("%d",a[2]);
    printf("%d", a[(unsigned char) b[2]]);
>>>>>>> 87a71e96c379a0b63fc536a533716d4cac099bc0
}
