#include "GaussianMixModel.h"
#include <math.h>
#include <vector>
#include <list>
#include "Action.h"

std::vector<double> output(6);
std::vector<Action> actions;

GaussianMixModel::GaussianMixModel(std::vector<Action> a) 
{
	actions = a;
}


//takes in parameters to add all indiviual gaussians and return an angle
double GaussianMixModel::angleFromGaussian(float duration, double* weights, double* centers, double* std)
{
	//int len = *(&weights + 1) - weights;
	double o = 0;

	for (int i = 0; i < 14; i++)  //
	{
		o = o + weights[i] * exp(-(pow((duration - centers[13 - i]), 2)) / (2 * pow(std[13 - i], 2)));    //centers an std are reversed to make the dot product work

	}
	o = o + weights[14]; //make sure to include intercept
	return o;
}


std::vector<double> GaussianMixModel::GetActionAngles(int actionIndex, std::vector<float>dur)
{
	Action a = actions.at(actionIndex);
	 std::vector<double> result = a.CalculateAngles(dur.at(actionIndex));

	return result;
}