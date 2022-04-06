#pragma once
#include <vector>
class Action
{
public:
	Action(char *inpath[9]);
	std::vector<double> weights;
	std::vector<double> centers;
	std::vector<double> stdev;
private:
	
};

