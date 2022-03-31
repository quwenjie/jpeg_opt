#include "morpho.h"
#include <iostream>
using namespace std;
Eigen::MatrixXi used(640,480);
vector<vector<pii> >  FindConnectedComponents(Eigen::MatrixXi &mat)
{
    using pii = pair<int,int>;
    int n = mat.rows(),m = mat.cols();
    
    queue<pii> q;
    int dx[] = {0,-1,0,1,-1,1,-1,1};
    int dy[] = {-1,0,1,0,-1,1,1,-1}; 
    
    used.setZero();
    vector<vector<pii> > ret;
    for(int i = 0;i < n;i++) for(int j = 0;j < m;j++)
    {
        if(!used(i,j) && !mat(i,j))
        {
            vector<pii> tmp;
            tmp.reserve(5000);
            q.push(make_pair(i,j));
            Eigen::Vector2d centre(i,j);
            int size = 0;
            while(!q.empty())
            {
                auto [x,y] = q.front();
                q.pop();
                for(int k = 0;k < 8;k++){
                    if(x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !used(x + dx[k],y + dy[k]) && !mat(x + dx[k],y + dy[k]))
                    {
                        pii pt=make_pair(x + dx[k],y + dy[k]);
                        q.push(pt);
                        tmp.push_back(pt);
                        used(x + dx[k],y + dy[k]) = 1;
                    }
                }
            }
            if(tmp.size() >= 50 && tmp.size() < 50000)
            {
                ret.push_back(tmp);
            }
        }
    }
    return ret;
}
