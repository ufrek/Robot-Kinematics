#include "Action.h"
#include<vector>
#include <iostream>
#include <fstream>
#include <ios>
#include < Windows.h >
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <istream>
#include <sstream>
#include<list>
#include "MotorModel.h"
#include "GaussianMixModel.h"
#include "GaussianMixModel.cpp"

std::vector<MotorModel> motorModels;
std::vector<double> weights0;
std::vector<double> weights1;
std::vector<double> weights2;
std::vector<double> weights3;
std::vector<double> weights4;
std::vector<double> weights5;
std::vector<double> centers0;
std::vector<double> centers1;
std::vector<double> centers2;
std::vector<double> centers3;
std::vector<double> centers4;
std::vector<double> centers5;
std::vector<double> standard_deviations0;
std::vector<double> standard_deviations1;
std::vector<double> standard_deviations2;
std::vector<double> standard_deviations3;
std::vector<double> standard_deviations4;
std::vector<double> standard_deviations5;

std::vector<MotorModel> motorModels;
MotorModel model0;
MotorModel model1;
MotorModel model2;
MotorModel model3;
MotorModel model4;
MotorModel model5;

Action::Action(char inpath[40])
{
	std::vector<double> weights;
	std::vector<double> centers;
	std::vector<double> standard_deviations;

	std::ifstream indata;
	indata.open(*inpath); // Input csv file to read, "input.csv" or whatever.
	char inputrow[3]; // row that is currently being read
	double data[3]; // data that will be read and applied from read inputrow
	
	indata.getline(inputrow, 3, '\n'); // Reads in the first 3 elements and puts them into inputrow.
	std::string var = ""; // no idea

	for (char x : inputrow) {
		if (x == ',') {
			data[0] = std::stod(var);
			var = "";
	}
		else {
			var = var + x;
		}
	}
	int weightcount = data[0]; // Gets the motor weight count from the first element in the file.
	int linecount = weightcount * 6; // Calculates total numbers of line to read.
	
	int counter = 0;
	// Reads the remaining lines of the csv file and saves them into 3 vectors.
	for (int i = 1; i < linecount; i++) {
		int j = 0;
		char row[100];
		indata.getline(row, 100, '\n');
		std::string var = "";
		for (char x : row) {
			if (x == ',') {
				data[j] = std::stod(var);
				j++;
				var = "";
			}
			else {
				var = var + x;
			}
		}
		counter++;
		printf("%f %f %f \n", data[0], data[1], data[2]);

		weights.push_back(data[0]);
		centers.push_back(data[1]);
		standard_deviations.push_back(data[2]);
		int vectorcounter = 0;
		if (counter = weightcount) {
			vectorcounter = 0;
			if (counter == 0) {
				std::copy(weights.begin(), weights.end(), std::back_inserter(weights0));
				std::copy(centers.begin(), centers.end(), std::back_inserter(centers0));
				std::copy(standard_deviations.begin(), standard_deviations.end(), std::back_inserter(standard_deviations0));
			}
			else if (counter == 1) {
				std::copy(weights.begin(), weights.end(), std::back_inserter(weights1));
				std::copy(centers.begin(), centers.end(), std::back_inserter(centers1));
				std::copy(standard_deviations.begin(), standard_deviations.end(), std::back_inserter(standard_deviations1));
			}
			else if (counter == 2) {
				std::copy(weights.begin(), weights.end(), std::back_inserter(weights2));
				std::copy(centers.begin(), centers.end(), std::back_inserter(centers2));
				std::copy(standard_deviations.begin(), standard_deviations.end(), std::back_inserter(standard_deviations2));
			}
			else if (counter == 3) {
				std::copy(weights.begin(), weights.end(), std::back_inserter(weights3));
				std::copy(centers.begin(), centers.end(), std::back_inserter(centers3));
				std::copy(standard_deviations.begin(), standard_deviations.end(), std::back_inserter(standard_deviations3));
			}
			else if (counter == 4) {
				std::copy(weights.begin(), weights.end(), std::back_inserter(weights4));
				std::copy(centers.begin(), centers.end(), std::back_inserter(centers4));
				std::copy(standard_deviations.begin(), standard_deviations.end(), std::back_inserter(standard_deviations4));
			}
			else if (counter == 5) {
				std::copy(weights.begin(), weights.end(), std::back_inserter(weights5));
				std::copy(centers.begin(), centers.end(), std::back_inserter(centers5));
				std::copy(standard_deviations.begin(), standard_deviations.end(), std::back_inserter(standard_deviations5));
			}
			weights.clear();
			centers.clear();
			standard_deviations.clear();
			vectorcounter++;

		}
	}
	model0 = *new MotorModel(weights0, centers0, standard_deviations0);
	motorModels.push_back(model0);
	model1 = *new MotorModel(weights1, centers1, standard_deviations1);
	motorModels.push_back(model1);
	model2 = *new MotorModel(weights2, centers2, standard_deviations2);
	motorModels.push_back(model2);
	model3 = *new MotorModel(weights3, centers3, standard_deviations3);
	motorModels.push_back(model3);
	model4 = *new MotorModel(weights4, centers4, standard_deviations4);
	motorModels.push_back(model4);
	model5 = *new MotorModel(weights5, centers5, standard_deviations5);
	motorModels.push_back(model5);
	indata.close();
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
		out = out + weights[i] * exp(-(pow((duration - centers[13 - i]), 2)) / (2 * pow(stdevs[13 - i], 2)));    //centers an std are reversed to make the dot product work

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



