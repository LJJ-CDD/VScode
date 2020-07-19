#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

void C_myPermutation(unsigned int In[],int n,unsigned char *P)      //从前往后置换
{
    int i,j,temp;
    for(i=0; i<n; i++)
    {
        j = P[i];
        temp = In[j];
        In[j] = In[i];
        In[i] = temp;
    }
}

void CC_myPermutation(unsigned int In[],int n,unsigned char *P)     //从后往前置换
{
    int i,j,temp;
    for(i=n-1; i>=0; i--)
    {
        j = P[i];
        temp = In[j];
        In[j] = In[i];
        In[i] = temp;
    }
}

void PKeyGenerator(unsigned char* Key)  //制作位移密码表
{
    int i, j;
    char temp;

    srand((unsigned)time(NULL));
    for (i = 0; i < 32; i++)
        Key[i] = i;

    for (i = 0; i < 32; i++)
    {
        j = i + rand() % (32 - i); //取得 i - 32-i 之间的随机数
        temp = Key[i];
        Key[i] = Key[j];
        Key[j] = temp;
    }
}

void PEncrytion(unsigned int* PlainText, unsigned int* CipherText, unsigned char* Key)
{
    int i;
    printf("加密\n");
    C_myPermutation(PlainText,32,Key); //初始置换
    for(i=0; i<32; i++)
    {
        printf("%d ",PlainText[i]);
    }
    printf("\n");
}

void SDecrytion(unsigned int* PlainText, unsigned int* CipherText, unsigned char* Key)
{
    int i;
    printf("解密\n");
    CC_myPermutation(PlainText,32,Key);   //逆初始置
    for(i=0; i<32; i++)
    {
        printf("%d ",PlainText[i]);
    }
    printf("\n");
}


int main()
{
    unsigned int m[32]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1};
    unsigned int k[32];
    unsigned int *M = &m[0], *K = &k[0];

    int i;
    unsigned char SKey[4][8];
    unsigned char *pSKey = &SKey[0][0];
    PKeyGenerator(pSKey);

    printf("原文\n");
    for(i=0; i<32; i++)
    {
        printf("%d ",M[i]);
    }
    printf("\n");

    PEncrytion(M, K, pSKey);
    SDecrytion(M, K, pSKey);

}