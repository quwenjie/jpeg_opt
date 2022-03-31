#include "feature.h"
vector<pff> logical_rotate(vector<pii> v,double ang)  //rotate ANG
{
    double si=sin(ang),cs=cos(ang);
    vector<pff> ret;
    for(auto [x,y] : v)
    {
        double xx,yy;
        xx=cs*x-si*y;
        yy=si*x+cs*y;
        ret.push_back(make_pair(xx,yy));
    }
    return ret;
}
