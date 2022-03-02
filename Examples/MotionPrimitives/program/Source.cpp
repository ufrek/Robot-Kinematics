#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <Windows.h>
#include <time.h>
#include <ctime>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"
#include <iostream>
#include <fstream>
#include <thread>
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;


// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[6] = "COM11";

int main()
{
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	std::ofstream file;
	file.open("angles.txt");

	//get current time
	time_t start_time;

	auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	//alter this to slow it down? I think
	float timeFactor = .00015f;
	double angles[] = { 0, 0, 0, 0, 0, 0 };

	
	int totalRuns = 0;
	while (1)
	{
		auto currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		double duration = (currentTime - startTime);
		//cout << duration;
		//CHECK THIS		
		if (duration * timeFactor  >= 280)
			break;
		//duration *= timeFactor;
		//cout << duration << "\n";

		

		// a / (1.0 + exp(x - d))) + b 
		//x = time


		angles[0] = -0.08847149061058925 / (1.0 + exp(-5861.2986553395 * (duration - 0.4463415613754276))) + 180.5930084033614;
		angles[1] = 113.92094070939986 / (1.0 + exp(-36.80468057067554 * (duration - 0.36783185167165916))) + 70.7262474226124;
		angles[2] = -((100.16158050571426 / (1.0 + exp(-29.623944320336754 * (duration - 0.6227530305348828))) + 177.42072336886352) - .5) + .5 ;
		angles[3] = 214 - 99.7 * duration + 78.4 * duration * duration;
		angles[4] = 190 - 12.8 * duration + 11.9 * duration * duration;
		

		

		if (angles[2] > 277.816)
			angles[2] = 277.816;
		else if (angles[2] < 177.32)
			angles[2] = 177.32;
		

		if (angles[3] > 212.256)
			angles[3] = 212.256;
		else if(angles[3] < 170)
			angles[3] = 170;

		if (angles[4] < 0)
			angles[4] = 0;
		else if (angles[4] > 350)
			angles[4] = 350;

		/*if (angles[4] < 187.792)
			angles[4] = 187.792;
		else if (angles[4] > 195.624)
			angles[4] = 195.624;
			*/
		for (int i = 0; i < 6; i++)
		{
			
			//cout << "angle " << i << ": " << angles[i] << "\n";
		}

		edxl.setTorqueMult(idarr, torque, 6);
		edxl.setAngleMult(idarr, angles, 6);
		
		cout << angles[3] << "\n";
		file << angles[0] << "," << angles[1] << "," << angles[2] << "," << angles[3] << "," << angles[4] << "," << angles[5] << "\n";
		totalRuns++;
		if (totalRuns == 269)
		{
			for (int i = 0; i < 6; i++)
			{
				
				//cout << "angle " << i << ": " << angles[i] << "\n";
			}
			//break;
		}
			
		if (GetKeyState('Q') & 0x8000)  //Check if high-order bit is set (1 << 15)
		{
			printf("Application Closed. You pressed Q.");
			edxl.closePort();
			break;
		}

	    sleep_for(10ns);


	}

	cout << "total runs: " << totalRuns;
		int close[] = { 0, 0, 0, 0, 0, 0 };
		edxl.setTorqueMult(idarr, close, 6);
		sleep_for(10ns);

		printf("Application Closed.");
		edxl.closePort();



	/*
	while (1)
	{
		double* d;
		d = edxl.getAngleMult(idarr, 6);
		file << d[0] << "," << d[1] << "," << d[2] << "," << d[3] << "," << d[4] << "," << d[5] << ",";
		printf("%f, %f, %f, %f, %f, %f \n", d[0], d[1], d[2], d[3], d[4], d[5]);



		
	}

	*/
	/*
	
	for (int i = 0; i < 1000; i++) {
		double* d;
		d = edxl.getAngleMult(idarr, 6);
		file << d[0] << "," << d[1] << "," << d[2] << "," << d[3] << "," << d[4] << "," << d[5] << "\n";
		printf("%f, %f, %f, %f, %f, %f \n", d[0], d[1], d[2], d[3], d[4], d[5]);
	}*/
	file.close();
	auto end = std::chrono::system_clock::now();

	//edxl.closePort();
	return 0;
}


