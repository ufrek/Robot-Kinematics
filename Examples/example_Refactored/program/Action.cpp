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
Action::Action(const char* inpath[9])
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
		printf("%f %f %f \n", data[0], data[1], data[2]);

		weights.push_back(data[0]);
		centers.push_back(data[1]);
		standard_deviations.push_back(data[2]);
	}
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



