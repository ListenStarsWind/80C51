#include"choose.h"
#ifndef CHOOSE

//#define CODE1
#define CODE2

#ifdef CODE1

#include<reg52.h>

//类型重命名
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

//按键比特位命名
sbit Key2 = P3^0;

//数码管段选位选比特位命名
sbit DU = P2^6;
sbit WE = P2^7;

//共阴极数码管字符码
uchar Data[] = {
                    0x3F,0x06,0x5B,0x4f,0x66,
                    0x6D,0x7D,0x07,0x7F,0x6F, 
                    0x77,0x7C,0x39,0x5E,0x79,  
                    0x71,0x76,0x38,0x40,0x00 
                };

void main()
{
    bit prevkey = 1;                //按键最开始是没有被按下的，所以初始化为1
    uchar number = 0;               //最开始显示0，所以初始化为0

    //数码管消隐：关闭段。
    P0 = 0x00;
    DU = 1;
    DU = 0;

    //显示初始数字
    //位操作
    P0 = 0x7f;
    WE = 1;
    WE = 0;
    //段操作
    P0 = Data[number];
    DU = 1;
    DU = 0;

    while(1)
    {
        if(Key2 != prevkey)
        {
            number++;
            if(number == 10)
            {
                number = 0;
            }

            P0 = Data[number];
            DU = 1;
            DU = 0;

            prevkey = Key2;
        }
    }
}                

#endif

#ifdef CODE2

#include<reg52.h>

//类型重命名
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

//按键比特位命名
sbit Key2 = P3^0;

//数码管段选位选比特位命名
sbit DU = P2^6;
sbit WE = P2^7;

bit newkey = 1;                 //按键最开始是没有被按下的，所以初始化为1

//共阴极数码管字符码
uchar Data[] = {
                    0x3F,0x06,0x5B,0x4f,0x66,
                    0x6D,0x7D,0x07,0x7F,0x6F, 
                    0x77,0x7C,0x39,0x5E,0x79,  
                    0x71,0x76,0x38,0x40,0x00 
                };

void main()
{
    bit prevkey = 1;                //按键最开始是没有被按下的，所以初始化为1
    uchar number = 0;               //最开始显示0，所以初始化为0

    //数码管消隐：关闭段。
    P0 = 0x00;
    DU = 1;
    DU = 0;

    //显示初始数字
    //位操作
    P0 = 0x7f;
    WE = 1;
    WE = 0;
    //段操作
    P0 = Data[number];
    DU = 1;
    DU = 0;

    //启用定时中断
    EA = 1;        //使能总中断
    ET0 = 1;       //使能定时中断
    TMOD = 0x01;   //设置定时T0为模式一
    //装载初始化数据，定时2ms
    TH0 = 0xf8;
    TL0 = 0xcd;
    TR0 = 1;       //启动T0

    while(1)
    {
        if(newkey != prevkey)                               //按键状态发生变化
        {
            if(newkey == 0)                                 //按键被按下
            {
                number++;
                if(number == 10)
                {
                    number = 0;
                }

                P0 = Data[number];
                DU = 1;
                DU = 0;

                prevkey = newkey;
            }
            else                                            //按键弹起
            {
                ;
            }
        }
    }
}

//以定时中断的形式检测按键
void iskey() interrupt 1
{
    static uchar keyhistory = 0xff;          //构建缓冲区，存储按键在16ms内的8次状态。

    //装载初始化数据，定时2ms
    TH0 = 0xf8;
    TL0 = 0xcd;

    Key2 = 1;                                //对相关IO口初始化为1，确保能正常读取按键

    keyhistory = (keyhistory<<1) | Key2;         //记录按键每2ms的状态

    if (keyhistory == 0x00)                      //连续 8 次扫描值都为 0，即 16ms 内都只检测到按下状态时，可认为按键已按下
    { 
        newkey = 0;
    }
    else if (keyhistory == 0xFF)                 //连续 8 次扫描值都为 1，即 16ms 内都只检测到弹起状态时，可认为按键已弹起
    { 
        newkey = 1;
    }
    else                                     //其它情况则说明按键状态尚未稳定，则不对 KeySta 变量值进行更新
    {
        
    } 
}

#endif

#endif
