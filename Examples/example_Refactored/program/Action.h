#pragma once
#ifndef ACTION_H
#define ACTION_H
#include <vector>
#include "MotorModel.h"
#include <list>
#include <string>


class Action
{
public:
	Action(std::string inpath);
	std::vector<double> CalculateActionAngles(float duration);
	static double actionAngleFromGaussian(MotorModel m, float duration);
	

	

private:
	
	
	
};
#endif
