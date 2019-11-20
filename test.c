#include<stdio.h>
void main()
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
}
