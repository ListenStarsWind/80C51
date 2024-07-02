#include<reg52.h>
#include<intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long int ulint;

uchar Data[] = {
                    0x3F,0x06,0x5B,0x4f,0x66,
                    0x6D,0x7D,0x07,0x7F,0x6F, 
                    0x77,0x7C,0x39,0x5E,0x79,  
                    0x71,0x76,0x38,0x40,0x00 
                };

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
    //要知道为什么置为0对应数码管就会选中
    //这里用的是八位共阴极数码管，也就是说每个数码管中的八个LED阴极是接在一起的，
    //当位选锁存器开启后，八个P0端口相当于依据高低位分别与八个数码管的阴极相连
    //而LED的点亮条件是阳极接高电位，阴极接低电位；
    //此时，若把对应IO口置为高电位，则阴极就是高电位，这样，无论阳极电位如何，LED都不会被点亮
    P0 = 0xff;
    WE = 1;
    WE = 0;
}


#define DEBUG

#ifdef DEBUG

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

#else
void Display( number)
{
    
}

#endif

void main()
{
    SegmentDisplayInit();//数码管初始化函数
    Display(65536);//八位数码管显示函数
    while(1);
}