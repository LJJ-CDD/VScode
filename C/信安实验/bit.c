#include <stdio.h>
void changeBinary(int);
int main()
{
	int num;
	scanf("%d",&num);
	changeBinary(num);
}
void changeBinary(int num)
{
	// int* p=&num;
	// typedef unsigned char uc;
	// uc* ptr=(uc*)p;
	// int len=sizeof(int);
	// for(int i=0;i<len;++i){
		int byte=100;
		for(int j=0;j<56;++j){
			putchar(0x80000000000000 & byte ? '1':'0');
			byte<<=1;
		}
		putchar(' ');
		// ++ptr;
	// }
	puts("");
}