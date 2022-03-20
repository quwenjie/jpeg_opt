#include "morpho.h"
#include <iostream>
using namespace std;

vector<pair<int,int> >  FindConnectedComponents(Eigen::MatrixXi &mat){
    using pii = pair<int,int>;
    int n = mat.rows(),m = mat.cols();
    vector<pii> res;
    queue<pii> q;
    int dx[] = {0,-1,0,1};
    int dy[] = {-1,0,1,0}; 
    Eigen::MatrixXi used(n,m);
    used.setZero();

    for(int i = 0;i < n;i++) for(int j = 0;j < m;j++){
        if(!used(i,j) && !mat(i,j)){
            q.push(make_pair(i,j));
            Eigen::Vector2d centre(i,j);
            int size = 0;
            while(!q.empty()){
                auto [x,y] = q.front();
                q.pop();
                for(int k = 0;k < 4;k++){
                    if(x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !used(x + dx[k],y + dy[k]) && !mat(x + dx[k],y + dy[k])){
                        q.push(make_pair(x + dx[k],y + dy[k]));
                        used(x + dx[k],y + dy[k]) = 1;
                        centre += Eigen::Vector2d(x + dx[k],y + dy[k]);
                        size++;
                    }
                }
            }
            if(size >= 10 && size < 50000){
                centre /= size;
                res.push_back(make_pair(centre[0],centre[1]));
            }
        }
    }
    return res;
}