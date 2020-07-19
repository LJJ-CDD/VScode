#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

void SKeyGenerator(unsigned char *Key) //交换数组
{
    int i, j;
    char temp;

    srand((unsigned)time(NULL));
    for (i = 0; i < 256; i++)
        Key[i] = i;

    for (i = 0; i < 256; i++)
    {
        j = i + rand() % (256 - i); //取得 i - 256-i 之间的随机数
        //swap(Key[i],Key[j]);  //交换数据
        temp = Key[i];
        Key[i] = Key[j];
        Key[j] = temp;
    }
}

int fact(int n)     //十进制转换为二进制
{ 
	if(n<2)                       //将 2 换成其它数如 8 就可输出 8 进制的结果
		return n; 
	else
	{ 
		return fact(n/2)*10+n%2;                     //将二进制结果整个输出 
	} 
}

int convertBinaryToDecimal(int n) //将二级制转换为十进制
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

void SEncrytion(unsigned char PlainText, unsigned char CipherText, unsigned char* Key)   //替代加密函数 明文 密文 密码表
{
    int Plain = fact(PlainText);
    int start,last;
    last = Plain % 10000;     //求后四位
    start = (Plain-last) / 10000; //求前四位
    
    start = convertBinaryToDecimal(start);
    last = convertBinaryToDecimal(last);
    CipherText = Key[start*16+last];
    printf("明文二进制为 %d\t前四位行为 %d\t后四位列为 %d\t 密文为%d\t\n",Plain,start,last,CipherText);
}

void SDecrytion(unsigned char PlainText, unsigned char CipherText, unsigned char* Key)   //替代解密函数
{
	
	int i,j;
	for(i=0;i<256;i++)
    {
    	j = Key[i];
        //printf("%d ",j);
		if(j == CipherText)
			break;
    }
    
    int start,last;
    start = i/16;
    last = i%16;
    
	start = fact(start);
	last = fact(last); 

    int num;
    num = start*10000+last;
    convertBinaryToDecimal(num);
    
    printf("解密得明文为 %d\n",convertBinaryToDecimal(num));
}

void Printf_tPasswordTable(unsigned char Key[][16])
{
    int i,j;
    printf("\n\tPasswordTable\n");      //打印密码表
    for(i=0;i<16;i++)
    {
    	for(j=0;j<16;j++)
    	{
    		printf("%d ",Key[i][j]);	
    	}
    	printf("\n");
    }	
    printf("\n");
}


int main()
{
    unsigned char SKey[17][16];
    unsigned char *pSKey = &SKey[0][0];

    SKeyGenerator(pSKey);   //初始化密码表
	unsigned char CipherText;
    unsigned int PlainText;

    Printf_tPasswordTable(SKey);   //打印密码表

    //加密方法 十进制数字->8bit->分割前四为行后四为列->两个十进制对应密码表行列密文
	printf("请输入要加密的数字: ");
	scanf("%d",&PlainText); 
	SEncrytion(PlainText,CipherText,pSKey);
    printf("\n");getchar();
    
    //Printf_tPasswordTable(pSKey);   //打印密码表
    //解密方法 十进制数字在密码表中寻找对应->取得行列->分别转为4bit前后结合为8bit->转为10进制原文
	printf("请输入要解密的数字: ");
	scanf("%d",&CipherText); 
	SDecrytion(PlainText,CipherText,pSKey);

    return 0;
}
