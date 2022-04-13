#pragma once

#include <vector>
#include "MotorModel.h"
#include <string>
#include <list>
class Action
{
public:
	Action(std::string inpath);

	std::vector<double> CalculateAngles(float duration);
	static double angleFromGaussian(MotorModel m, float duration);
	
};

