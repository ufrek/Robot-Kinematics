#include "TrainingData.h"
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

std::vector<double> motor0Angles;
std::vector<double> motor1Angles;
std::vector<double> motor2Angles;
std::vector<double> motor3Angles;
std::vector<double> motor4Angles;
std::vector<double> motor5Angles;

std::vector<std::vector<std::vector<double>>> actions;



//Takes in acsv and outputs recorded motor angles from the csv
TrainingData::TrainingData() 
{

}

//So each row of the CSV file has 6 values, one for each motor
void TrainingData::importAction(std::string inpath)
{
	std::ifstream indata;
	indata.open(inpath); // Input csv file to read, "input.csv" or whatever.
	char inputrow[6]; // row that is currently being read
	double data[6]{ 0,0,0, 0,0,0 }; // data that will be read and applied from read inputrow

	indata.getline(inputrow, 6, '\n'); // Reads in the first 3 elements and puts them into inputrow.
	std::string var = ""; // no idea

////////////////////////////////////////////////////////////TODO: NOT SURE IF THIS IS RIGHT CHECK THIS OVER
	for (char x : inputrow) {
		if (x == ',') {
			data[0] = std::stod(var);
			var = "";
		}
		else {
			var = var + x;
		}
	}


//TODO: Make sure I'm doing this right
	// Goes through whole file and adds each column value to corresponding motorAngle vector
	while (true) 
	{
	
		if (indata.eof()) break;
	
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
		//printf("%f %f %f \n", data[0], data[1], data[2]);

		motor0Angles.push_back(data[0]);
		motor1Angles.push_back(data[1]);
		motor2Angles.push_back(data[2]);
		motor3Angles.push_back(data[3]);
		motor4Angles.push_back(data[4]);
		motor5Angles.push_back(data[5]);
	}
	std::vector<std::vector<double>> vec{ motor0Angles, motor0Angles, motor0Angles, motor0Angles, motor0Angles, motor0Angles };
	actions.push_back(vec);

}

//returns the motor ngles based on current action and unscaled duration
std::vector<double> TrainingData::GetAngle(int currentAction, std::vector<float> duration)
{
	std::vector<std::vector<double>> action = actions.at(currentAction);
	
	std::vector<double> result(6);
	int index = duration.at(currentAction) * motor0Angles.size() * 2; //this will unscale the duration increments in Main for just a counter
	//in main it does scaled increments by 1/(size * 2)



	for (int i = 0; i < action.size(); i++) //should be 6 motors here
	{
		result.push_back(action.at(i).at(index));
	}

	return result;

}

//use this to scale the size of the incrementFactor in Main() 
int TrainingData::getActionSize(int currentAction)
{
	std::vector<std::vector<double>> action = actions.at(currentAction);
	std::vector<double> motorData = action.at(0);
	return motorData.size();
}
