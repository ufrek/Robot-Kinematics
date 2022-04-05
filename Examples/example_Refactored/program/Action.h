#pragma once
#include <vector>
class Action
{
public:
	Action(std::vector<double> w, std::vector<double> c, std::vector<double>sdev);

private:
	std::vector<double> weights;
	std::vector<double> centers;
	std::vector<double> stdev;
};

