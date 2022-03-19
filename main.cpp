#include "intellisense.h"
#include "jpeg.h"
#include "ddraw.h"
#include <iostream>
#include <Eigen/Dense>
using namespace std;

int main()
{
    PixelBuffer buf{"9.jpg"};
    auto m = buf.Threshold(200,250);
    PixelBuffer t(m,true);
    t.Save("123.jpg");
    return 0;
}