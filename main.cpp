#include "jpeg.h"
#include <iostream>

using namespace std;


int w,h;
char* buf;
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


int main()
{
    read_JPEG_file("0.jpg",  &buf, &w, &h);
    for(int i=0;i<100;i++)
    for(int j=0;j<100;j++)
        putpixel(i,j,0,255,0);
    cout<<(int)getr(0,0)<<endl;
    write_JPEG_file("targ.jpeg",buf, w,h);
    
    return 0;
}