#pragma once
#include "DataSet.h"
#include "Action.h"
#include <vector>
#include<list>

class GaussianMixModel 
{
	private:
		static double angleFromGaussian(float duration, double* weights, double* centers, double* std);
	

	public:
		GaussianMixModel(std::vector<Action> a);
		//can make non-static version later
		static std::vector<double> CalculateMotorAngles(int actionIndex, std::vector<float> duration);
		static void cradleToHomeAngles(float duration);
		static void DrawAngles(float duration);
		static void homeToCradleAngles(float duration);

		std::vector<double> GetActionAngles(int actionIndex, std::vector<float>duration);


	
};

