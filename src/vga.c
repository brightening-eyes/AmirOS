#include <types.h>
#include <screen.h>
#include <memory.h>
#include "io.h"

pointer vidmem=0xB8000;
uint curser_x, curser_y;
color clr;

void scr()
{
uint blank, tmp;
uint attribute=0<<8;
blank=0x20|(attribute);
if(curser_y>=25)
{
tmp=curser_y-25+1;
memcpy(vidmem+tmp*80, (25-tmp)*80*2, 0x400);
memset(vidmem+(25-tmp)*80, blank, 80);
curser_y=25-1;
}
}

void movescr()
{
uint tmp;
tmp=curser_y*80+curser_x;
outb(0x3D4, 14);
outb(0x3D5, tmp>>8);
outb(0x3D4, 15);
outb(0x3D5, tmp);
}

void print(pointer p, ...)
{
pointer v;
pointer vidmem=0xB8000;
pointer a;
int attribute=0<<8;
if(p==0x08||v==0x08)
{
if(curser_x!=0)
{
curser_x--;
}
}
else if(p=='\r'||v=='\r')
{
curser_y=0;
}
else if(p=='\0'||v=='\0')
{
curser_x++;
}
else if(p=='\n'||v=='\n')
{
curser_y=0;
curser_x++;
}
else if(p>=' '||v>=' ')
{
a=vidmem+(curser_y*80+curser_x);
a=(int)p|(int)v|attribute|get_color();
curser_x++;
}
if(curser_x>=80)
{
curser_x=0;
curser_y+=1;
}
scr();
movescr();
}

void clrscr()
{
uint blank;
int i;
int attribute=0<<8;
blank=0x20|(attribute);
for(i=0;i<=25;i++)
{
memset(vidmem+i*80, blank, 80);
curser_x=0;
curser_y=0;
movescr();
}
}

void set_color(color bg, color fg)
{
clr=bg|fg;
}

color get_color()
{
return clr<<4;
}

