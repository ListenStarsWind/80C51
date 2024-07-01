#include<stdio.h>

typedef unsigned uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

int Key2 = 1;
int Key3 = 1;

void delay(uint span)
{
    uint i = 0;
    uint j = 0;
    for(i=0;i<span;i++)
    {
        for(j=0;j<144;j++);
    }
}

void iskey(ulong* num)
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

int main()
{
    ulong number = 65543;
    while(1)
    {
        scanf("%d",&Key2);
        scanf("%d",&Key3);
        iskey(&number);
        printf("%d\n",number);
    }
    return 0;
}

![]()