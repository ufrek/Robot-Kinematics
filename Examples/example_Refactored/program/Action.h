#pragma once
#include <vector>
#include "MotorModel.h"
#include <list>
class Action
{
public:
	Action();
	std::vector<double> CalculateAngles(float duration);
	static double angleFromGaussian(MotorModel m, float duration);
	

	

private:
	
	
	
};

