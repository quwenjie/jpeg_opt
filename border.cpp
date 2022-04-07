#include "border.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;
using pii = pair<int, int>;
using pff = pair<double, double>;
// 使用中点算法画任意斜率的直线（包括起始点，不包括终止点）
void Line_Midpoint(Eigen::MatrixXi &m, int x1, int y1, int x2, int y2, int col)
{
    int x = x1, y = y1;
    int a = y1 - y2, b = x2 - x1;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));

    int d, d1, d2;
    if (-a <= b) // 斜率绝对值 <= 1
    {
        d = 2 * a + b;
        d1 = 2 * a;
        d2 = 2 * (a + b);
        while (x != x2)
        {
            m(x, y) = col;

            if (d < 0)
                y += cy, d += d2;
            else
                d += d1;
            x += cx;
        }
    }
    else // 斜率绝对值 > 1
    {
        d = 2 * b + a;
        d1 = 2 * b;
        d2 = 2 * (a + b);
        while (y != y2)
        {
            m(x, y) = col;

            if (d < 0)
                d += d1;
            else
                x += cx, d += d2;
            y += cy;
        }
    }
}
void fill_from_point(Eigen::MatrixXi &mat, int sx, int sy, int col)
{
    using pii = pair<int, int>;
    int n = mat.rows(), m = mat.cols();
    vector<pii> res;
    queue<pii> q;
    int dx[] = {0, -1, 0, 1};
    int dy[] = {-1, 0, 1, 0};
    mat(sx, sy) = col;
    q.push(make_pair(sx, sy));
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++)
        {
            if (x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < m && !mat(x + dx[k], y + dy[k]))
            {
                q.push(make_pair(x + dx[k], y + dy[k]));
                mat(x + dx[k], y + dy[k]) = col;
                // cout<<x+dx[k]<<" "<<y+dy[k]<<" "<<mat(x + dx[k],y + dy[k])<<endl;
            }
        }
        // break;
    }
    cout << "*** " << mat(320, 239) << endl;
}

using pff = pair<double, double>;
using Point = pff;

// A global point needed for sorting points with reference
// to the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) +
           (p1.second - p2.second) * (p1.second - p2.second);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);

    if (val == 0)
        return 0;             // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

// Prints convex hull of a set of n points.
vector<Point> convexHull(vector<Point> &points, int n)
{
    // Find the bottommost point
    int ymin = points[0].second, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].second;

        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                           points[i].first < points[min].first))
            ymin = points[i].second, min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted output if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i = 1; i < n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n - 1 && orientation(p0, points[i],
                                        points[i + 1]) == 0)
            i++;

        points[m] = points[i];
        m++; // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3)
        return {};

    // Create an empty stack and push first three points
    // to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }
    vector<Point> ans;
    // Now stack has the output points, print contents of stack
    while (!S.empty())
    {
        Point p = S.top();
        ans.push_back(p);
        //cout << "(" << p.first << ", " << p.second << ")" << endl;
        S.pop();
    }
    return ans;
}


void solve(Eigen::MatrixXi &mask, vector<pff> &p)
{
    int n = p.size();
    auto stackk = convexHull(p,p.size());
    int top = stackk.size();
    for (int i = 1; i < top; i++)
    {
        Line_Midpoint(mask, stackk[i - 1].first, stackk[i - 1].second, stackk[i].first, stackk[i].second, 1);
    }
    Line_Midpoint(mask, stackk[top - 1].first, stackk[top - 1].second, stackk[0].first, stackk[0].second, 1);
    cout << "CONVEX SHAPE " << stackk.size() << endl;
}

Eigen::MatrixXi FindCorner(Eigen::MatrixXi &m)
{
    int N = m.rows(), M = m.cols();
    pii ymax = make_pair(0, -1), xmax = make_pair(-1, 0), xmin = make_pair(10000, 0), ymin = make_pair(0, 10000);
    int dist1 = -1, dist2 = -1, dist3 = -1, dist4 = -1;

    vector<pff> all_border;
    // all_border.push_back(make_pair(0.0, 0.0));
    int dx[] = {0, -1, 0, 1, -1, 1, -1, 1};
    int dy[] = {-1, 0, 1, 0, -1, 1, 1, -1};
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
            if (fd)
                all_border.push_back(make_pair((double)i, (double)j));
        }

    cout << "BORDER SIZE"
         << " " << all_border.size() << endl;
    Eigen::MatrixXi mask(640, 480);
    mask.setZero();
    /*for (auto [x,y] : all_border)
    {
        mask((int)x,(int)y)=1;
    }
    */
    solve(mask, all_border);

    fill_from_point(mask, 320, 240, 1);

    return mask;
}
