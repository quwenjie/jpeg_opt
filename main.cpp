#include "intellisense.h"
#include <iostream>
#include <Eigen/Dense>
#include <algorithm>
#include "jpeg.h"
#include "ddraw.h"
#include "morpho.h"
#include "border.h"
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
    
    auto mask=FindCorner(m);
    
    Eigen::MatrixXi m2(1-(1-m.array())*mask.array());
    cout <<"calculate mask time "<< time_cost() << endl;

    auto eroded = erode<1>(m2); 
    
    cout <<"erode time "<< time_cost() << endl;

    PixelBuffer r(m,true);

    cout <<"convert time "<<time_cost() << endl;

    PixelBuffer t(eroded,true);

    //cout <<"convert time2 "<<time_cost()  << endl;
    auto d = dilate<1>(eroded);
    //cout << "dilate time "<<time_cost() << endl;
    PixelBuffer y(d,true);
    cout << "dilate time "<<time_cost()  << endl;

    auto components = FindConnectedComponents(d);
     
    cout << "Connectivity Analysis time " << time_cost() << endl;

    

    for(auto [tx,ty] : components)
    {
        y.DrawCross(tx,ty,5);
    }

    PixelBuffer masks(mask,true);
    PixelBuffer filtered(m2,true);
    r.Save("thresh.jpg");  
    t.Save("erode.jpg");
    masks.Save("mask.jpg");
    filtered.Save("afterfilter.jpg");

    y.Save("recog.jpg");
    
    return 0;
}