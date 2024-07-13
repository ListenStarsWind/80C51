#include <reg52.h>

sbit DU = P2 ^ 6;
sbit WE = P2 ^ 7;

// Rows and columns
sbit writekey1 = P3 ^ 0;
sbit writekey2 = P3 ^ 1;
sbit writekey3 = P3 ^ 2;
sbit writekey4 = P3 ^ 3;
sbit readkey1 = P3 ^ 4;
sbit readkey2 = P3 ^ 5;
sbit readkey3 = P3 ^ 6;
sbit readkey4 = P3 ^ 7;

typedef unsigned char uchar;
typedef unsigned int uint;

uchar displayCodes[] = {
    0x3F, 0x06, 0x5B, 0x4f, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F,
    0x77, 0x7C, 0x39, 0x5E, 0x79,
    0x71, 0x76, 0x38, 0x40, 0x00};

uchar newkey[4][4] = {
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1};

void main()
{
    uchar i = 0;
    uchar j = 0;
    static uchar prevkey[4][4] = {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1};

    P0 = displayCodes[19];
    DU = 1;
    DU = 0;

    P0 = 0x7f;
    WE = 1;
    WE = 0;

    writekey1 = 0;
    writekey2 = 1;
    writekey3 = 1;
    writekey4 = 1;

    //启用定时中断
    EA = 1;        //使能总中断
    ET0 = 1;       //使能定时中断
    TMOD = 0x01;   //设置定时T0为模式一
    //装载初始化数据，定时1ms
    TH0 = 0xfc;
    TL0 = 0x67;
    TR0 = 1;       //启动T0

    while(1)
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(newkey[i][j] != prevkey[i][j])
                {
                    if(newkey[i][j] == 0)
                    {
                        P0 = displayCodes[i*4+j];
                        DU = 1;
                        DU = 1;
                    }
                    prevkey[i][j] = newkey[i][j];
                }
            }
        }
    }
}

void iskey() interrupt 1
{
    static uchar keyHistory[4][4] = {
                                        0xff, 0xff, 0xff, 0xff, 
                                        0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff
                                    };
    static uchar rows = 0;
    uchar columns = 0;

    TH0 = 0xfc;
    TL0 = 0x67;

    keyHistory[rows][0] = (keyHistory[rows][0]<<1) | readkey1;
    keyHistory[rows][1] = (keyHistory[rows][1]<<1) | readkey2; 
    keyHistory[rows][2] = (keyHistory[rows][2]<<1) | readkey3; 
    keyHistory[rows][3] = (keyHistory[rows][3]<<1) | readkey4;

    for(columns = 0; columns < 4; columns++)
    {
        if((keyHistory[rows][columns] & 0x0f) == 0x00)
        {
            newkey[rows][columns] = 0;
        }
        else if ((keyHistory[rows][columns] & 0x0f) == 0x0f)
        {
            newkey[rows][columns] = 1;
        }
        else
        {

        }
    }
    rows++;
    rows = rows & 0x03;
    switch(rows)
    {
        case 0: writekey4 = 1; writekey1 = 0; break;
        case 1: writekey1 = 1; writekey2 = 0; break;
        case 2: writekey2 = 1; writekey3 = 0; break;
        case 3: writekey3 = 1; writekey4 = 0; break;
    }
}