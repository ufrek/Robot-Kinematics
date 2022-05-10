#pragma once
#ifndef JACOBIAN_H
#define JACOBIAN_H
#include "Eigen/Dense"
#include <vector>
class Jacobian
{
	private:
		static Eigen::Matrix<double, 4, 4> getJacobian(double* theta);


	public:
		static Eigen::MatrixXd getChangeInAngles(double* currentPositions, std::vector<double> deltaPositions);

};
#endif

