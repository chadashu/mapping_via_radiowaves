//
// Created by chad on 28/08/23.
//

#include "net_engine_header.h"
#include <iostream>
#include <eigen/Eigen/Dense>
#include <vector>

Eigen::MatrixXd removeRowsWithNaN(const Eigen::MatrixXd &data) {
    // Determine the number of valid rows (those without NaN)
    int validRowCount = 0;
    for (int i = 0; i < data.rows(); ++i) {
        if (!data.row(i).hasNaN()) {
            validRowCount++;
        }
    }

    // If all rows are valid, return the input matrix as-is
    if (validRowCount == data.rows()) {
        return data;
    }

    // Construct the resulting matrix with the valid rows
    Eigen::MatrixXd cleanedData(validRowCount, data.cols());
    int rowIndex = 0;
    for (int i = 0; i < data.rows(); ++i) {
        if (!data.row(i).hasNaN()) {
            cleanedData.row(rowIndex++) = data.row(i);
        }
    }

    return cleanedData;
}

// Normalize data to [0, 1]
Eigen::MatrixXd normalize(const Eigen::MatrixXd &data) {
    Eigen::VectorXd min_values = data.colwise().minCoeff();
    Eigen::VectorXd max_values = data.colwise().maxCoeff();
    return (data.rowwise() - min_values.transpose()).array().rowwise() / (max_values - min_values).transpose().array();
}



// Standardize data to have mean = 0 and stddev = 1
Eigen::MatrixXd standardize(const Eigen::MatrixXd &data) {
    Eigen::VectorXd mean = data.colwise().mean();
    Eigen::MatrixXd centered = data.rowwise() - mean.transpose();
    Eigen::VectorXd stddev = (centered.array().square().rowwise().sum() / data.rows()).sqrt();
    return centered.array().rowwise() / stddev.transpose().array();
}

// Split data into training and testing
std::pair<Eigen::MatrixXd, Eigen::MatrixXd> trainTestSplit(const Eigen::MatrixXd &data, double trainRatio) {
    int trainSize = static_cast<int>(data.rows() * trainRatio);
    int testSize = data.rows() - trainSize;
    Eigen::MatrixXd trainData = data.topRows(trainSize);
    Eigen::MatrixXd testData = data.bottomRows(testSize);
    return {trainData, testData};
}

