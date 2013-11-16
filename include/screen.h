#ifndef _AMIROS_SCREEN_
#define _AMIROS_SCREEN_

enum colors
{
black=0,
blue=1,
green=2,
cyan=3,
red=4,
magenta=5,
brown=6,
light_grey=7,
dark_grey=8,
light_blue=9,
light_green=10,
light_cyan=11,
light_red=12,
light_magenta=13,
light_brown=14,
white=15
}__attribute((packed));

typedef enum colors color;

void clrscr();
void print(char);
void set_color(color bg, color fg);
color get_color();

#endif