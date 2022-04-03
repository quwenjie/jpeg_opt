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
#include "dicision.h"
#include <cmath>
using namespace std;
using pff = pair<double,double>;
double time_cost();

int main(int argc,char **argv)
{
    if(argc != 2){
        cout << "Usage: ippr [photo name] " << endl;
        return 0;
    }

    PixelBuffer buf{argv[1]};
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

    vector<vector<pii> > components = FindConnectedComponents(eroded);
    vector<vector<pii> > components2 = FindConnectedComponents(m2);
     
    cout << "Connectivity Analysis time " << time_cost() << endl;
    if( components.size()==components2.size()) //use before eroded
    {
        eroded=m2;
        components=components2;
    }
    PixelBuffer y(eroded,true);
    PixelBuffer t(eroded,true);
    cout << "convert time " << time_cost() << endl;
    int id=0;
    for(auto &vec : components)
    {
        auto [ret,ori_bound] = PCA_angle(vec);
        
        double center_x=ret[0];
        double center_y=ret[1];
        double ang=ret[2];
        int mn_x = ori_bound[0],mx_x = ori_bound[1],mn_y = ori_bound[2],mx_y = ori_bound[3];
        y.Line(int(center_x-50*cos(ang)),int(center_y-50*sin(ang)),int(center_x+50*cos(ang)),int(center_y+50*sin(ang)));
        y.DrawCross(int(center_x),int(center_y),5);
        auto rotated=logical_rotate(vec,-ang);
        double xmin=1e9,ymin=1e9,xmax=-1e5,ymax=-1e5;
        for(auto &[x,y] : rotated)
        {
            xmin=min(x,xmin);
            ymin=min(y,ymin);
            xmax=max(x,xmax);
            ymax=max(y,ymax);
        }
        double S=vec.size();
        double rectS=(xmax-xmin)*(ymax-ymin);
        bool isNail = judge_nail(rotated,xmax,xmin);
        auto compType = judge(S,rectS,xmax-xmin,ymax-ymin,isNail);
        printf("%d Position: %lf %lf Angle: %lf Rectangle: %lf %lf Size: %lf RectSize: %lf Ratio: %lf %s\n",id,center_x,center_y,ang*180/3.141593,xmax-xmin,ymax-ymin,S,rectS,S/rectS,ComponentsTypeName[compType].c_str());
        char tmp[100];
        sprintf(tmp,"%d,%s",id,ComponentsTypeName[compType].c_str());
        y.DrawASCII(mn_x,mn_y-14,tmp);
        y.Line(mn_x,mn_y,mx_x,mn_y,ComponentsColor[compType]);
        y.Line(mn_x,mn_y,mn_x,mx_y,ComponentsColor[compType]);
        y.Line(mn_x,mx_y,mx_x,mx_y,ComponentsColor[compType]);
        y.Line(mx_x,mn_y,mx_x,mx_y,ComponentsColor[compType]);
        
        //cout<<"Positon: "<<center_x<<" "<<center_y<<" Rectangle "<<xmax-xmin<<" "<<ymax-ymin<<" "<<"ratio "<<S/rectS<<endl;
        id++;
    }
    cout << "PCA+Recog time " << time_cost() << endl;
    
    PixelBuffer masks(mask,true);
    PixelBuffer filtered(m2,true);
    r.Save("thresh.jpg");  
    t.Save("erode.jpg");
    masks.Save("mask.jpg");
    filtered.Save("afterfilter.jpg");
    
    y.Save("recog.jpg");
    

    return 0;
}