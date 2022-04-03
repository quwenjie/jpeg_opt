#include "border.h"
#include<iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;
using pff = pair<double, double>;
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
    mat(sx,sy)=col;
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
                //cout<<x+dx[k]<<" "<<y+dy[k]<<" "<<mat(x + dx[k],y + dy[k])<<endl;
                
            }
        }
        //break;
    }
    cout<<"*** "<<mat(320,239)<<endl;
}
using Point = pff;
#define NN 100000
Point MinA;
double dist(Point A, Point B)
{
    return sqrt((A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second));
}
//计算叉积 判断bc向量到ac向量 是否通过左转得到 >0左转 <0右转  =0共线 
double cross(Point A, Point B, Point C)
{
    return (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
}

bool cmp(Point a, Point b)	//极角排序 
{
    double k = cross(MinA, a, b);
    if (k > 0) return 1;
    if (k < 0) return 0;
    return dist(MinA, a) < dist(MinA, b);
}
vector<Point> Graham(vector<pff>& p,int n)
{
    int top;
    vector<Point> stackk(NN);
    int i;
    for (i = 1; i < n; i++)
        if (p[i].second < p[0].second || (p[i].second == p[0].second && p[i].first < p[0].first))
            swap(p[i], p[0]);
    MinA = p[0];
    sort(p.begin() + 1, p.begin() + n, cmp);
    stackk[0] = p[0];
    stackk[1] = p[1];
    top = 1;
    for (i = 2; i < n; i++)
    {
        //注意这里我们把共线的点也压入凸包里
        //是否满足叉乘大于0 不满足出栈  控制<0或<=0可以控制重点，共线
        while (cross(stackk[top - 1], stackk[top], p[i]) <= 0 && top >= 1) --top;
        stackk[++top] = p[i];
    }
    top++;
    return { stackk.begin(),stackk.begin() + top };
}

void solve(Eigen::MatrixXi &mask,vector<pff>& p)
{
    int n = p.size();
    auto stackk = Graham(p,n);
    double ans = 0.0;
    int top = stackk.size();
    for (int i = 1; i < top; i++) 
    {
        ans += dist(stackk[i - 1], stackk[i]);
        Line_Midpoint(mask,stackk[i-1].first,stackk[i-1].second,stackk[i].first,stackk[i].second,1);
    }
    Line_Midpoint(mask,stackk[top-1].first,stackk[top-1].second,stackk[0].first,stackk[0].second,1);
    cout << "CONVEX SHAPE "<<stackk.size() << endl;
}

Eigen::MatrixXi FindCorner(Eigen::MatrixXi &m)
{
    int N = m.rows(),M = m.cols();
    pii ymax=make_pair(0,-1),xmax=make_pair(-1,0),xmin=make_pair(10000,0),ymin=make_pair(0,10000);
    int dist1 = -1, dist2 = -1, dist3 = -1, dist4 = -1;

    vector<pff> all_border;
    //all_border.push_back(make_pair(0.0, 0.0));
    int dx[] = { 0,-1,0,1,-1,1,-1,1 };
    int dy[] = { -1,0,1,0,-1,1,1,-1 };
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) 
        {
            if (!m(i, j))
                continue;
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
            {
                all_border.push_back(make_pair((double)i, (double)j));
                continue;
            }
            int fd = 0;
            for (int k = 0; k < 4; k++) 
            {
                if (!m(i + dx[k], j + dy[k]))
                {
                    fd = 1;
                    break;
                }
            }
            if(fd)
                all_border.push_back(make_pair((double)i, (double)j));
        }
   
    cout << "BORDER SIZE" << " " << all_border.size() << endl;
    Eigen::MatrixXi mask(640,480);
    mask.setZero();
    /*for (auto [x,y] : all_border)
    {
        mask((int)x,(int)y)=1;
    }
    */
    solve(mask,all_border);

    fill_from_point(mask,320,240,1);
    
    return mask;
}
