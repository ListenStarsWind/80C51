#include<reg52.h>
#include<intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

uchar Data[] = {
                    0x3F,0x06,0x5B,0x4f,0x66,
                    0x6D,0x7D,0x07,0x7F,0x6F, 
                    0x77,0x7C,0x39,0x5E,0x79,  
                    0x71,0x76,0x38,0x40,0x00 
                };



sbit DU = P2^6;
sbit WE = P2^7;

typedef enum location
{
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Seventh,
    Eighth   
}location;

void delay(uint span)
{
    uint i = 0;
    uint j = 0;
    for(i=0;j<span;i++)
    {
        for(j=0;j<144;j++);
    }
}

void DigitalTubeInitialization()
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

void display(uint value,location place)
{
    uchar position = 0xfe;
    WE = 1;
    P0 = _crol_(position,(uint)place);
    WE = 0;
    P0 = Data[value];
    DU = 1;
    DU = 0;
}

void main()
{
    DigitalTubeInitialization();
    display(1, Eighth);
    //第一次写没有带while(1);结果发现一些本不该发光的的LED有辉光，后来稍微想了一下，意识到有辉光是因为嵌入式程序是反复运行的，
    //如果不加while(1);数码管立刻又会被初始化，而程序运行又很快，残留的视觉混在一起就有了辉光
    while(1);  
}