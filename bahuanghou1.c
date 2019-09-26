#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int count=0;
int chess[8][8];
int check(int y,int x)
{ int  k;
for(k=-8;k<=8;k++){//两对角线
 if(y+k>=0&&y+k<8&&x+k>=0&&x+k<8)//从左上到右下对角线
      if(chess[y+k][x+k]==1) return 0;
if(y-k>=0&&y-k<8&&x+k>=0&&x+k<8)//从左下到右上对角线
      if(chess[y-k][x+k]==1) return 0;
}
for (k=0;k<8;k++)//同一列
{
    if(chess[k][y]==1||chess[x][k]==1)
       return 0;
}
return 1;
}
void queen(int y,int x)
{
    if(x>=8)
    {
        return;
    }
    if(check(y,x)==1)
    {  chess[y][x]=1;
       if(y==7)
       {
        count++;
        }
        else{ queen(y+1,0);}}
    else 
    {chess[y][x]=0;
    queen(y,x+1);}
}
void main()
{
  queen(0,0);
  printf("%d",count);
}

