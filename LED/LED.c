#include<reg52.h>

sbit LED = P1^0;

void main()
{
	while(1)
	{
		LED = 0;
	}
}	