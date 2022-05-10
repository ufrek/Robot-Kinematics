#include "ForwardKinematics.h"
#include "Eigen/Dense"

double pi = 3.1415926535897932384626433;


// Matrices for Forward Kinematics.
Eigen::Matrix4f t;
Eigen::Matrix4f a0;
Eigen::Matrix4f a1;
Eigen::Matrix4f a2;
Eigen::Matrix4f a3;
Eigen::Matrix4f a4;
Eigen::Matrix4f a5;
Eigen::Matrix4f a6;
Eigen::Matrix4f tfinal;

double positionArray[3];

double line0[3] = { 0, 0, 113.25 };
double line1[3] = { pi / 2, 0, 0 };
double line2[3] = { 0, 200, 0 };
double line3[3] = { 0, 50, 0 };
double line4[3] = { 0, 200, 0 };
double line5[3] = { pi / 2, 0, 0 };
double line6[3] = { 0, 0, 174.15 };

/*
Returns the result of the DH parameters. Calculates the resulting Matrix.
*/
Eigen::Matrix4f getresult(double alpha, double a, double d, double angle)
{
	double radangle = angle;
	t << cos(radangle), -1 * sin(radangle), 0, a,
		sin(radangle)* cos(alpha), cos(radangle)* cos(alpha), -1 * sin(alpha), -1 * sin(alpha) * d,
		sin(radangle)* sin(alpha), cos(radangle)* sin(alpha), cos(alpha), cos(alpha)* d,
		0, 0, 0, 1;

	return t;
}

// Converts degrees to radians.
double ForwardKinematics::torad(double angle) {
	return angle * (pi / 180.0);
}

// Returns Pi.
double ForwardKinematics::getPi()
{
	return pi;
}

/*
Returns the dot product using the DH matrix and calculates the end effector.
*/
Eigen::Matrix4f cdhparam(double* angles)
{
	// Line list: in order: alpha, a, d
	a0 = getresult(line0[0], line0[1], line0[2], ForwardKinematics::torad(angles[0]));
	a1 = getresult(line1[0], line1[1], line1[2], ForwardKinematics::torad(angles[1]) - pi / 2);
	a2 = getresult(line2[0], line2[1], line2[2], pi / 2);
	a3 = getresult(line3[0], line3[1], line3[2], ForwardKinematics::torad(angles[2]) - pi);
	a4 = getresult(line4[0], line4[1], line4[2], ForwardKinematics::torad(angles[3]) - pi / 2);
	a5 = getresult(line5[0], line5[1], line5[2], ForwardKinematics::torad(angles[4]));
	a6 = getresult(line6[0], line6[1], line6[2], 0);
	tfinal = a0 * a1 * a2 * a3 * a4 * a5 * a6;
	return tfinal;
}

/*
Returns the X Y Z coordinate of the robot arm using forward kinematics.
*/
double* ForwardKinematics::getXYZ(double* angleArray)
{
	Eigen::Matrix4f result = cdhparam(angleArray);
	double x = result.coeff(0, 3);
	double y = result.coeff(1, 3);
	double z = result.coeff(2, 3);
	positionArray[0] = x;
	positionArray[1] = y;
	positionArray[2] = z;
	return positionArray;
}
