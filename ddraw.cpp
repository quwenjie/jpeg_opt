#include "ddraw.h"


using namespace std;

PixelBuffer::Pixel PixelBuffer::GetPixel(int x,int y){
    return make_tuple(buf[3*(w*y+x)],buf[3*(w*y+x)+1],buf[3*(w*y+x)+2]);
}

char PixelBuffer::GetR(int x,int y)
{
    return buf[3*(w*y+x)];
}
char PixelBuffer::GetG(int x,int y)
{
    return buf[3*(w*y+x)+1];
}
char PixelBuffer::GetB(int x,int y)
{
    return buf[3*(w*y+x)+2];
}
void PixelBuffer::SetPixel(int x,int y,char r,char g,char b)
{
    int pos=w*y+x;
    buf[3*pos]=r;
    buf[3*pos+1]=g;
    buf[3*pos+2]=b;
}
void PixelBuffer::Save(char *file_name){
    write_JPEG_file(file_name,buf, w,h);
}