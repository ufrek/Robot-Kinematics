#include "Action.h"
#include<vector>
#include<list>
#include "MotorModel.h"
#include "GaussianMixModel.h"
#include "GaussianMixModel.cpp"

std::vector<MotorModel> motorModels;

Action::Action()
{
	
}



double Action::angleFromGaussian(MotorModel m, float duration)
{
	//int len = *(&weights + 1) - weights;
	double out = 0;
	std::vector<double> weights = m.getWeights();
	std::vector<double> centers = m.getCenters();
	std::vector<double> stdevs = m.getStdevs();


	for (int i = 0; i < 14; i++)  //
	{
		out = out + weights[i] * exp(-(pow((duration - centers[13 - i]), 2)) / (2 * pow(std[13 - i], 2)));    //centers an std are reversed to make the dot product work

	}
	out = out + weights[14]; //make sure to include intercept
	return out;
}

std::vector<double> CalculateAngles(float duration)
{
	std::vector<double> outAngles;
	for (MotorModel m : motorModels)
	{
		
		outAngles.push_back(Action::angleFromGaussian(m, duration));
	}

	return outAngles;
}