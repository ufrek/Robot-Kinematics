#pragma once
#include <vector>
#include "MotorModel.h"
#include <list>
class Action
{
public:
	Action(char inpath[40]);
	std::vector<double> weights;
	std::vector<double> centers;
	std::vector<double> stdev;
	std::vector<double> CalculateAngles(float duration);
	static double angleFromGaussian(MotorModel m, float duration);
	
};

