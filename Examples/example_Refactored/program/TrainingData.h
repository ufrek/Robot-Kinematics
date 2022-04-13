#pragma once
#include "Action.h"
#include <vector>
class TrainingData
{
	public:
		TrainingData();
		void importAction(std::string inpath);
		std::vector<double> GetAngle(int currentAction, std::vector<float> duration);
		int getActionSize(int currentAction);
};

