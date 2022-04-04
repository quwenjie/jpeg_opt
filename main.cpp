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
    Eigen::MatrixXi m;
    PixelBuffer y(1280,960);
    if(argc >3 || argc==1)
    {
        cout << "Usage: ippr [photo name]  [(optional)]" << endl;
        return 0;
    }
    int thr=215;
    if(argc==3)
        sscanf(argv[2],"%d",&thr);
    /*
    if (!strcmp(argv[2],"1"))
    {
        */
        PixelBuffer buf{argv[1]};
        
        cout <<"read time "<< time_cost() << endl;

        PixelBuffer buf2=buf.downscale(2);
        memcpy(y.GetBuffer(),buf.GetBuffer(),y.GetWidth()*y.GetHeight()*3);
        cout <<"downscale time "<<time_cost() << endl;

        m = buf2.Threshold(thr,255);
    /*
    }
    else
    {
        PixelBuffer bufx{argv[1]};
        cout <<"load time "<<time_cost() << endl;

        m = bufx.Threshold(thr,255);
    }
    */
    cout <<"thresh time "<< time_cost() << endl;
    vector<vector<pii> > components;
    auto mask=FindCorner(m);
    mask=dilate<1>(mask);
    Eigen::MatrixXi m2(1-(1-m.array())*mask.array()),eroded;

    cout <<"calculate mask time "<< time_cost() << endl;
    /*
    if (!strcmp(argv[2],"3"))  //use old
    {
        cout<<"classical segment"<<endl;
        eroded = erode<1>(m2); 
        components=FindConnectedComponents(eroded);
    }
    else
    {
        */
        auto m3=fix_white(m2);

        eroded = erode<2>(m3); 
    
        cout <<"fix white+ erode time "<< time_cost() << endl;

        auto [components_,seg] = ErodedGrow(m3,eroded);
        components=components_;
    //}

    cout << components.size()<<" Connectivity Analysis time " << time_cost() << endl;
    //PixelBuffer y(org,true);

    PixelBuffer t(eroded,true);
    
    int id=0;
    cout<<components.size()<<endl;
    for(auto vec : components)
    {
        cout<<"before pca"<<endl;
        auto [ret,ori_bound] = PCA_angle(vec);
        cout<<"after pca"<<endl;
        double center_x=ret[0];
        double center_y=ret[1];
        double ang=ret[2];
        int mn_x = ori_bound[0],mx_x = ori_bound[1],mn_y = ori_bound[2],mx_y = ori_bound[3];
        y.Line(2*int(center_x-50*cos(ang)),2*int(center_y-50*sin(ang)),2*int(center_x+50*cos(ang)),2*int(center_y+50*sin(ang)));
        y.DrawCross(2*int(center_x),2*int(center_y),10);
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
        y.DrawASCII(2*mn_x,2*mn_y-14,tmp);
        y.Line(2*mn_x,2*mn_y,2*mx_x,2*mn_y,ComponentsColor[compType]);
        y.Line(2*mn_x,2*mn_y,2*mn_x,2*mx_y,ComponentsColor[compType]);
        y.Line(2*mn_x,2*mx_y,2*mx_x,2*mx_y,ComponentsColor[compType]);
        y.Line(2*mx_x,2*mn_y,2*mx_x,2*mx_y,ComponentsColor[compType]);
        
        //cout<<"Positon: "<<center_x<<" "<<center_y<<" Rectangle "<<xmax-xmin<<" "<<ymax-ymin<<" "<<"ratio "<<S/rectS<<endl;
        id++;
    }
    cout << "PCA+Recog time " << time_cost() << endl;
    
    PixelBuffer masks(mask,true);
    PixelBuffer filtered(m2,true);
    //r.Save("thresh_out.jpg");  
    t.Save("erode.jpg");
    masks.Save("mask.jpg");
    filtered.Save("afterfilter.jpg");
    
    y.Save("recog.jpg");
    

    return 0;
}