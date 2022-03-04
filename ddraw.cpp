#include "ddraw.h"
extern int w,h;
extern char* buf;
char getr(int x,int y)
{
    return buf[3*(w*y+x)];
}
char getg(int x,int y)
{
    return buf[3*(w*y+x)+1];
}
char getb(int x,int y)
{
    return buf[3*(w*y+x)+2];
}
void putpixel(int x,int y,char r,char g,char b)
{
    int pos=w*y+x;
    buf[3*pos]=r;
    buf[3*pos+1]=g;
    buf[3*pos+2]=b;
}