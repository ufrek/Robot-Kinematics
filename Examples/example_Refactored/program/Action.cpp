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