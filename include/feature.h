#pragma once
#include <iostream>
#include <vector>
#include <cmath>

std::vector<std::pair<double,double>> logical_rotate(std::vector<std::pair<int,int>> &v,double ang); //rotate logical pixels
bool judge_nail(std::vector<std::pair<double,double>> &a,double maxX,double minX,bool hard = false);