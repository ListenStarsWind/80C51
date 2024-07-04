//用于在80C51系列单片机系统中添加野指针检查函数
//类似于断言，当输入形参为野指针时，蜂鸣器以摩斯密码SOS的形式发出警报
#include<reg52.h>
#include<stddef.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit buzzer = P2^3;

//注意C51中的unsigned int范围是0~65535
//这个144是用Debug的程序运行时间算出来的
void delay(uint interval)
{
    uint i = 0;
    uint j = 0;
    for(i=0;i<interval;i++)
    {
        for(j=0;j<144;j++)
        {
            ;
        }
    }
}

//SOS:  ···   ---   ···

void SOS()
{
    uint i = 0;
    for(i=0;i<3;i++)
    {
        buzzer = 0;
        delay(10);
        buzzer = 1;
        delay(5);
    }
    delay(50);

    for(i=0;i<3;i++)
    {
        buzzer = 0;
        delay(20);
        buzzer = 1;
        delay(5);
    }
    delay(50);

    for(i=0;i<3;i++)
    {
        buzzer = 0;
        delay(10);
        buzzer = 1;
        delay(5);
    }
    delay(50);
}

void isnull(void* ptr)
{
    if(ptr == NULL)
    {
        SOS();
    }
    else
    {
        ;
    }
}