#include<stdio.h>

typedef unsigned int uint;
typedef unsigned char uchar;


int main()
{
    uchar eight = '1';
    uchar seven = '3';
    uchar six = '5';
    uchar five = '5';
    uchar four = '6';
    uchar three = '0';
    uchar two = '0';
    uchar one = '0';
    uint eighth = (uint)(eight-'0');
    uint seventh = (uint)(seven-'0');
    uint sixth = (uint)(six-'0');
    uint fifth = (uint)(five-'0');
    uint fourth = (uint)(four-'0');
    uint third = (uint)(three-'0');
    uint second = (uint)(two-'0');
    uint first = (uint)(one-'0'); 
    printf("%u\n",eighth);
    printf("%u\n",seventh);
    printf("%u\n",sixth);
    printf("%u\n",fifth);
    printf("%u\n",fourth);
    printf("%u\n",third);
    printf("%u\n",second);
    printf("%u\n",first);
    return 0;
}