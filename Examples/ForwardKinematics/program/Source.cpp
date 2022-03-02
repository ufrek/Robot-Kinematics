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
#include <math.h> 
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


	double cradleToRestAngles[] = { 0, 0, 0, 0, 0, 0 };
	double drawLineAngles[] = { 0, 0, 0, 0, 0, 0 };
	double restToCradleAngles[] = { 0, 0, 0, 0, 0, 0 };
	double angles[] = { 0, 0, 0, 0, 0, 0 };

	int currentAction = 0;
	
	int totalRuns = 0;
	while (1)
	{
		auto currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		double duration = (currentTime - startTime);
		//cout << duration;
		//CHECK THIS		
//uncomment later		
		if (duration * timeFactor  >= 280)
			break;
		//duration *= timeFactor;
		//cout << duration << "\n";

		double* d;
		//d = edxl.getAngleMult(idarr, 6);
		for (int i = 0; i < 6; i++)
		{
			//angles[i] = d[i];
		}

		// a / (1.0 + exp(x - d))) + b 
		//x = time

		
		
	
				


		



	

		if (currentAction == 0)
		{
			angles[0] = -0.08847149061058925 / (1.0 + exp(-5861.2986553395 * (duration - 0.4463415613754276))) + 180.5930084033614;
			angles[1] = 113.92094070939986 / (1.0 + exp(-36.80468057067554 * (duration - 0.36783185167165916))) + 70.7262474226124;
			angles[2] = -((100.16158050571426 / (1.0 + exp(-29.623944320336754 * (duration - 0.6227530305348828))) + 177.42072336886352) - .5) + .5;
			angles[3] = 214 - 99.7 * duration + 78.4 * duration * duration;
			angles[4] = 190 - 12.8 * duration + 11.9 * duration * duration;




			if (angles[2] > 277.816)
				angles[2] = 277.816;
			else if (angles[2] < 177.32)
				angles[2] = 177.32;


			if (angles[3] > 212.256)
				angles[3] = 212.256;
			else if (angles[3] < 170)
				angles[3] = 170;

			if (angles[4] < 0)
				angles[4] = 0;
			else if (angles[4] > 350)
				angles[4] = 350;
		}
		else if(currentAction == 1)
		{
			angles[0] = (-15.196778970879052 * pow(duration, 14)) +
				(-5.663202825104264 * pow(duration, 13)) +
				(-7.911861808042175 * pow(duration, 12)) +
				(-3.5053454257120933 * pow(duration, 11)) +
				(-10.048697140685874 * pow(duration, 10)) +
				(-3.197996543439004 * pow(duration, 9)) +
				(-15.055391591741667 * pow(duration, 8)) +
				(10.72947878626806 * pow(duration, 7)) +
				(-4.187046941037764 * pow(duration, 6)) +
				(5.509427026936919 * pow(duration, 5)) +
				(-1.9940064665328237 * pow(duration, 4)) +
				(3.4813460053425587 * pow(duration, 3)) +
				(-1.2472581409176726 * pow(duration, 2)) +
				(-9.299173832309691 * pow(duration, 1)) +
				(196.12080242650953 * pow(duration, 0));


			angles[1] = (74.09456833397293 * pow(duration, 14)) +
				(-1.792242995232698 * pow(duration, 13)) +
				(66.76024847627694 * pow(duration, 12)) +
				(-16.984589174765617 * pow(duration, 11)) +
				(100.6365308990444 * pow(duration, 10)) +
				(29.03371387766905 * pow(duration, 9)) +
				(67.65910663739655 * pow(duration, 8)) +
				(46.004509260084646 * pow(duration, 7)) +
				(58.40707506327852 * pow(duration, 6)) +
				(52.08301689091602 * pow(duration, 5)) +
				(65.91054778593225 * pow(duration, 4)) +
				(37.07301206740236 * pow(duration, 3)) +
				(8.931833497012988 * pow(duration, 2)) +
				(64.45732459064293 * pow(duration, 1)) +
				(86.38105767679536 * pow(duration, 0));

			angles[2] = (-111.96067842495265 * pow(duration, 14)) +
				(-4.446402377465972 * pow(duration, 13)) +
				(-101.94303216445441 * pow(duration, 12)) +
				(-29.126070104687727 * pow(duration, 11)) +
				(-23.90435781705206 * pow(duration, 10)) +
				(-45.51226003647615 * pow(duration, 9)) +
				(-14.242273115330477 * pow(duration, 8)) +
				(-40.15501471505475 * pow(duration, 7)) +
				(-20.325943175154706 * pow(duration, 6)) +
				(-39.57297192545191 * pow(duration, 5)) +
				(-36.94482555828117 * pow(duration, 4)) +
				(-24.336266395313743 * pow(duration, 3)) +
				(-37.125287315310764 * pow(duration, 2)) +
				(-94.33677727363226 * pow(duration, 1)) +
				(332.031400217155 * pow(duration, 0));
			angles[3] = (52.11954328245571 * pow(duration, 14)) +
				(11.442846793998669 * pow(duration, 13)) +
				(44.45680407867796 * pow(duration, 12)) +
				(41.78379798018655 * pow(duration, 11)) +
				(-55.93018486834647 * pow(duration, 10)) +
				(13.125549292993853 * pow(duration, 9)) +
				(-31.080167706734215 * pow(duration, 8)) +
				(-5.774516574178534 * pow(duration, 7)) +
				(-17.840546050473606 * pow(duration, 6)) +
				(-14.05542953233062 * pow(duration, 5)) +
				(-18.676083599951824 * pow(duration, 4)) +
				(-1.1002834565996409 * pow(duration, 3)) +
				(42.37073539136537 * pow(duration, 2)) +
				(48.93332910587446 * pow(duration, 1)) +
				(108.29452296130245 * pow(duration, 0));
			angles[4] = (-0.19588572113343616 * pow(duration, 14)) +
				(-0.06358183190670275 * pow(duration, 13)) +
				(-0.1358022655691542 * pow(duration, 12)) +
				(0.04915599242124813 * pow(duration, 11)) +
				(-0.2855887437128075 * pow(duration, 10)) +
				(0.07731460729132777 * pow(duration, 9)) +
				(-0.3230189720961931 * pow(duration, 8)) +
				(0.15670231619240838 * pow(duration, 7)) +
				(-0.461110571377489 * pow(duration, 6)) +
				(0.38815300569854116 * pow(duration, 5)) +
				(-0.8872823811910848 * pow(duration, 4)) +
				(1.1855092125156261 * pow(duration, 3)) +
				(-0.7717503200631555 * pow(duration, 2)) +
				(0.29010378557538274 * pow(duration, 1)) +
				(179.2459650286285 * pow(duration, 0));
		}
		else if (currentAction == 2)
		{

		}

		
		
		/* //cradle to rest
		angles[0] = -0.08847149061058925 / (1.0 + exp(-5861.2986553395 * (duration - 0.4463415613754276))) + 180.5930084033614;
		angles[1] = 113.92094070939986 / (1.0 + exp(-36.80468057067554 * (duration - 0.36783185167165916))) + 70.7262474226124;
		angles[2] = -((100.16158050571426 / (1.0 + exp(-29.623944320336754 * (duration - 0.6227530305348828))) + 177.42072336886352) - .5) + .5 ;
		angles[3] = 214 - 99.7 * duration + 78.4 * duration * duration;
		angles[4] = 190 - 12.8 * duration + 11.9 * duration * duration;
		*/

		/*

		if (angles[2] > 277.816)
			angles[2] = 277.816;
		else if (angles[2] < 177.32)
			angles[2] = 177.32;
		

		if (angles[3] > 212.256)
			angles[3] = 212.256;
		else if(angles[3] < 170)
			angles[3] = 170;
		*/
		/*if (angles[4] < 0)
			angles[4] = 0;
		else if (angles[4] > 350)
			angles[4] = 350;
			*/
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
		
		cout << angles[2] << "\n";
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

		if (duration > .99)    //check for accuracy of this
		{


			if (currentAction == 0)
				startTime = currentTime;
			//else if (duration > 1)
				//duration = 1;

			currentAction++;

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


