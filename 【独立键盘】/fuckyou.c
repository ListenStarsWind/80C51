#include<reg52.h>
#include<intrins.h>

#define CASE(select,code) case select: code; break

//类型重命名
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

//按键比特位命名
sbit Key2 = P3^0;
sbit Key3 = P3^1;
sbit Key4 = P3^2;
sbit Key5 = P3^3;

//LED比特位命名
sbit LED  = P1^0;

//数码管段选位选比特位命名
sbit DU = P2^6;
sbit WE = P2^7;

typedef enum sequence
{
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Seventh,
    Eighth   
}sequence;

//共阴极数码管字符码
uchar Data[] = {
                    0x3F,0x06,0x5B,0x4f,0x66,
                    0x6D,0x7D,0x07,0x7F,0x6F, 
                    0x77,0x7C,0x39,0x5E,0x79,  
                    0x71,0x76,0x38,0x40,0x00 
                };

//显示
ulong number = 65534;


void delay(uint span)
{
    uint i = 0;
    uint j = 0;
    for(i=0;i<span;i++)
    {
        for(j=0;j<144;j++);
    }
}

void main()
{
    EA =1;
    ET0 = 1;
    TH0 =0XFB;
    TL0= 0X0F;
    TR0 = 1;

    P0 = 0xff;
    WE = 1;
    WE = 0;

    while(1)
    {
        if(Key2 == 0)
        {
            delay(10);
            if(Key2 == 0)
            {
                LED = 0 ;
                if(number < 99999999)
                {
                    number++;
                }
                else
                {
                    ;
                }
                LED = 1;
                while(!Key2);
            }
        }
        if(Key3 == 0)
        {
            delay(10);
            if(Key3 == 0)
            {
                LED = 0;
                if(number > 0)
                {
                    number--;
                }
                else
                {
                    ;
                }
                LED =1;
                while(!Key3);
            }
        }
    }
}

void display()
{
    static sequence i =  First;
    static uchar position = 0xfe;
	DU = 1;
    P0 = 0x00;
	DU = 0;
    switch(i)
    {
        CASE(First,DU =1; P0 = Data[number/10000000];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Second;);
        CASE(Second,DU =1; P0 = Data[number%10000000/1000000];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Third;);
        CASE(Third,DU =1; P0 = Data[number%1000000/100000];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Fourth;);
        CASE(Fourth,DU =1; P0 = Data[number%100000/10000];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Fifth;);
        CASE(Fifth,DU =1; P0 = Data[number%10000/1000];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Sixth;);
        CASE(Sixth,DU =1; P0 = Data[number%1000/100];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Seventh;);
        CASE(Seventh,DU =1; P0 = Data[number%100/10];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = Eighth;);
        CASE(Eighth,DU =1; P0 = Data[number%10];DU = 0;P0 = _crol_(position,i);WE = 1; WE = 0;i = First;);
    }
}


void timer0() interrupt 1
{
    TH0 =0XFB;
    TL0= 0X0F;
    display();
}