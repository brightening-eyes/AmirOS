#include <types.h>
#include <screen.h>
#include "init.h"

void LoadKernel()
{
init();
clrscr();
set_color(black, white);
print("Wellcome to AmirOS!\n");
}
