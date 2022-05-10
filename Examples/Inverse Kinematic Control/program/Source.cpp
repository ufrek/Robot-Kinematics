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
#include "Jacobian.h"
#include <iostream>
using namespace std::chrono;
using namespace std::this_thread;

// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.576, 71.192, 277.816, 211.464, 195.624, 129.184 };

// 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[6] = "COM13";

//blink logic
int currentLight = 0;
int toggle[] = { 0,0,0,0,0,0,0 };

double safeIncrement = .01f; //was .001
double pie = 3.1415926535897932384626433;

int main() 
{
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);

	//double* currentAngles = edxl.getAngleMult(idarr, 6);
	double* currentAngles = angles;
	double* currentPosition = ForwardKinematics::getXYZ(currentAngles);
	double targetAngles[] = { 180.3, 25, 272.27, 226.33, 189.16, 129.4 };
	double* targetPosition = ForwardKinematics::getXYZ(targetAngles);
	
	
	while (1) 
	{
			
		std::vector<double> deltaPosition;
		
	
	
		//get change in positions
		for (int i = 0; i < 3; i++)
		{
			deltaPosition.push_back(targetPosition[i] - currentPosition[i]);
		}

		double currentPitch =-180; //might be 0 instead
		double targetPitch = 0;
		for (int i = 1; i < 4; i++)
		{
			currentPitch = currentPitch + currentAngles[i] - 180;
			targetPitch = targetPitch + targetAngles[i] - 180;
		}

		//add pitch
		deltaPosition.push_back(((targetPitch - currentPitch) * (pie / 180)));
		double magnitude = sqrt(pow(deltaPosition[0], 2) + pow(deltaPosition[1], 2) + pow(deltaPosition[2], 2) + pow(deltaPosition[3], 2));

		//deltaPositions as a unit vector
		for (int i = 0; i < 4; i++)
		{
			deltaPosition[i] = deltaPosition[i] / magnitude;
			
			//multiply by safe increment
			deltaPosition[i] = deltaPosition[i] * safeIncrement;
		}

		
		
		//double deltaAngle = Jacobian::getChangeInAngles(curPos, deltaPosition);
		Eigen::MatrixXd deltaAngles = Jacobian::getChangeInAngles(currentAngles, deltaPosition);
		
	
		//std::cout << "Delta Angles = " << deltaAngles << "\nNew Angles: ";
		if (deltaAngles.coeff(0,0) != -999) // nice lmao
		{
			for (int i = 1; i < 4; i++)
			{
				currentAngles[i] = (currentAngles[i] + (deltaAngles.coeff(i, 0) * (180/pie)));
				std::cout << currentAngles[i] << ", ";
			}
			std::cout << "\n";
		}
		else
		{
			std::cout << "invalid Delta Angle";
			//break;
		}
			
		
		
		edxl.setTorqueMult(idarr, torque, 6);
		edxl.setAngleMult(idarr, currentAngles, 6);
		



		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}
		sleep_for(nanoseconds(10));

		

	}
	edxl.closePort();
	
	return 0;
}


