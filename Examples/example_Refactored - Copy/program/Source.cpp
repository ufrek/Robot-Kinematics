#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <chrono>
#include <thread>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"
#include "ForwardKinematics.h"
#include <iostream>
#include "GaussianMixModel.h"
#include "Action.h"
using namespace std::chrono;
using namespace std::this_thread;

int currentAction = 0;
boolean isTransitioning = false;

//use this to set the speed of the actions of the robot arm
float timeIncrementFactor = (float)(1.0 / 269.0);

//use this to set the speed of transition between actions
float weightIncrementFactor = (float).001;

std::vector<float> durations(3, 0);  //cradle to home, draw, home to cradle

float weights[2] = { 0,0 };

int numberOfActions = 2;


// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 0, 0, 0, 0, 0, 0 };
char com[6] = "COM13";

//blink logic
int currentLight = 0;
int toggle[] = { 0,0,0,0,0,0,0 };

std:: vector<double> outputAngles(6);

void transitionActions(int currentAction)
{
	std::cout << "TRANSITION: \n";
	std::vector<double> oldAction(6);
	if (currentAction == 1)
	{
			oldAction = outputAngles;
		
		outputAngles = GaussianMixModel::CalculateMotorAngles(currentAction, durations);
	}

	if (currentAction == 2)
	{
			oldAction = outputAngles;
		
			outputAngles = GaussianMixModel::CalculateMotorAngles(currentAction, durations);
	}


	for (int i = 0; i < 6; i++)
	{
		double temp = (weights[1] * outputAngles[i]) + (weights[0] * oldAction[i]);
		angles[i] = temp;
	}

	weights[0] -= weightIncrementFactor;
	weights[1] += weightIncrementFactor;

	if (weights[1] >= 1)
	{
		isTransitioning = false;;
	}
}


int main()
{
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);

	
	
	while (1) 
	{

		outputAngles = GaussianMixModel::CalculateMotorAngles(currentAction, durations);
		
		if (isTransitioning)
		{
			transitionActions(currentAction);
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				//std::cout << output[i] << " , ";
				angles[i] = outputAngles[i];

			}
			//std::cout << "\n";


			//increments duration 
			float temp = durations[currentAction] + timeIncrementFactor; 
			durations[currentAction] = temp;
		}

		double* motorPositions = ForwardKinematics::getXYZ(angles);
		for (int i = 0; i < 3; i++)
		{
			std::cout << motorPositions[i] << ", ";
		}
		std::cout << "\n";

		edxl.setTorqueMult(idarr, torque, 6);
		edxl.setAngleMult(idarr, angles, 6);



		if (durations[currentAction] >= 1)
		{
			durations[currentAction] = 1;
			currentAction++;

			if (currentAction == 1)
			{
				timeIncrementFactor = (float)(1.0 / 739.0);
			}
			else if (currentAction == 2)
			{
				timeIncrementFactor = (float)(1.0 / 269.0);
			}



			if (currentAction > numberOfActions)
			{
				break;
			}

			isTransitioning = true;
			weights[0] = 1;
			weights[1] = 0;

			//std::cout << "\n" << " \nCurent Action: " << currentAction;
		}

		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}

		sleep_for(nanoseconds(10));
	}
	
	return 0;
}


