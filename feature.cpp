#include "feature.h"

using namespace std;
using pii = pair<int,int>;
using pff = pair<double,double>;


vector<pff> logical_rotate(vector<pii>& v,double ang)  //rotate ANG
{
    double si=sin(ang),cs=cos(ang);
    vector<pff> retx;
    retx.reserve(10000);
    double xx,yy;
    for(auto [x,y] : v)
    {
        xx=cs*x-si*y;
        yy=si*x+cs*y;
        //cout<<xx<<" "<<yy<<endl;
        retx.push_back(make_pair(xx,yy));
    }
    cout<<"end rotate"<<endl;
    return retx;
}

bool judge_nail(vector<pff> &rotated,double maxX,double minX,bool hard){
    const int num_pieces = 10;
    vector<int> piece_cnt(num_pieces,0);
    const double sp = (maxX - minX)/ num_pieces;
    for(auto [x,y] : rotated){
        piece_cnt[int((x - minX) / sp)]++;
    }
    // for(auto &it : piece_cnt){
    //     cout << it << " ";
    // }
    // cout << 1.0*piece_cnt[0] / piece_cnt[1] << " " << 1.0* piece_cnt[num_pieces-1] / piece_cnt[num_pieces-2] << " ";
    if(hard){
        if(fabs(1.0 * piece_cnt[0] / piece_cnt[1] - 0.5) < 0.1 && fabs(1.0 * piece_cnt[num_pieces-1] / piece_cnt[num_pieces-2] - 1.8) < 0.2  ||
        fabs(1.0 * piece_cnt[0] / piece_cnt[1] - 1.8) < 0.1 && fabs(1.0 * piece_cnt[num_pieces-1] / piece_cnt[num_pieces-2] - 0.5) < 0.2){
            return true;
            //cout << "Nail "; 
        }else{
            return false;
            //cout << "Not Nail" << " ";
        }
    }else{
        if(fabs(1.0 * piece_cnt[0] / piece_cnt[1] - 0.5) < 0.1 ||
        fabs(1.0 * piece_cnt[num_pieces-1] / piece_cnt[num_pieces-2] - 0.5) < 0.1){
            return true;
            //cout << "Nail "; 
        }else{
            return false;
            //cout << "Not Nail" << " ";
        }
    }
    return false;
}
