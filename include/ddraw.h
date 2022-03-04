#pragma once
#include <tuple>
#include "jpeg.h"

class PixelBuffer{
public:
    typedef std::tuple<char,char,char> Pixel;
    PixelBuffer() : buf(nullptr),w(0),h(0){}
    PixelBuffer(char *file_name){
        read_JPEG_file(file_name, &buf, &w, &h);
    }
    PixelBuffer(int width,int height) : buf(new char[width * height * 3]),
                                        w(width),h(height){}
    ~PixelBuffer(){
        delete[] buf;
    }
    PixelBuffer(const PixelBuffer&) = delete;
    PixelBuffer& operator=(const PixelBuffer&) = delete;
    Pixel GetPixel(int x,int y);
    char GetR(int x,int y);
    char GetG(int x,int y);
    char GetB(int x,int y);
    void SetPixel(int x,int y,char r,char g,char b);
    void Save(char *file_name);
private:
    char *buf;
    int w,h;
};