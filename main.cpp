#include "intellisense.h"
#include "jpeg.h"
#include "ddraw.h"
#include "morpho.h"
#include <iostream>
#include <Eigen/Dense>
#include <time.h>
using namespace std;

int main()
{
    clock_t clk;
    clk = clock();
    PixelBuffer buf{"9.jpg"};
    auto m = buf.Threshold(200,250);
    Eigen::Matrix<int,5,5> ker;
    ker << 1,1,1,1,1,
           1,1,1,1,1,
           1,1,1,1,1,
           1,1,1,1,1,
           1,1,1,1,1;        
    auto eroded = erode<2>(m,ker); 
       
    PixelBuffer r(m,true);
    r.Save("123.jpg");   
    PixelBuffer t(eroded,true);
    t.Save("234.jpg");
    auto d = dilate<2>(eroded,ker);
    PixelBuffer y(d,true);
    y.Save("345.jpg");
    clk = clock() - clk;
    cout << (double) clk / CLOCKS_PER_SEC << endl;
    return 0;
}