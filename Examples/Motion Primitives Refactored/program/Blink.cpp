#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"



char cox[6] = "COM11";

int blink() {
	Easydxl edxl(cox);
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds
	int currentLight = 0;
	int toggle[] = { 0,0,0,0,0,0,0 };

	while (1) 
	{
		currentLight = currentLight % 7;
		if (toggle[currentLight] == 0)
		{
			toggle[currentLight] = 1;
			edxl.setLed(currentLight, toggle[currentLight]);

		}
			
		else
		{
			toggle[currentLight] = 0;

			edxl.setLed(currentLight, toggle[currentLight]);
		}
			

		currentLight++;

		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			edxl.closePort();
			break;
		}
		sleep_for(seconds(1));

	}

	return 0;
}




// Turns and LED on or off depending on the input.
// @param id Motor ID
// @param value 0 for LED off, 1 for LED on
