#pragma once
#ifndef JACOBIAN_H
#define JACOBIAN_H
#include "Eigen/Dense"
#include <vector>
class Jacobian
{
	private:
		static Eigen::Matrix<double, 4, 4> getJacobian(std::vector<double> theta);


	public:
		static Eigen::MatrixXd getChangeInAngles(std::vector<double> currentPositions, std::vector<double> deltaPositions);

};
#endif

