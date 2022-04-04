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
Eigen::MatrixXi fix_white(Eigen::MatrixXi &mat)
{
    using pii = pair<int,int>;
    int n = mat.rows(),m = mat.cols();
    Eigen::MatrixXi ret_mat;
    ret_mat=mat.replicate(1,1);
    queue<pii> q;
    int dx[] = {0,-1,0,1};
    int dy[] = {-1,0,1,0}; 
    
    used.setZero();
    for(int i = 0;i < n;i++) for(int j = 0;j < m;j++)
    {
        if(!used(i,j) && mat(i,j))
        {
            vector<pii> tmp;
            tmp.reserve(5000);
            tmp.push_back(make_pair(i,j));
            q.push(make_pair(i,j));
            
            int size = 0;
            while(!q.empty())
            {
                auto [x,y] = q.front();
                q.pop();
                for(int k = 0;k < 4;k++)
                {
                    if(x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !used(x + dx[k],y + dy[k]) && mat(x + dx[k],y + dy[k]))
                    {
                        pii pt=make_pair(x + dx[k],y + dy[k]);
                        q.push(pt);
                        tmp.push_back(pt);
                        used(x + dx[k],y + dy[k]) = 1;
                    }
                }
            }
            //cout<<tmp.size()<<endl;
            if(tmp.size() < 20000)
            {
                for (auto [x,y]: tmp)
                    ret_mat(x,y)=0;
            }
        }
    }
    return ret_mat;
}

pair<vector<vector<pii> >,Eigen::MatrixXi> ErodedGrow(Eigen::MatrixXi &mat,Eigen::MatrixXi &eroded)
{
    using pii = pair<int,int>;
    vector<vector<pii> > ret;
    int n = mat.rows(),m = mat.cols();
    Eigen::MatrixXi diff=eroded-mat;
    Eigen::MatrixXi Seg(640,480);
    queue<pii> q;
    int dx[] = {0,-1,0,1};
    int dy[] = {-1,0,1,0}; 
    

    //segment
    used.setZero();
    Seg.setZero();
    int cnt=0;
    for(int i = 0;i < n;i++) for(int j = 0;j < m;j++)  //initial segment
    {
        if(!used(i,j) && !eroded(i,j))
        {
            //++cnt;
            //Seg(i,j)=cnt;
            vector<pii> tmp;
            tmp.reserve(5000);
            tmp.push_back(make_pair(i,j));
            q.push(make_pair(i,j));
            
            int size = 0;
            while(!q.empty())
            {
                auto [x,y] = q.front();
                q.pop();
                for(int k = 0;k < 4;k++)
                {
                    if(x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !used(x + dx[k],y + dy[k]) && !eroded(x + dx[k],y + dy[k]))
                    {
                        pii pt=make_pair(x + dx[k],y + dy[k]);
                        q.push(pt);
                        used(x + dx[k],y + dy[k]) = 1;
                        tmp.push_back(pt);
                        //Seg(i,j)=cnt;         //segment
                    }
                }
            }
            if(tmp.size() >50 &&tmp.size() < 50000)
            {
                ++cnt;
                for (auto [x,y]: tmp)
                    Seg(x,y)=cnt;
            }

        }
    }

    cout<<cnt<<endl;
    used=Eigen::MatrixXi(1-eroded.array()); //all black are used
    for(int i=0;i<cnt;i++)
        ret.push_back(vector<pii>());

    for(int i = 0;i < n;i++) for(int j = 0;j < m;j++)     //put them in queue
    {
        if((!eroded(i,j))&&Seg(i,j)>0)
            q.push(make_pair(i,j));
    }
    while(!q.empty())
    {
        auto [x,y] = q.front();
        q.pop();
        auto now=Seg(x,y);
        ret[now-1].push_back(make_pair(x,y));
        for(int k = 0;k < 4;k++)
        {
            if(x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !used(x + dx[k],y + dy[k]) && diff(x + dx[k],y + dy[k])&& Seg(x + dx[k],y + dy[k])==0)
            {
                pii pt=make_pair(x + dx[k],y + dy[k]);
                q.push(pt);
                used(x + dx[k],y + dy[k]) = 1;
                Seg(x+dx[k],y+dy[k])=now;
            }
        }
    }
    return make_pair(ret,Seg);
}
