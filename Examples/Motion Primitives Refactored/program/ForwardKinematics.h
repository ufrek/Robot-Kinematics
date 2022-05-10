#pragma once
#include "Eigen/Dense"


class ForwardKinematics
{

private:


	//functions
	//Eigen::Matrix4f getresult(double alpha, double a, double d, double angle);

	 //Eigen::Matrix4f cdhparam(double* angles);

public:
	static double* getXYZ(double* angleArray);
	static double torad(double angle);
};

