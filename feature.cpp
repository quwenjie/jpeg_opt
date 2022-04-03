#include "feature.h"
using namespace std;
using pii = pair<int,int>;
using pff = pair<double,double>;


vector<pff> logical_rotate(vector<pii>& v,double ang)  //rotate ANG
{
    double si=sin(ang),cs=cos(ang);
    vector<pff> retx;
    retx.reserve(2000);
    double xx,yy;
    for(auto [x,y] : v)
    {
        xx=cs*x-si*y;
        yy=si*x+cs*y;
        retx.push_back(make_pair(xx,yy));
    }

    return retx;
}


void reverse(double a[],int cnt){
    for(int i = 0;i < cnt / 2;i++){
        swap(a[i],a[cnt-1-i]);
    }
}
bool judge_nail(vector<pff> &rotated,double maxX,double minX,bool hard){
    const int num_pieces = 10;
    double piece_cnt[num_pieces + 10] = {0};
    const double sp = (maxX - minX)/ num_pieces;
    for(auto [x,y] : rotated)
    {
        piece_cnt[int((x - minX) / sp)]++;
    }
    
    //cout<<piece_cnt<<endl;
    if(piece_cnt[0]>=piece_cnt[1] && piece_cnt[1]>=piece_cnt[2])
    {
        //cout<<"reverse"<<endl;
        reverse(piece_cnt,num_pieces);  // ascending
    }
    else if(piece_cnt[num_pieces-1]/piece_cnt[num_pieces-2]<0.9&&piece_cnt[num_pieces-2]/piece_cnt[num_pieces-3]<0.9)
    {
        reverse(piece_cnt,num_pieces);  // ascending
    }
    
    // for(auto &it : piece_cnt)
    // {
    //      cout << it << " ";
    // }
    // cout<<endl;
    // cout << 1.0*piece_cnt[0] / piece_cnt[1] << endl;
 
    if(fabs(1.0 * piece_cnt[0] / piece_cnt[1] - 0.5) < 0.1 )
    {
        //cout<<"top "<<endl;
        return true;
            //cout << "Nail "; 
    }
    else if(piece_cnt[0]/piece_cnt[1]<0.8 && piece_cnt[1]/piece_cnt[2]<0.8)
    {
        //cout<<"0.8!!!"<<endl;
        return true;
    }
    else
    {
            return false;
            //cout << "Not Nail" << " ";
    }
    
    return false;
}
