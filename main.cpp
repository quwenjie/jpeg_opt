#include "intellisense.h"
#include "jpeg.h"
#include "ddraw.h"
#include "morpho.h"
#include "util.h"
#include <iostream>
#include <Eigen/Dense>
using namespace std;

int main()
{
    
    PixelBuffer buf{"picture/9.jpg"};

    cout <<"read time "<<time_cost() << endl;
    PixelBuffer buf2=buf.downscale_2();
    cout <<"downscale time "<<time_cost() << endl;

    auto m = buf2.Threshold(200,255);

    cout <<"thresh time "<< time_cost() << endl;
    
    Eigen::Matrix<int,5,5> ker;
    ker << 1,1,1,1,1,
           1,1,1,1,1,
           1,1,1,1,1,
           1,1,1,1,1,
           1,1,1,1,1;     
           
    //Eigen::Matrix<int,3,3> ker;
    //ker << 1,1,1,
    //       1,1,1,
    //       1,1,1;      
    auto eroded = erode<2>(m,ker); 
    
    cout <<"erode time "<< time_cost() << endl;

    PixelBuffer r(m,true);

    cout <<"convert time "<<time_cost() << endl;


    PixelBuffer t(eroded,true);

    cout <<"convert time2 "<<time_cost()  << endl;


    auto d = dilate<2>(eroded,ker);


    cout << "dilate time "<<time_cost() << endl;


    PixelBuffer y(d,true);

    cout << "convert time "<<time_cost()  << endl;


    r.Save("123.jpg");  
    t.Save("234.jpg");
    y.Save("345.jpg");
    
    return 0;
}