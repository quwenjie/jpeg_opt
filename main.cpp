#include "intellisense.h"
#include <iostream>
#include <Eigen/Dense>
#include <algorithm>
#include "jpeg.h"
#include "ddraw.h"
#include "morpho.h"
#include "util.h"
using namespace std;

double time_cost();

int main()
{
    char fn[20];
    cout<<"Enter filename!"<<endl;
    cin>>fn;

    PixelBuffer buf{fn};
    cout <<"read time "<< time_cost() << endl;

    PixelBuffer buf2=buf.downscale(2);
    cout <<"downscale time "<<time_cost() << endl;

    auto m = buf2.Threshold(200,255);

    cout <<"thresh time "<< time_cost() << endl;
      
    auto eroded = erode<1>(m); 
    
    cout <<"erode time "<< time_cost() << endl;

    PixelBuffer r(m,true);

    cout <<"convert time "<<time_cost() << endl;

    PixelBuffer t(eroded,true);

    //cout <<"convert time2 "<<time_cost()  << endl;
    //auto d = dilate<1>(eroded);
    //cout << "dilate time "<<time_cost() << endl;
    //PixelBuffer y(d,true);
    //cout << "convert time "<<time_cost()  << endl;

    auto components = FindConnectedComponents(eroded);
     
    cout << "Connectivity Analysis time " << time_cost() << endl;

    

    for(auto [tx,ty] : components)
    {
        t.DrawCross(tx,ty,5);
    }

    r.Save("123.jpg");  
    t.Save("234.jpg");
   // y.Save("345.jpg");
    
    return 0;
}