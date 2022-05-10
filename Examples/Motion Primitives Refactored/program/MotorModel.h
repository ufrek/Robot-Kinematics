#pragma once
#include <vector>
class MotorModel
{
public:
	MotorModel(std::vector<double> w, std::vector<double> c, std::vector<double>sdev);
	std::vector<double> getWeights() { return weights; };
	std::vector<double> getCenters() { return centers; };
	std::vector<double> getStdevs() { return stdev; };

private:
	std::vector<double> weights;
	std::vector<double> centers;
	std::vector<double> stdev;

};

