#include "pca.h"
vector<double> PCA_angle(vector<pii> vec)
{
    double center_x=0,center_y=0;
        for(auto [x,y]:vec)
        {
            center_x+=x;
            center_y+=y;
        }
        center_x/=vec.size();
        center_y/=vec.size();
        double xx = 0, xy = 0, yy = 0;
        for(auto [x,y]:vec)
        {
            xx += (x - center_x) * (x - center_x);
            xy += (x - center_x) * (y - center_y);
            yy += (y - center_y) * (y - center_y);
        }
        //大小为3*3的协方差矩阵
        Eigen::Matrix2f covMat(2, 2);
        covMat(0, 0) = xx / vec.size();
        covMat(0, 1) = covMat(1, 0) = xy / vec.size();
        covMat(1, 1) = yy / vec.size();
        Eigen::EigenSolver<Eigen::Matrix2f> eigen_solver(covMat);
        Eigen::Matrix2f val = eigen_solver.pseudoEigenvalueMatrix();
        Eigen::Matrix2f vecs=eigen_solver.pseudoEigenvectors();
        int ii = val(0, 0) < val(1, 1);  //0 or 1, the biggest eigen value
        Eigen::Vector2f dir(vecs(0, ii), vecs(1, ii));
        double ang=acos(dir(0));
        if(dir(1)<0)
            ang=2*PI-ang;
    vector<double> ret;
    ret.push_back(center_x);
    ret.push_back(center_y);
    ret.push_back(ang);
    return ret;
}
        //cout<<center_x<<" "<<center_y<<" "<<vec.size()<<" "<<ang<<endl;