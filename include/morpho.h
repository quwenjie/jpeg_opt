#pragma once
#include "intellisense.h"
#include "Eigen/Dense"
#include <queue>
#include <vector>
#include <utility>


template<int kerSize>
Eigen::MatrixXi erode(Eigen::MatrixXi &mat){
    int w = mat.rows();
    int h = mat.cols();
    Eigen::MatrixXi res(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            if(i >= kerSize && j >= kerSize && i + kerSize < w && j + kerSize < h){
                auto subMat = mat(Eigen::seqN(i - kerSize,2 * kerSize + 1),Eigen::seqN(j - kerSize,2 * kerSize + 1));
                res(i,j) = subMat.maxCoeff();
            }else{
                res(i,j) = mat(i,j);
            }
        }
    }
    return res;
}

template<int kerSize>
Eigen::MatrixXi dilate(Eigen::MatrixXi &mat){
    int w = mat.rows();
    int h = mat.cols();
    Eigen::MatrixXi res(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            if(i >= kerSize && j >= kerSize && i + kerSize < w && j + kerSize < h){
                auto subMat = mat(Eigen::seqN(i - kerSize,2 * kerSize + 1),Eigen::seqN(j - kerSize,2 * kerSize + 1));
                res(i,j) = subMat.minCoeff();
            }else{
                res(i,j) = mat(i,j);
            }
        }
    }
    return res;
}
std::vector<std::pair<int,int> > FindConnectedComponents_white(Eigen::MatrixXi &mat);
std::vector<std::pair<int,int> > FindConnectedComponents(Eigen::MatrixXi &mat);