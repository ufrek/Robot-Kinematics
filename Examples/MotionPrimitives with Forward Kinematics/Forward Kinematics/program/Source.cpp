#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <chrono>
#include <thread>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"
using namespace std::chrono;
using namespace std::this_thread;

#include <iostream>
#include <fstream>


#include "Eigen/Dense"

//  1, 2, 4, 5, 6, 7

double pi = 3.1415926535897932384626433;


//Build our DH Parameter Matrix
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

//DH values lined up in a matrix. Each line is a motor's values
double line0[3] = { 0, 0, 113.25 };
double line1[3] = { pi / 2, 0, 0 };
double line2[3] = { 0, 200, 0 };
double line3[3] = { 0, 50, 0 };
double line4[3] = { 0, 200, 0 };
double line5[3] = { pi / 2, 0, 0 };
double line6[3] = { 0, 0, 174.15 };

//Takes our DH parameter values and returns the transsformation matrix
Eigen::Matrix4f getresult(double alpha, double a, double d, double angle)
{
	double radangle = angle;
	t << cos(radangle), -1 * sin(radangle), 0, a,
		sin(radangle)* cos(alpha), cos(radangle)* cos(alpha), -1 * sin(alpha), -1 * sin(alpha) * d,
		sin(radangle)* sin(alpha), cos(radangle)* sin(alpha), cos(alpha), cos(alpha)* d,
		0, 0, 0, 1;

	return t;
}

//Cnnverts angle degrees to radians
double torad(double angle) {
	return angle * (pi / 180.0);
}

//After getting the transformation matrix, returns the Position values
Eigen::Matrix4f cdhparam(double* angles)
{
	// Line list: in order: alpha, a, d
	a0 = getresult(line0[0], line0[1], line0[2], torad(angles[0]));
	a1 = getresult(line1[0], line1[1], line1[2], torad(angles[1]) - pi / 2);
	a2 = getresult(line2[0], line2[1], line2[2], pi / 2);
	a3 = getresult(line3[0], line3[1], line3[2], torad(angles[2]) - pi);
	a4 = getresult(line4[0], line4[1], line4[2], torad(angles[3]) - pi / 2);
	a5 = getresult(line5[0], line5[1], line5[2], torad(angles[4]));
	a6 = getresult(line6[0], line6[1], line6[2], 0);
	tfinal = a0 * a1 * a2 * a3 * a4 * a5 * a6;
	return tfinal;
}

//Returns the X,Y, and Z positions based on an array of motor angles from the robot arm
double* getXYZ(double* angleArray)
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


//motion primitve variables
double output[6];

//Takes in parameters to add all indiviual gaussians and return an angle
double angleFromGaussian(float duration, double* weights, double* centers, double* std)
{
	//int len = *(&weights + 1) - weights;
	double out = 0;

	for (int i = 0; i < 14; i++)  //
	{
		out = out + weights[i] * exp(-(pow((duration - centers[13 - i]), 2)) / (2 * pow(std[13 - i], 2)));    //centers an std are reversed to make the dot product work

	}
	out = out + weights[14]; //make sure to include intercept
	return out;
}

//The Gaussian Mixture Models for the Cradle to Home Action
//Returns angles based on a normalized duration from  TIme = 0 to 1 
void cradleToHomeAngles(float duration)
{


	output[0] = 180.576;

	double weights1[15] = {
			27.2074324737, 6.9372034318, 19.6523044701, 11.1812252573, 16.6193976876,
			13.3522607571, 16.0649047305, 9.9608924220, 34.9769072043, -83.0513359198,
			-0.2747548491, -62.1391668822, -5.3742342690, -67.8283682875, 150.5226667220
	};

	double centers1[15] = {
			0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
			0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
			0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations1[15] = {
			0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
			0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
			0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[1] = angleFromGaussian(duration, weights1, centers1, deviations1);



	/////////////////////Motor: 2
	double weights2[15] = {
							-26.7870593434, -8.6952489712, -17.6061989962, -14.8666688088, -11.8136387054,
							-21.4675614742, -2.6628736821, -35.4845902467, 10.2208180065, 36.3139001125,
							18.0028125756, 41.3253054851, 10.1174454410, 53.0955863622, 212.4901492674
	};

	double centers2[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations2[15]{
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[2] = angleFromGaussian(duration, weights2, centers2, deviations2);

	///////////////Motor: 3
	double weights3[15] = {
							38.2814341936, 9.9478186760, 27.4949145810, 17.7742240376, 21.3980824221,
							25.0135678824, 8.3720918940, 53.5400356683, -35.9056984151, 73.5380302905,
							-22.7319480377, 66.1180981219, -1.0744800578, 68.3131014906, 137.0858012698
	};

	double centers3[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231,1.0000000000, 0.0
	};

	double deviations3[15] = {
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[3] = angleFromGaussian(duration, weights3, centers3, deviations3);

	///////////////Motor: 4
	double weights4[15] = {
			-8.4634102599, -1.2981990404, -7.0384799012, -1.9683774398, -7.0136991575,
			-1.3331382035, -8.2634894445, 0.5452751964, -9.9876199536, -3.4272372771,
			-4.9993521210, -3.9188417891, -7.7130350161, 2.0125879523, 198.0944956003
	};

	double centers4[15] = {
			0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
			0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
			0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations4[15] = {
			0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
			0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
			0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[4] = angleFromGaussian(duration, weights4, centers4, deviations4);
	if (output[4] < 350)
		output[4] = 350;

	////////////Motor: 5
	double weights5[15] = {
							-0.0000000002, -0.0000000000, -0.0000000000, -0.0000000001, -0.0000000001,
							-0.0000000001, -0.0000000001, -0.0000000001, -0.0000000001, -0.0000000001,
							-0.0000000001, -0.0000000000, -0.0000000000, -0.0000000001, 129.1840000001
	};

	double centers5[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations5[15] = {
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[5] = angleFromGaussian(duration, weights5, centers5, deviations5);
	
	

}

//The Gaussian Mixture Models for the Drawing a Line Action
//Returns angles based on a normalized duration from  Time = 0 to 1 
void DrawAngles(float duration)
{
	//Motor: 0
	double weights0[15] = {
							-15.1967789709, -5.6632028251, -7.9118618080, -3.5053454257, -10.0486971407,
							-3.1979965434, -15.0553915917, 10.7294787863, -4.1870469410, 5.5094270269,
							-1.9940064665, 3.4813460053, -1.2472581409, -9.2991738323, 196.1208024265
	};

	double centers0[15] = {
			0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
			0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
			0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations0[15] = {
					0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
					0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
					0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[0] = angleFromGaussian(duration, weights0, centers0, deviations0);

	/////Motor: 1
	double weights1[15] = {
						74.0945683340, -1.7922429952, 66.7602484763, -16.9845891748, 100.6365308990,
						29.0337138777, 67.6591066374, 46.0045092601, 58.4070750633, 52.0830168909,
						65.9105477859, 37.0730120674, 8.9318334970, 64.4573245906, 86.3810576768
	};

	double centers1[15] = {
						0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
						0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
						0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations1[15] = {
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[1] = angleFromGaussian(duration, weights1, centers1, deviations1);


	//Motor: 2
	double weights2[15] = {
							-111.9606784250, -4.4464023775, -101.9430321645, -29.1260701047,
								-23.9043578171, -45.5122600365, -14.2422731153, -40.1550147151,
								-20.3259431752, -39.5729719255, -36.9448255583, -24.3362663953,
								-37.1252873153, -94.3367772736, 332.0314002172
	};

	double centers2[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations2[15] = {
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[2] = angleFromGaussian(duration, weights2, centers2, deviations2);

	////Motor: 3
	double weights3[15] = {
							52.1195432825, 11.4428467940, 44.4568040787, 41.7837979802, -55.9301848683,
							13.1255492930, -31.0801677067, -5.7745165742, -17.8405460505, -14.0554295323,
							-18.6760836000, -1.1002834566, 42.3707353914, 48.9333291059, 108.2945229613
	};

	double centers3[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations3[15] = {
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[3] = angleFromGaussian(duration, weights3, centers3, deviations3);

	///Motor: 4
	double weights4[15] = {
							-0.1958857211, -0.0635818319, -0.1358022656, 0.0491559924, -0.2855887437,
							0.0773146073, -0.3230189721, 0.1567023162, -0.4611105714, 0.3881530057,
							-0.8872823812, 1.1855092125, -0.7717503201, 0.2901037856, 179.2459650286
	};

	double centers4[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations4[15] = {
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[4] = angleFromGaussian(duration, weights4, centers4, deviations4);

	//Motor: 5
	double weights5[15] = {
							-0.1399546717, -0.0218084658, -0.1348402974, -0.0299223580, -0.1180808766,
							-0.0260040161, -0.1124470705, -0.0531812406, -0.0841377682, -0.0836725756,
							-0.0379770086, -0.0965387047, -0.0461422016, -0.1315688800, 169.4142304735
	};

	double centers5[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations5[15] = {
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
								0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[5] = angleFromGaussian(duration, weights5, centers5, deviations5);
}

//The Gaussian Mixture Models for the Cradle to Home Action
//Returns angles based on a normalized duration from  Time = 0 to 1 
void homeToCradleAngles(float duration)
{
	output[0] = 180.576;

	////////Motor: 1
	double weights1[15] = {
							-67.8283682875, -5.3742342690, -62.1391668822, -0.2747548491, -83.0513359197,
							34.9769072044, 9.9608924221, 16.0649047305, 13.3522607570, 16.6193976876,
							11.1812252574, 19.6523044702, 6.9372034318, 27.2074324738, 150.5226667220,
	};

	double centers1[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations1[15] = {
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[1] = angleFromGaussian(duration, weights1, centers1, deviations1);

	/////Motor: 2
	double weights2[15] = {
							53.0955863622, 10.1174454410, 41.3253054851, 18.0028125756, 36.3139001126,
							10.2208180066, -35.4845902467, -2.6628736821, -21.4675614744, -11.8136387055,
							-14.8666688088, -17.6061989962, -8.6952489712, -26.7870593434, 212.4901492674
	};

	double centers2[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations2[15] = {
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[2] = angleFromGaussian(duration, weights2, centers2, deviations2);

	////Motor: 3
	double weights3[15] = {
							68.3131014905, -1.0744800578, 66.1180981219, -22.7319480378, 73.5380302905,
							-35.9056984150, 53.5400356683, 8.3720918939, 25.0135678823, 21.3980824220,
							17.7742240376, 27.4949145809, 9.9478186760, 38.2814341936, 137.0858012699
	};

	double centers3[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations3[15] = {
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[3] = angleFromGaussian(duration, weights3, centers3, deviations3);

	////Motor: 4
	double weights4[15] = {
						2.0125879523, -7.7130350160, -3.9188417891, -4.9993521210, -3.4272372770,
						-9.9876199535, 0.5452751965, -8.2634894446, -1.3331382036, -7.0136991576,
						-1.9683774398, -7.0384799012, -1.2981990404, -8.4634102599, 198.0944956003
	};

	double centers4[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations4[15] = {
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[4] = angleFromGaussian(duration, weights4, centers4, deviations4);

	//Motor: 5
	double weights5[15] = {
							-0.0000000002, -0.0000000000, -0.0000000000, -0.0000000001, -0.0000000001,
							-0.0000000001, -0.0000000001, -0.0000000001, -0.0000000001, -0.0000000001,
							-0.0000000001, -0.0000000000, -0.0000000000, -0.0000000001, 129.1840000001
	};

	double centers5[15] = {
							0.0000000000, 0.0769230769, 0.1538461538, 0.2307692308, 0.3076923077,
							0.3846153846, 0.4615384615, 0.5384615385, 0.6153846154, 0.6923076923,
							0.7692307692, 0.8461538462, 0.9230769231, 1.0000000000, 0.0
	};

	double deviations5[15] = {
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714,
							0.0714285714, 0.0714285714, 0.0714285714, 0.0714285714, 0.0
	};

	output[5] = angleFromGaussian(duration, weights5, centers5, deviations5);
}



//regularly initialized stuff
// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[6] = "COM14";



//Loops through each action and increments a time duration variable from 0 to 1
//Feeds the duration values to get angles from Motion Primitives
//Feeds the calculated Angles into Forward Kinematics Functions to get the position in 3D space.

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	std::ofstream file;
	file.open("positionsActions.txt");

	int currentAction = 0; //which task is currently being played


	boolean isTransitioning = false;


	//use this to set the speed of the actions of the robot arm
	float timeIncrementFactor = 1.0 / 269.0;

	//use this to set the speed of transition between actions
	float weightIncrementFactor = .001;


	float duration[3] = { 0, 0, 0 };  //cradle to home, draw, home to cradle

	float weights[2] = {0,0}; //used to transition angles between two tasks


	int numberOfActions = 2;
	
	while (1) 
	{	
		if (currentAction == 0)
		{

			cradleToHomeAngles(duration[0]);



		}
		else if (currentAction == 1)
		{
			DrawAngles(duration[1]);

		}
		else if (currentAction == 2)
		{

			homeToCradleAngles(duration[2]);

		}

		//if transitioning, initiate motion blur
		if (isTransitioning)
		{
			
			std::cout << "TRANSITION: \n";
			double oldAction[5];
			if (currentAction == 1)
			{
				
				for (int i = 0; i < 6; i++)
				{
					oldAction[i] = output[i];     
				}
				DrawAngles(duration[1]);
			}

			if (currentAction == 2)
			{
				for (int i = 0; i < 6; i++)
				{
					oldAction[i] = output[i];
				}
				homeToCradleAngles(duration[2]);
			}


			for (int i = 0; i < 5; i++)
			{
				double temp = (weights[1] * output[i]) + (weights[0] * oldAction[i]);
				angles[i] = temp;
			}

			weights[0] -= weightIncrementFactor;
			weights[1] += weightIncrementFactor;

			if (weights[1] >= 1)
			{
				isTransitioning = false;;
			}
		}
		else
		{

			for (int i = 0; i < 5; i++)
			{
				//std::cout << output[i] << " , ";
				angles[i] = output[i];
				//std::cout << angles[i] << " , ";

			}
			//std::cout << "\n";
			
			float temp = duration[currentAction] + timeIncrementFactor; ///has to be hardcoded for some reason

			duration[currentAction] = temp;
		}

		double* motorPositions = getXYZ(angles);
		for (int i = 0; i < 3; i++)
		{
			std:: cout << motorPositions[i] << ", ";
		}
		std::cout << "\n";



		edxl.setTorqueMult(idarr, torque, 6);
		edxl.setAngleMult(idarr, angles, 6);

		//std::cout << angles[3] << "\n";
		file << angles[0] << "," << angles[1] << "," << angles[2] << "," << angles[3] << "," << angles[4] << "," << angles[5] << "\n";


		if (GetKeyState('Q') & 0x8000)  //Check if high-order bit is set (1 << 15)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}

		//std::cout << duration[currentAction];
		
		if (duration[currentAction] >= 1)
		{
			duration[currentAction] = 1;
			currentAction++;

			if (currentAction == 1)
			{
				timeIncrementFactor = 1.0 / 739.0;
			}
			else if (currentAction == 2)
			{
				timeIncrementFactor = 1.0 / 269.0;
			}

			

			if (currentAction > numberOfActions)
			{
				break;
			}

			isTransitioning = true;
			weights[0] = 1;
			weights[1] = 0;

			//std::cout << "\n" << " \nCurent Action: " << currentAction;
		}

		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}
		sleep_for(nanoseconds(10));

		

	}

	int close[] = { 0, 0, 0, 0, 0, 0 };

	auto end = std::chrono::system_clock::now();

	edxl.setTorqueMult(idarr, close, 6);
	file.close();
	Sleep(10);
	//std::this_thread::sleep_for(10ns);
	edxl.closePort();
	return 0;
	
	return 0;
}


