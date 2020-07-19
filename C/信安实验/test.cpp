#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>


typedef struct RSA
{
long long int Key;
long long  int n;
};

bool Prime(int num);     //判断素数
void phi_table(int n); //1-n中所有数的欧拉phi函数值（小于n且与n互素的整数个数）
int mgcd(int a,int b); //返回值为1则互质
long long int publiceKey(int p_num, struct RSA PubliceKey);    //加密函数
void privateKey(long long int C, struct RSA PrivateKey);    //解密函数
void test(int n,struct RSA PubliceKey,struct RSA PrivateKey);   //测试加解密

int main()
{
    srand((unsigned)time(NULL));    //设置随机

    int prime_num = 168, prime[168];
	//生成1000以内的素数的数组
    int a = 0;
    for(int i=1;i<=1000;i++)
    {
        if(Prime(i))
        {
            prime[a] = i;
            a++;
        }
    }

    int prime_a, prime_b;       //取得随机两位素数
    prime_a = prime[rand()%prime_num];
    prime_b = prime[rand()%prime_num];
    //printf("prime_a = %d , prime_b = %d , prime_num = %d\n",prime_a,prime_b,prime_num);

    int n,phi,e;
    n = prime_a * prime_b;
    phi = (prime_a-1) * (prime_b-1);

    do{                     //随机寻找到[2,phi-1]之间的正整数e与phi互素
        e = (rand()%(phi-2))+2;
    }while(mgcd(e,phi) != 1);

    long long int d,k=1;
    while(k++)     //使得(phi×k+1)能被e整除
    {
        if((phi*k+1) % e == 0)
        {
            d = (phi*k+1)/e;
            break;
        }
    }

    struct RSA PubliceKey = {e , n};  //公钥PubliceKey
    struct RSA PrivateKey = {d , n};  //私钥PrivateKey
    
    printf("公钥PubliceKey = (%d , %ld)\n",PubliceKey.Key,PubliceKey.n);
    printf("私钥PrivateKey = (%d , %ld)\n",PrivateKey.Key,PrivateKey.n);
    printf("\n");

    //三次测试
    test(n,PubliceKey,PrivateKey);printf("\n");
    test(n,PubliceKey,PrivateKey);printf("\n");
    test(n,PubliceKey,PrivateKey);printf("\n");

}

void test(int n,struct RSA PubliceKey,struct RSA PrivateKey)
{
        int p_num = rand()%n-1; //随机取得明文 p
    printf("明文P = %d\n",p_num);

    long long int C;

    C = publiceKey(p_num, PubliceKey);

    privateKey(C, PrivateKey);
}

long long int publiceKey(int p_num, struct RSA PubliceKey)    //加密函数
{
    int i;
    long long int C = p_num;
    for(i=0; i<PubliceKey.Key-1; i++)
    {
        C = (C*p_num) % PubliceKey.n;
    }
    printf("加密C = %lld\n",C);
    return C;
}


void privateKey(long long int C, struct RSA PrivateKey)    //解密函数
{
    int i;
    long long int P = C;
    for(i=0; i<PrivateKey.Key-1; i++)
    {
        P = (P*C) % PrivateKey.n;
    }
    printf("解密P = %lld\n",P);
}




int mgcd(int a,int b)
{
    int t;
    if(a<b)
    {
        t=a;a=b;b=t;
    }
    while(a%b)
    {
        t=b;
        b=a%b;
        a=t;
    }
    return b;
}

bool Prime(int num)
{
    int k = sqrt(num)+1, i;
    if(num == 1)
        return false;
    for(i=2; i<k; i++)
    {
        if(num % i == 0)
            return false;
    }
    return true;
}