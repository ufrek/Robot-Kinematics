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
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[6] = "COM13";

//blink logic
int currentLight = 0;
int toggle[] = { 0,0,0,0,0,0,0 };

double safeIncrement = .001f;
double pie = 3.1415926535897932384626433;

int main() 
{
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	
	while (1) 
	{
			

		
		//double* currentAngles = edxl.getAngleMult(idarr, 6);
		double* currentAngles = angles;
		double* currentPosition = ForwardKinematics::getXYZ(currentAngles);
		double targetAngles[] = {182.248000, 180.048000, 82.280000, 188.760000, 175.296000, 185.856000};
		double* targetPosition = ForwardKinematics::getXYZ(targetAngles);
		std::vector<double> deltaPosition;
		std::vector<double> curPos; //convert double* to vector
		//get change in positions
		for (int i = 0; i < 3; i++)
		{
			curPos.push_back(currentPosition[i]);
			deltaPosition.push_back(targetPosition[i] - currentPosition[i]);
		}

		double currentPitch =0;
		double targetPitch = 0;
		for (int i = 0; i < 3; i++)
		{
			currentPitch = currentPitch + currentAngles[i] - 180;
			targetPitch = targetPitch + targetAngles[i] - 180;
		}

		deltaPosition.push_back(((targetPitch - currentPitch) * (pie / 180)));
		double magnitude = sqrt(pow(deltaPosition[0], 2) + pow(deltaPosition[1], 2) + pow(deltaPosition[2], 2));

		//deltaPositions as a unit vector
		for (int i = 0; i < 3; i++)
		{
			deltaPosition[i] = deltaPosition[i] / magnitude;
			
			//multiply by safe increment
			deltaPosition[i] = deltaPosition[i] * safeIncrement;
		}

		
		
		//double deltaAngle = Jacobian::getChangeInAngles(curPos, deltaPosition);
		Eigen::MatrixXd deltaAngles = Jacobian::getChangeInAngles(curPos, deltaPosition);
		double newAngles[] = { 0, 0, 0, 0, 0, 0 };
	
		//std::cout << "Delta Angles = " << deltaAngles << "\nNew Angles: ";
		if (deltaAngles.coeff(0,0) != -999) // nice lmao
		{
			for (int i = 0; i < 6; i++)
			{
				newAngles[i] = (currentAngles[i] + (deltaAngles.coeff(i, 0) * (180/pie)));
				std::cout << newAngles[i] << ", ";
			}
			std::cout << "\n";
		}
		else
		{
			std::cout << "invalid Delta Angle";
			//break;
		}
			
		
		
		edxl.setTorqueMult(idarr, torque, 6);
		edxl.setAngleMult(idarr, newAngles, 6);
		



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


