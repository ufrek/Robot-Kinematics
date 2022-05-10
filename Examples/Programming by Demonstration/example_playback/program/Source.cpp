#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <ios>
#include < Windows.h >

// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };
double inputangles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };
// 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[6] = "COM14";

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	//std::ifstream inFile("positions.txt");
	std::ifstream indata;
	indata.open("positions.txt");
	
	for(int i = 0; i < 1000; i++){
		int j = 0;
		char row[100];
		indata.getline(row, 100, '\n');
		std::string var = "";
		for (char x : row) {
			if (x == ',') {
				inputangles[j] = std::stod(var);
				j++;
				var = "";
			}
			else {
				var = var + x;
			}
		}
			printf("%f %f %f %f %f %f \n", inputangles[0], inputangles[1], inputangles[2], inputangles[3], inputangles[4], inputangles[5]);
	
		edxl.setAngleMult(idarr, inputangles, 6);
		Sleep(5);
	}
	indata.close();
	edxl.closePort();
	return 0;
}
