#include "intellisense.h"
#include "jpeg.h"
#include "ddraw.h"
#include <iostream>
#include <Eigen/Dense>
using namespace std;

int main()
{
    PixelBuffer buf = {"0.jpg"};
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            buf.SetPixel(i,j,0,255,0);
    cout << (int)buf.GetR(0,0) << endl;
    buf.Save("targ.jpg");
    auto m = buf.Threshold(200,250,250);
    PixelBuffer t(m);
    t.Save("123.jpg");
    return 0;
}