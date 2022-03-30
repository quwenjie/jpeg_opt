#include <bits/stdc++.h>
#include "border.h"
using namespace std;
// 使用中点算法画任意斜率的直线（包括起始点，不包括终止点）
void Line_Midpoint(Eigen::MatrixXi &m,int x1, int y1, int x2, int y2,int col)
{
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));

	int d, d1, d2;
	if (-a <= b)		// 斜率绝对值 <= 1
	{
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while(x != x2)
		{
			m(x,y)=col;

			if (d < 0)
				y += cy, d += d2;
			else
				d += d1;
			x += cx;
		}
	}
	else				// 斜率绝对值 > 1
	{
		d = 2 * b + a; 
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while(y != y2) 
		{ 
			m(x,y)=col;

			if(d < 0)
				d += d1; 
			else 
				x += cx, d += d2; 
			y += cy; 
		} 
	}
}
void  fill_from_point(Eigen::MatrixXi &mat,int sx,int sy,int col)
{
    using pii = pair<int,int>;
    int n = mat.rows(),m = mat.cols();
    vector<pii> res;
    queue<pii> q;
    int dx[] = {0,-1,0,1};
    int dy[] = {-1,0,1,0}; 
    q.push(make_pair(sx,sy));
    while(!q.empty())
    {
        auto [x,y] = q.front();
        q.pop();
        for(int k = 0;k < 4;k++)
        {
            if(x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !mat(x + dx[k],y + dy[k]))
            {
                q.push(make_pair(x + dx[k],y + dy[k]));
                mat(x + dx[k],y + dy[k]) = col;
            }
        }
    }
}
Eigen::MatrixXi FindCorner(Eigen::MatrixXi &m)
{
    int N = m.rows(),M = m.cols();
    pii ymax=make_pair(0,-1),xmax=make_pair(-1,0),xmin=make_pair(10000,0),ymin=make_pair(0,10000);
    for(int i = 0;i < N;i++) 
        for(int j = 0;j < M;j++)
        {
            if(m(i,j))
            {
                pii mp=make_pair(i,j);
                if(xmax.first<=i)
                    xmax=mp;
                if(xmin.first>=i)
                    xmin=mp;
                if(ymax.second<=j)
                    ymax=mp;
                if(ymin.second>=j)
                    ymin=mp;
            }
        }
    vector<pii> ret;
    ret.push_back(xmax);
    ret.push_back(xmin);
    ret.push_back(ymax);
    ret.push_back(ymin);

    Eigen::MatrixXi mask(640,480);
    for(int i=0;i<4;i++)
    {
        for(int j=i+1;j<4;j++)
        {
            if(abs(ret[i].first-ret[j].first)>50 && abs(ret[i].second-ret[j].second)>50) //not neighbor corner
                continue;
            Line_Midpoint(mask,ret[i].first,ret[i].second,ret[j].first,ret[j].second,1);
        }
    }

    fill_from_point(mask,320,240,1);
    
    return mask;
}

