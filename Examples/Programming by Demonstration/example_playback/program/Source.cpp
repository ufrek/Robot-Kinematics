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

///Playback: 
// Note: running from the local windows debugger will not work. Build the playback application file and run that instead.
//The application will be built in ../Programming by Demonstration/example_playback/x64/Release/playback.exe
//REQUIRED: You need a file called "positions.txt" in the same directory as the application file for it to run properly. (Or rename the target file in ode)
//Each line in the text document must containr 6 comma separated values, one for each motor angle

//This program takes a text file in the same directory, gets the motor angles from each line of the file, and sets the motor's angles to the retrieved values.
//I.E. it plays back a recorded behavior

// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };
double inputangles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };
//  setting toruque values to 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[6] = "COM14";

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	//std::ifstream inFile("positions.txt");
	std::ifstream indata;
	indata.open("positions.txt"); //change targe file name here
	

	//for each line, get the motor angle values from file
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
	
		//set values to motor
		edxl.setAngleMult(idarr, inputangles, 6);
		Sleep(5);
	}
	indata.close();
	edxl.closePort();
	return 0;
}
