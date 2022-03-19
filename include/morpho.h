#pragma once
#include "intellisense.h"
#include "Eigen/Dense"

template<int kerSize>
Eigen::MatrixXi erode(Eigen::MatrixXi &mat,Eigen::Matrix<int,2 * kerSize + 1,2 * kerSize + 1> &ker){
    int w = mat.rows();
    int h = mat.cols();
    Eigen::MatrixXi res(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            if(i >= kerSize && j >= kerSize && i + kerSize < w && j + kerSize < h){
                auto subMat = mat(Eigen::seqN(i - kerSize,2 * kerSize + 1),Eigen::seqN(j - kerSize,2 * kerSize + 1));
                //int t = (ker.array() * subMat.array()).minCoeff();
                res(i,j) = subMat.maxCoeff();
            }else{
                res(i,j) = mat(i,j);
            }
        }
    }
    return res;
}

template<int kerSize>
Eigen::MatrixXi dilate(Eigen::MatrixXi &mat,Eigen::Matrix<int,2 * kerSize + 1,2 * kerSize + 1> &ker){
    int w = mat.rows();
    int h = mat.cols();
    Eigen::MatrixXi res(w,h);
    for(int i = 0;i < w;i++){
        for(int j = 0;j < h;j++){
            if(i >= kerSize && j >= kerSize && i + kerSize < w && j + kerSize < h){
                auto subMat = mat(Eigen::seqN(i - kerSize,2 * kerSize + 1),Eigen::seqN(j - kerSize,2 * kerSize + 1));
                //int t = (ker.array() * subMat.array()).minCoeff();
                res(i,j) = subMat.minCoeff();
            }else{
                res(i,j) = mat(i,j);
            }
        }
    }
    return res;
}

