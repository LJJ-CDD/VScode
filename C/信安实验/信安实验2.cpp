#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

void SKeyGenerator(unsigned char *Key) //��������
{
    int i, j;
    char temp;

    srand((unsigned)time(NULL));
    for (i = 0; i < 256; i++)
        Key[i] = i;

    for (i = 0; i < 256; i++)
    {
        j = i + rand() % (256 - i); //ȡ�� i - 256-i ֮��������
        //swap(Key[i],Key[j]);  //��������
        temp = Key[i];
        Key[i] = Key[j];
        Key[j] = temp;
    }
}

int fact(int n)     //ʮ����ת��Ϊ������
{ 
	if(n<2)                       //�� 2 ������������ 8 �Ϳ���� 8 ���ƵĽ��
		return n; 
	else
	{ 
		return fact(n/2)*10+n%2;                     //�������ƽ��������� 
	} 
}

int convertBinaryToDecimal(int n) //��������ת��Ϊʮ����
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

void SEncrytion(unsigned char PlainText, unsigned char CipherText, unsigned char* Key)   //������ܺ��� ���� ���� �����
{
    int Plain = fact(PlainText);
    int start,last;
    last = Plain % 10000;     //�����λ
    start = (Plain-last) / 10000; //��ǰ��λ
    
    start = convertBinaryToDecimal(start);
    last = convertBinaryToDecimal(last);
    CipherText = Key[start*16+last];
    printf("���Ķ�����Ϊ %d\tǰ��λ��Ϊ %d\t����λ��Ϊ %d\t ����Ϊ%d\t\n",Plain,start,last,CipherText);
}

void SDecrytion(unsigned char PlainText, unsigned char CipherText, unsigned char* Key)   //������ܺ���
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
    
    printf("���ܵ�����Ϊ %d\n",convertBinaryToDecimal(num));
}

void Printf_tPasswordTable(unsigned char Key[][16])
{
    int i,j;
    printf("\n\tPasswordTable\n");      //��ӡ�����
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

    SKeyGenerator(pSKey);   //��ʼ�������
	unsigned char CipherText;
    unsigned int PlainText;

    Printf_tPasswordTable(SKey);   //��ӡ�����

    //���ܷ��� ʮ��������->8bit->�ָ�ǰ��Ϊ�к���Ϊ��->����ʮ���ƶ�Ӧ�������������
	printf("������Ҫ���ܵ�����: ");
	scanf("%d",&PlainText); 
	SEncrytion(PlainText,CipherText,pSKey);
    printf("\n");getchar();
    
    //Printf_tPasswordTable(pSKey);   //��ӡ�����
    //���ܷ��� ʮ�����������������Ѱ�Ҷ�Ӧ->ȡ������->�ֱ�תΪ4bitǰ����Ϊ8bit->תΪ10����ԭ��
	printf("������Ҫ���ܵ�����: ");
	scanf("%d",&CipherText); 
	SDecrytion(PlainText,CipherText,pSKey);

    return 0;
}
