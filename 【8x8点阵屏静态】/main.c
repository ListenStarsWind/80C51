#include <reg52.h>
#include <intrins.h>

typedef unsigned char uchar;

typedef struct LED_Dot_Matrix_Display
{
    uchar Columns[8];
    uchar Rows;
} matrix, *pMatrix;

sbit HC595_SERIAL_DATA_INPUT = P3 ^ 4;
sbit HC595_SHIFT_REGISTER_LATCH = P3 ^ 5;
sbit HC595_INPUT_LATCH = P3 ^ 6;

#define HC595_SHIFT_REGISTER_LATCH_HIGH() \
    {                                     \
        HC595_SHIFT_REGISTER_LATCH = 1;   \
        HC595_SHIFT_REGISTER_LATCH = 0;   \
    }
#define HC595_INPUT_LATCH_HIGH() \
    {                            \
        HC595_INPUT_LATCH = 1;   \
        HC595_INPUT_LATCH = 0;   \
    }

#define IN_Global_Variables(vale,n,data) {vale.Columns[n] = data;}

#define NULL ((void*)0)

//0xE7,0xF7,0xF7,0xF7,0x80,0xF7,0xFB,0xC3   子
//0xE0,0xEE,0x01,0x6D,0x01,0x6D,0x01,0xEF   电
matrix test = {{0xE7,0xF7,0xF7,0xF7,0x80,0xF7,0xFB,0xC3},{0x80}};


void display8x8LEDMatrixDisplay(pMatrix p)
{
    static uchar i = 0;
    uchar j = 0;
    uchar k = 0;
    uchar buffer = 0;
    static pMatrix history = NULL;

    if (p == NULL)
    {
        again:
        buffer = history->Columns[i];
        i++;
        if (i == 8)
        {
            i = 0;
        }
        do
        {
            for (j = 0; j < 8; j++)
            {
                if (buffer & 0x01)
                {
                    HC595_SERIAL_DATA_INPUT = 1;
                }
                else
                {
                    HC595_SERIAL_DATA_INPUT = 0;
                }
                HC595_SHIFT_REGISTER_LATCH_HIGH();
                buffer >>= 1;
            }
            buffer = history->Rows;
        } while (!k++);
        history->Rows = _cror_(history->Rows, 1);
        HC595_INPUT_LATCH_HIGH();
    }
    else
    {
        if (i == 0)
        {
            history = p;
            buffer = p->Columns[i];
            i++;
            if (i == 8)
            {
                i = 0;
            }
            do
            {
                for (j = 0; j < 8; j++)
                {
                    if (buffer & 0x01)
                    {
                        HC595_SERIAL_DATA_INPUT = 1;
                    }
                    else
                    {
                        HC595_SERIAL_DATA_INPUT = 0;
                    }
                    HC595_SHIFT_REGISTER_LATCH_HIGH();
                    buffer >>= 1;
                }
                buffer = p->Rows;
            } while (!k++);
            p->Rows = _cror_(p->Rows, 1);
            HC595_INPUT_LATCH_HIGH();
        }
        else
        {
            goto again;
        }
    }
}

void main()
{
    HC595_SHIFT_REGISTER_LATCH = 0;
    HC595_INPUT_LATCH = 0;

    EA = 1;
    ET0 = 1;
    TMOD = 0x01;
    TH0 = 0xf8;
    TL0 = 0xcd;
    TR0= 1;

    while(1);
}

void display() interrupt 1
{
    TH0 = 0xf8;
    TL0 = 0xcd;
    display8x8LEDMatrixDisplay(&test);
}