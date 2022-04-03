#include "ddraw.h"
#include <iostream>
#include <cstdlib>
using namespace std;
//extern const char font_en[][72];
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
void PixelBuffer::SetPixel(int x,int y,Pixel c)
{
    int pos=w*y+x;
    auto [r,g,b] = c;
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
void PixelBuffer::DrawCross(int x,int y,int k,unsigned char r,unsigned char g,unsigned char b)
{
    for(int i = x - k;i < x + k;i++){
        SetPixel(i,y,r,g,b);
    }
    for(int i = y - k;i < y + k;i++){
        SetPixel(x,i,r,g,b);
    }
}
void PixelBuffer::DrawASCII(int x,int y,const char *s,unsigned char r,unsigned char g,unsigned char b)
{
	FILE* hzk_p = NULL;       
    int fontsize=16;                              
	unsigned char quma, weima;               
	unsigned long offset;                         
	unsigned char mask[] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 }; 
	int i, j, pos, y0 = y;

	char mat[288];
	char eng[2] = "E";
	char fn[30];
	sprintf(fn, "ASC%d", fontsize);
	hzk_p=fopen(fn, "rb");           
	if (hzk_p == NULL)
		exit(-1);
	long fsize=fontsize * fontsize / 8L;

	while (*s != NULL)
	{
		while ( (*s != NULL))
		{
			y = y0;
			if (s[0] >= 0)
			{
				eng[0] = s[0];
                offset = fontsize*fontsize/2/8  *  (int)s[0] ;
                fseek(hzk_p, offset, SEEK_SET);
                fread(mat, fsize/2, 1, hzk_p); 
				int byte=0;
				for (i = 0; i < fontsize; i++)
				{
					for (j = 0; j < fontsize/2; j++)   
					{
						if (( mat[byte]>> (7 - j))&1)   
							SetPixel(x + j, y, r,g,b);
                        
					}
                    byte++;
					y++;
				}
				s += 1;
				x += 10;				
			}
		}
	}
	fclose(hzk_p);

}
void PixelBuffer::Line(int x1, int y1, int x2, int y2,unsigned char rr,unsigned char gg,unsigned char bb)
{
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));

	int d, d1, d2;
	if (-a <= b)		// 斜率绝对值 <= 1
	{
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while(x != x2)
		{
			SetPixel(x,y,rr,gg,bb);

			if (d < 0)
				y += cy, d += d2;
			else
				d += d1;
			x += cx;
		}
	}
	else				// 斜率绝对值 > 1
	{
		d = 2 * b + a; 
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while(y != y2) 
		{ 
			SetPixel(x,y,rr,gg,bb);

			if(d < 0)
				d += d1; 
			else 
				x += cx, d += d2; 
			y += cy; 
		} 
	}
}

void PixelBuffer::Line(int x1, int y1, int x2, int y2,Pixel c){
    auto [rr,gg,bb] = c;
    Line(x1,y1,x2,y2,rr,gg,bb);
}