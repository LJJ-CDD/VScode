#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>


typedef struct RSA
{
long long int Key;
long long  int n;
};

bool Prime(int num);     //�ж�����
void phi_table(int n); //1-n����������ŷ��phi����ֵ��С��n����n���ص�����������
int mgcd(int a,int b); //����ֵΪ1����
long long int publiceKey(int p_num, struct RSA PubliceKey);    //���ܺ���
void privateKey(long long int C, struct RSA PrivateKey);    //���ܺ���
void test(int n,struct RSA PubliceKey,struct RSA PrivateKey);   //���Լӽ���

int main()
{
    srand((unsigned)time(NULL));    //�������

    int prime_num = 168, prime[168];
	//����1000���ڵ�����������
    int a = 0;
    for(int i=1;i<=1000;i++)
    {
        if(Prime(i))
        {
            prime[a] = i;
            a++;
        }
    }

    int prime_a, prime_b;       //ȡ�������λ����
    prime_a = prime[rand()%prime_num];
    prime_b = prime[rand()%prime_num];
    //printf("prime_a = %d , prime_b = %d , prime_num = %d\n",prime_a,prime_b,prime_num);

    int n,phi,e;
    n = prime_a * prime_b;
    phi = (prime_a-1) * (prime_b-1);

    do{                     //���Ѱ�ҵ�[2,phi-1]֮���������e��phi����
        e = (rand()%(phi-2))+2;
    }while(mgcd(e,phi) != 1);

    long long int d,k=1;
    while(k++)     //ʹ��(phi��k+1)�ܱ�e����
    {
        if((phi*k+1) % e == 0)
        {
            d = (phi*k+1)/e;
            break;
        }
    }

    struct RSA PubliceKey = {e , n};  //��ԿPubliceKey
    struct RSA PrivateKey = {d , n};  //˽ԿPrivateKey
    
    printf("��ԿPubliceKey = (%d , %ld)\n",PubliceKey.Key,PubliceKey.n);
    printf("˽ԿPrivateKey = (%d , %ld)\n",PrivateKey.Key,PrivateKey.n);
    printf("\n");

    //���β���
    test(n,PubliceKey,PrivateKey);printf("\n");
    test(n,PubliceKey,PrivateKey);printf("\n");
    test(n,PubliceKey,PrivateKey);printf("\n");

}

void test(int n,struct RSA PubliceKey,struct RSA PrivateKey)
{
        int p_num = rand()%n-1; //���ȡ������ p
    printf("����P = %d\n",p_num);

    long long int C;

    C = publiceKey(p_num, PubliceKey);

    privateKey(C, PrivateKey);
}

long long int publiceKey(int p_num, struct RSA PubliceKey)    //���ܺ���
{
    int i;
    long long int C = p_num;
    for(i=0; i<PubliceKey.Key-1; i++)
    {
        C = (C*p_num) % PubliceKey.n;
    }
    printf("����C = %lld\n",C);
    return C;
}


void privateKey(long long int C, struct RSA PrivateKey)    //���ܺ���
{
    int i;
    long long int P = C;
    for(i=0; i<PrivateKey.Key-1; i++)
    {
        P = (P*C) % PrivateKey.n;
    }
    printf("����P = %lld\n",P);
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