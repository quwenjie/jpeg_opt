#include "ddraw.h"
#include <iostream>
#include <cstdlib>
using namespace std;

PixelBuffer::Pixel PixelBuffer::GetPixel(int x,int y){
    return make_tuple(buf[3*(w*y+x)],buf[3*(w*y+x)+1],buf[3*(w*y+x)+2]);
}
void PixelBuffer::clear()
{
    memset(buf,0,w * h * 3);
}
PixelBuffer PixelBuffer::downscale_2()
{
    PixelBuffer ret(w>>1,h>>1);
    ret.clear();
    auto retw=ret.GetWidth();
    auto reth=ret.GetHeight();

    for(int i = 0;i <retw ;i++)
    {
        for(int j = 0;j < reth;j++)
        {
            int rsum=0,gsum=0,bsum=0;
            auto [r1,g1,b1] = GetPixel(i*2,j*2);
            auto [r2,g2,b2] = GetPixel(i*2+1,j*2);
            auto [r3,g3,b3] = GetPixel(i*2,j*2+1);
            auto [r4,g4,b4] = GetPixel(i*2+1,j*2+1);
            rsum=(int(r1)+r2+r3+r4)>>2;
            gsum=(int(g1)+g2+g3+g4)>>2;
            bsum=(int(b1)+b2+b3+b4)>>2;
            ret.SetPixel(i,j,(unsigned char)rsum,(unsigned char)gsum,(unsigned char)bsum);
        }
    }
    return ret;
}
PixelBuffer PixelBuffer::downscale(int K)
{
    PixelBuffer ret(w/K,h/K);
    ret.clear();
    auto retw=ret.GetWidth();
    auto reth=ret.GetHeight();
    auto K2=K*K;
    for(int i = 0;i <retw ;i++)
    {
        for(int j = 0;j < reth;j++)
        {
            int rsum=0,gsum=0,bsum=0;
            for(int ii=i*K;ii<i*K+K;ii++)
                for(int jj=j*K;jj<j*K+K;jj++)
                {
                    auto [r,g,b] = GetPixel(ii,jj);
                    rsum+=r;
                    gsum+=g;
                    bsum+=b;
                }
            rsum=rsum/K2;
            gsum=gsum/K2;
            bsum=bsum/K2;
            ret.SetPixel(i,j,(unsigned char)rsum,(unsigned char)gsum,(unsigned char)bsum);
        }
    }
    return ret;
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

Eigen::MatrixXi PixelBuffer::Threshold(int lx,int rx)
{
    Eigen::MatrixXi m(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            auto [r,g,b] = GetPixel(i,j);
            int gray = (9738 * r + 19235 * g + 3735 * b) >> 15;
            if(gray>255)
                gray=255;
            if(gray >= lx && gray <= rx){
                m(i,j) = 1;
            }else{
                m(i,j) = 0;
            }
        }
    }
    return m; //RVO
}

Eigen::MatrixXi PixelBuffer::Gray()
{
    Eigen::MatrixXi m(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            auto [r,g,b] = GetPixel(i,j);
            int gray = (9738 * r + 19235 * g + 3735 * b) >> 15;
            if(gray>255)
                gray=255;
            m(i,j) = gray; 
        }
    }
    return m; //RVO
}