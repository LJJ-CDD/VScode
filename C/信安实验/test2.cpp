#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>

int gcb(int m,int n);

int main()
{
    srand((unsigned)time(NULL));    //设置随机

    int n,phi,e;

    e = rand()%99;       //随机寻找到[2,phi-1]之间的正整数e与phi互素
    int gbc_n;
    gbc_n = gcb(e,100);  
    printf("--%d ",gbc_n);
    while( gbc_n != 1)
    {
        e = rand()%99;
        gbc_n = gcb(e,100);
        printf("--%d ",gbc_n);
    }

    printf("\ne = %d \n",e);
}

int gcb(int m,int n) //求出最大公约数，若公约数为1，则互素
{ 
   int temp,b; 
   if(m)
   { 
    temp=m; 
    m=n; 
    n=temp; 
   } 
   b=m%n; 
   if(b==0) 
     return n; 
   else 
     return gcb(n,b); 
} 