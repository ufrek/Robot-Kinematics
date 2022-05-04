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
#include "TrainingData.h"





using namespace std::chrono;
using namespace std::this_thread;

int currentAction = 0;
boolean isTransitioning = false;

//use this to set the speed of the actions of the robot arm
float timeIncrementFactor = (float)(1.0 / 269.0);

//use this to set the speed of transition between actions
float weightIncrementFactor = (float).001;

std::vector<float> durations(3);  //cradle to home, draw, home to cradle

float weights[2] = { 0,0 };

int numberOfActions = -1;  //first action is at index 0


// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };
double Tangles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 0, 0, 0, 0, 0, 0 };
char com[6] = "COM13";

//blink logic
int currentLight = 0;
int toggle[] = { 0,0,0,0,0,0,0 };

std:: vector<double> outputAngles(6);
std::vector<double> trainingAngles(6); // thes are the angles from the training data

void transitionActions(int currentAction, GaussianMixModel* model, TrainingData* t)
{
	std::cout << "TRANSITION: \n";
	std::vector<double> oldAction(6);
	std::vector<double> oldTAction(6);
	
	oldAction = outputAngles;
	oldTAction = trainingAngles;

		
	outputAngles = model->GetActionAngles(currentAction, durations);
	trainingAngles = t->GetAngle(currentAction, durations);



	for (int i = 0; i < 6; i++)
	{
		double temp = (weights[1] * outputAngles[i]) + (weights[0] * oldAction[i]);
		angles[i] = temp;

		double temp2 = (weights[1] * trainingAngles[i]) + (weights[0] * oldTAction[i]);
		Tangles[i] = temp;
	}

	weights[0] -= weightIncrementFactor;
	weights[1] += weightIncrementFactor;

	if (weights[1] >= 1)
	{
		isTransitioning = false;;
	}
}


int main(int argc, char* argv[])
{
	std::cout << argv[0];

	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);

//TODO:: Fix the can't find file errors in here and make sure this runs the way it's supposed to
	std::vector<Action> actionVector;
	const char* test= "\\..\\..\\cradleToHome.csv";
	Action cth = *new Action(test);
	actionVector.push_back(cth);
	numberOfActions++; //increment actions each time you add a new one
	
	char test2[50] = "/../../drawLine.csv";
	Action draw = *new Action(test2);
	actionVector.push_back(draw);
	numberOfActions++;

	char test3[50] = "/../../homeToCradle.csv";
	Action htc = *new Action(test3);
	actionVector.push_back(htc);
	numberOfActions++;

	GaussianMixModel *mixModel = new GaussianMixModel(actionVector);

//TODO: fix the file directories for these files
	TrainingData* tData = new TrainingData();
	char test4[50] = "/../../cradleToHome.csv";
	char test5[50] = "/../../cradleToHome.csv";
	char test6[50] = "/../../cradleToHome.csv";
	tData->importAction(test4);
	tData->importAction(test5);
	tData->importAction(test6);
//test to make sure thimeIncrementFactor works,
//this should scale the time increments based on the length of the training data of the current action
//The first one shoule make this = to 1 / (269 * 2)
	timeIncrementFactor =  1 / (tData->getActionSize(currentAction) * 2); 


	
	
	while (1) 
	{

		outputAngles = mixModel->GetActionAngles(currentAction, durations);
//check this
		trainingAngles = tData->GetAngle(currentAction, durations);
		
		if (isTransitioning)
		{
			transitionActions(currentAction, mixModel, tData);
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				//std::cout << outputAngles[i] << " , ";
				angles[i] = outputAngles[i];
				Tangles[i] = trainingAngles[i];

			}
			//std::cout << "\n";


			//increments duration 
			float temp = durations[currentAction] + timeIncrementFactor; 
			durations[currentAction] = temp;
		}

		double* motorPositions = ForwardKinematics::getXYZ(angles);
		double* trainingPositions = ForwardKinematics::getXYZ(Tangles);
		for (int i = 0; i < 3; i++)
		{
//Print training positions here
			//std::cout << motorPositions[i] << ", ";
		}
		std::cout << "\n";

		edxl.setTorqueMult(idarr, torque, 6);

		//can swap out angles for Tangles
		edxl.setAngleMult(idarr, angles, 6);



		if (durations[currentAction] >= 1)
		{
			durations[currentAction] = 1;
			currentAction++;
			
			timeIncrementFactor = 1 / (tData->getActionSize(currentAction) * 2);



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


