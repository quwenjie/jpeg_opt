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
void PixelBuffer::SetPixel(int x,int y,unsigned char r,unsigned char g,unsigned char b)
{
    int pos=w*y+x;
    buf[3*pos]=r;
    buf[3*pos+1]=g;
    buf[3*pos+2]=b;
}
void PixelBuffer::Save(char *file_name){
    write_JPEG_file(file_name,(char*)buf, w,h);
}

Eigen::MatrixXi PixelBuffer::Threshold(int l,int r){
    Eigen::MatrixXi m(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            auto [r,g,b] = GetPixel(i,j);
            int gray = (38 * r + 75 * g + 15 * b) >> 7;
            if(gray >= l && gray <= r){
                m(i,j) = 1;
            }else{
                m(i,j) = 0;
            }
        }
    }
    return m; //RVO
}

Eigen::MatrixXi PixelBuffer::Gray(){
    Eigen::MatrixXi m(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            auto [r,g,b] = GetPixel(i,j);
            int gray = (38 * r + 75 * g + 15 * b) >> 7;
            m(i,j) = gray; 
        }
    }
    return m; //RVO
}