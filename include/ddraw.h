#pragma once
#include <intellisense.h>
#include <tuple>
#include "jpeg.h"
#include "Eigen/Dense"

class PixelBuffer
{
public:
    typedef std::tuple<unsigned char,unsigned char,unsigned char> Pixel;
    PixelBuffer(char *file_name){
        read_JPEG_file(file_name, (char**)(&buf), &w, &h);
    }
    PixelBuffer(int width,int height) : buf(new unsigned char[width * height * 3]),
                                        w(width),h(height){}
    PixelBuffer(Eigen::MatrixXi &mat,bool isBoolean) : w(mat.rows()),h(mat.cols()),
                                        buf(new unsigned char[mat.rows() * mat.cols() * 3]){
        for(int i = 0;i < w;i++){
            for(int j = 0;j < h;j++){
                if(isBoolean){
                    if(mat(i,j)){
                        SetPixel(i,j,255,255,255);
                    }else{
                        SetPixel(i,j,0,0,0);
                    }
                }else{
                    SetPixel(i,j,mat(i,j),mat(i,j),mat(i,j));
                }
            }
        }
    }
    ~PixelBuffer(){
        delete[] buf;
    }
    //PixelBuffer(const PixelBuffer&) = delete;
    //PixelBuffer& operator=(const PixelBuffer&) = delete;
    Pixel GetPixel(int x,int y);
    PixelBuffer downscale(int K);
    PixelBuffer downscale_2();
    void clear();
    char GetR(int x,int y);
    char GetG(int x,int y);
    char GetB(int x,int y);
    void SetPixel(int x,int y,unsigned char r,unsigned char g,unsigned char b);
    void SetPixel(int x,int y,Pixel c);
    void Save(char *file_name);
    int GetWidth(){return w;}
    int GetHeight(){return h;}
    Eigen::MatrixXi Gray();
    Eigen::MatrixXi Threshold(int l,int r);
    void DrawCross(int x,int y,int k,unsigned char r=255,unsigned char g=0,unsigned char b=0);
    void Line(int x1, int y1, int x2, int y2,unsigned char r=0,unsigned char g=255,unsigned char b=0);
    void Line(int x1, int y1, int x2, int y2,Pixel c);
    void DrawASCII(int x,int y,const char *s,unsigned char r=255,unsigned char g=0,unsigned char b=0);
    unsigned char* GetBuffer(){ return buf;};
private:
    unsigned char *buf;
    int w,h;
};
