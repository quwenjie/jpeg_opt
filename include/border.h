#pragma once
#include "intellisense.h"
#include "Eigen/Dense"
#include <queue>
#include <vector>
#include <utility>
using namespace std;
using pii = pair<int,int>;
Eigen::MatrixXi FindCorner(Eigen::MatrixXi &m);
void Line_Midpoint(Eigen::MatrixXi &m,int x1, int y1, int x2, int y2);
