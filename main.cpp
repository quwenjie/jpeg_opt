#include "jpeg.h"
#include "ddraw.h"
#include <iostream>
using namespace std;
char* buf;
int w,h;
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