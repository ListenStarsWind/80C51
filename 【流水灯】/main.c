#include<reg52.h>
#include<intrins.h>

typedef unsigned int uint;

void delay(uint x)
{
    uint i = 0;
    uint j = 0;
    for(;i<x;i++)
    {
        for(;j<144;j++);
    }
}

void main()
{
    uint Data = 0xfe;
    while(1)
    {
        P1 = Data;
        Data = _crol_(Data,1);
        delay(2000);
    }
}