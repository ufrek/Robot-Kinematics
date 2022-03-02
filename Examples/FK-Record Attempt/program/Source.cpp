#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"
#include <iostream>
#include <fstream>
using namespace std::chrono;

// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 0, 0, 0, 0, 0, 0 };
char com[6] = "COM11";

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	std::ofstream file;
	file.open("positionsDraw.txt");
	auto start = std::chrono::system_clock::now();

	while (1)
	{
		double* d;
		d = edxl.getAngleMult(idarr, 6);
		file << d[0] << "," << d[1] << "," << d[2] << "," << d[3] << "," << d[4] << "," << d[5] << "\n";
		printf("%f, %f, %f, %f, %f, %f \n", d[0], d[1], d[2], d[3], d[4], d[5]);



		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}

		/*
		double l2 = 213.25;
		double l3 = 200;
		double l4 = 200;
		double l5 = 65;
		double l6 = 66.05;

		double d1 = 50;

		double pos[3][1];
		for (int i = 0; i < 3; i++)
		{
			pos[i][0] = 0;
		}
		
		double joint1[3][1];
		joint1[0][0] = (l2 * cos(d[1])) + (d1 * cos(d[1]));
		joint1[1][0] = (l2 * sin(d[1])) + (d1 * cos(d[1]));
		joint1[2][0] = 0;


		double joint2[3][1];
		joint2[0][0] = l3 * cos(d[1] + d[2]);
		joint2[1][0] = l3 * sin(d[1] + d[2]);
		joint2[2][0] = 0;


		double joint3[3][1];
		joint3[0][0] = l4 * cos(d[1] + d[2] + d[3]);
		joint3[1][0] = l4 * sin(d[1] + d[2] + d[3]);
		joint3[2][0] = 0;

		double joint4[3][1];
		joint3[0][0] = l5 * cos(d[1] + d[2] + d[3] + d[4]);
		joint3[1][0] = l5 * sin(d[1] + d[2] + d[3] + d[4]);
		joint3[2][0] = 0;
		*/

		double l2 = 113.25;
		double l3 = 0;
		double l4 = 0;
		double l5 = 200;
		double l6 = 174.15;
	

		double d4 = 50;
		double d5 = 200;

		double pos[3][1];
		for (int i = 0; i < 3; i++)
		{
			pos[i][0] = 0;
		}



		double joint0[3][1];
		joint0[0][0] = 0;
		joint0[1][0] = 113.25;
		joint0[2][0] = 0;

		double joint1[3][1];
		joint1[0][0] = (l2 * cos(d[1]));
		joint1[1][0] = (l2 * sin(d[1]));
		joint1[2][0] = 0;


		double joint2[3][1];
		joint2[0][0] = l3 * cos(d[1] + d[2]);
		joint2[1][0] = l3 * sin(d[1] + d[2]) + 200;
		joint2[2][0] = 0;


		double joint3[3][1];
		joint3[0][0] = l4 * cos(d[1] + d[2] + d[3]) + (50 * cos(3.14159));
		joint3[1][0] = l4 * sin(d[1] + d[2] + d[3])  + (50 * sin(3.14159));
		joint3[2][0] = 0;

		double joint4[3][1];
		joint3[0][0] = l5 * cos(d[1] + d[2] + d[3] + d[4]);
		joint3[1][0] = l5 * sin(d[1] + d[2] + d[3] + d[4]);
		joint3[2][0] = 0;

		double posx = joint0[0][0] + joint1[0][0] + joint2[0][0] + joint3[0][0] + joint4[0][0];
		double posy = joint0[0][0] + joint1[1][0] + joint2[1][0] + joint3[1][0] + joint4[1][0];

		std::cout << "Pos x: " << posx << "\nPos y:" << posy << "\n";
		
		Sleep(500);


	}

	



	/*
	
	for (int i = 0; i < 1000; i++) {
		double* d;
		d = edxl.getAngleMult(idarr, 6);
		file << d[0] << "," << d[1] << "," << d[2] << "," << d[3] << "," << d[4] << "," << d[5] << "\n";
		printf("%f, %f, %f, %f, %f, %f \n", d[0], d[1], d[2], d[3], d[4], d[5]);
	}*/
	file.close();
	auto end = std::chrono::system_clock::now();

	edxl.closePort();
	return 0;
}
