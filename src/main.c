#include <types.h>
#include <screen.h>
#include "init.h"

void LoadKernel()
{
//initialize AmirOS
init();
clrscr();
set_color(black, white);
print("Wellcome to AmirOS!\n");
}
