//
// Created by chad on 28/08/23.
//

#pragma once

#include <eigen/Eigen/Dense>
#include <vector>
#include <utility>

Eigen::MatrixXd removeRowsWithNaN(const Eigen::MatrixXd &data);
Eigen::MatrixXd normalize(const Eigen::MatrixXd &data);
Eigen::MatrixXd standardize(const Eigen::MatrixXd &data);
std::pair<Eigen::MatrixXd, Eigen::MatrixXd> trainTestSplit(const Eigen::MatrixXd &data, double trainRatio = 0.8);
