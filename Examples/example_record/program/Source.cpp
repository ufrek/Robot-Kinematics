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
char com[6] = "COM12";

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	std::ofstream file;
	file.open("positions.txt");
	auto start = std::chrono::system_clock::now();

	while (1)
	{
		double* d;
		d = edxl.getAngleMult(idarr, 6);
		file << d[0] << "," << d[1] << "," << d[2] << "," << d[3] << "," << d[4] << "," << d[5] << ",";
		printf("%f, %f, %f, %f, %f, %f \n", d[0], d[1], d[2], d[3], d[4], d[5]);



		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}
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
