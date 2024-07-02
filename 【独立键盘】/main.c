#include<reg52.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulint;

sbit Key2 = P3^0;
sbit Key3 = P3^1;
sbit Key4 = P3^2;
sbit Key5 = P3^3;

sbit DU = P2^6;
sbit WE = P2^7;

uchar Data[] = {
                    0x3F,0x06,0x5B,0x4f,0x66,
                    0x6D,0x7D,0x07,0x7F,0x6F, 
                    0x77,0x7C,0x39,0x5E,0x79,  
                    0x71,0x76,0x38,0x40,0x00 
                };

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

void delay(uint span)
{
    uint i = 0;
    uint j = 0;
    for(i=0;i<span;i++)
    {
        for(j=0;j<144;j++);
    }
}

void SegmentDisplayInit(void)
{
    P0 = 0xff;
    WE = 1;
    WE = 0;
}

#define DELAY//打开使用延迟法判断按键状态，关闭使用计数法判断按键状态

#ifdef DELAY

void iskey(ulint* num)
{
    if(Key2 == 0)
    {
        delay(20);
        if(Key2 == 0)
        {
            (*num)--;
            while(Key2 == 0);
        }
    }
    if(Key3 == 0)
    {
        delay(20);
        if(Key3 == 0)
        {
            (*num)++;
            while(Key3 == 0);
        }
    }
}

#else

void iskey(ulint* num)
{
    uchar count = 0x00;
    uchar maxloop = 0x00;
    while(count < 0x05)
    {
        if(Key2 == 0)
        {
            count++;
        }
        else
        {
            count = 0;
            maxloop++;
        }
        delay(4);
        if(maxloop == 0x05)
        {
            break;
        }
    }
    if(count == 0x05)
    {
        (*num)++;
    }

    count = 0x00;
    while(count < 0x05)
    {
        if(Key3 == 0)
        {
            count++;
        }
        else
        {
            count = 0;
            maxloop++;
        }
        delay(4);
        if(maxloop == 0x05)
        {
            break;
        }
    }
    if(count == 0x05)
    {
        (*num)--;
    }
}

#endif

uchar digit(ulint* value)
{
    uchar ret = 0;
    ret = *value % 10 + 48;
    *value = *value / 10;
    return ret;
}

void stdout(uint value,sequence serial)
{
    uchar position = 0xfe;
    P0 = 0x00;
    DU = 1;
    DU = 0;
    P0 = _crol_(position,(uint)serial);
    WE = 1;
    WE = 0;
    P0 = Data[value];
    DU = 1;
    DU = 0;
}

void Display(ulint number)
{
    uint eighth = (uint)(digit(&number) - '0');
    uint seventh = (uint)(digit(&number) - '0');
    uint sixth = (uint)(digit(&number) - '0');
    uint fifth = (uint)(digit(&number) - '0');
    uint fourth = (uint)(digit(&number) - '0');
    uint third = (uint)(digit(&number) - '0');
    uint second = (uint)(digit(&number) - '0');
    uint first = (uint)(digit(&number) - '0');  
    uint i = 0;
    uint j = 0;
    for(i=0;i<3000;i++)
    {
        for(j=0;j<144;j++)
        {
                stdout(first,First);
                stdout(second,Second);
                stdout(third,Third);
                stdout(fourth,Fourth);
                stdout(fifth,Fifth);
                stdout(sixth,Sixth);
                stdout(seventh,Seventh);
                stdout(eighth,Eighth);
        }
    }
}

void main()
{
    ulint number = 65534;
    SegmentDisplayInit();
    while(1)
    {
        iskey(&number);
        Display(number);
    }
}