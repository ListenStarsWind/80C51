#include<reg52.h>

//类型重命名
typedef unsigned int unint;
//注意八位机器中的int与32位64位机器中的int范围不同

//注意形参范围：此处是0-65535；

//毫秒级延迟函数
void delay(unint x)
{
    unint i = 0;
    unint j = 0;
    for(i=0; i<x; i++)
    {
        for(j=0;j<144; j++);
    }
}

void main()
{
    //可千万不要用data呀，因为data在C51中是一个存储类型说明符，用于指定变量存储在片内数据存储区。
    unint Data = 0xff;
    while(1)
    {
        P1 = Data;
        delay(1000);
        //笑死了，我第一次写的时候，写成了Data~=Data;
        Data = ~Data;
    }    
}