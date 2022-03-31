#include "intellisense.h"
#include <iostream>
#include <Eigen/Dense>
#include <algorithm>
#include "jpeg.h"
#include "ddraw.h"
#include "morpho.h"
#include "border.h"
#include "util.h"
#include "pca.h"
#include "feature.h"
#include <cmath>
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

    auto m = buf2.Threshold(215,255);

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
    //auto d = dilate<1>(eroded);
    //cout << "dilate time "<<time_cost() << endl;


    PixelBuffer y(eroded,true);
    cout << "dilate time "<<time_cost()  << endl;

    auto components = FindConnectedComponents(eroded);
     
    cout << "Connectivity Analysis time " << time_cost() << endl;

    

    for(auto vec : components)
    {
        auto ret=PCA_angle(vec);
        
        double center_x=ret[0];
        double center_y=ret[1];
        double ang=ret[2];
        y.Line(int(center_x-50*cos(ang)),int(center_y-50*sin(ang)),int(center_x+50*cos(ang)),int(center_y+50*sin(ang)));
        y.DrawCross(int(center_x),int(center_y),5);

        auto rotated=logical_rotate(vec,-ang);
        double xmin=1e9,ymin=1e9,xmax=-1e5,ymax=-1e5;
        for(auto [x,y] : rotated)
        {
            xmin=min(x,xmin);
            ymin=min(y,ymin);
            xmax=max(x,xmax);
            ymax=max(y,ymax);
        }
        double S=vec.size();
        double rectS=(xmax-xmin)*(ymax-ymin);
        cout<<"Positon: "<<center_x<<" "<<center_y<<" Rectangle "<<xmax-xmin<<" "<<ymax-ymin<<" "<<"ratio "<<S/rectS<<endl;
    }
    cout << "PCA time " << time_cost() << endl;
    
    PixelBuffer masks(mask,true);
    PixelBuffer filtered(m2,true);
    r.Save("thresh.jpg");  
    t.Save("erode.jpg");
    masks.Save("mask.jpg");
    filtered.Save("afterfilter.jpg");

    y.Save("recog.jpg");
    
    return 0;
}