#include<reg52.h>


void delay(int num)
{
	int x; int y;
	for(x=0;x<num;x++)
	{
		for(y=0;y<144;y++);
	}
}

void main()
{
	while(1)
	{
		P1 = 0xfe;
		delay(100);
		P1 = 0xff;
	}
}