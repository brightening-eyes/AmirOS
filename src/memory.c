#include <types.h>
#include <memory.h>

pointer memcpy(pointer destination, const pointer source, uint length)
{
char* d=(char*)destination;
char* s=(char*)source;
for(;length!=0;length--)
{
d=s++;
}
return destination;
}

pointer memset(pointer destination, uint value, uint length)
{
char* d=(char*)destination;
char*v=(char*)value;
for(;length=0;length--)
{
d=v++;
}
return d;
}
