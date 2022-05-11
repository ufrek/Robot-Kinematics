# Programming by Demonstration:

For this project we have two small programs: Record and Playback. In programming by demonstration, we first gain demonstration data for the robot to re-enact (i.e. record the motion). Our record program collects the angles of each of the joints many times per second and exports the entire collection of data into a file called “positions.txt” Next, we take the demonstration and have the robot arm play it back. Our playback program takes a text file and parses the angles back into floating number values which are then sent to the robot arm as orders to move to that orientation. This happens many times per second to play back the action we just recorded.


### How To Run: ##
### To record:  
	1: Open the example_record folder.

	2: Open record.sln

	3: Open Dynamixel Wizard 2.0 and click on the options tab to check your serial com number 		     for the Dynamixel arm.

	4: Check to make sure the variable “com” (line 18) is matching your Dynamixel Arm. Our value 	    was “COM14.”

	5: Build the solution and run it.

	6: Move the arm however way you want and press the “Q” key when you are done.

	7: Navigate to ../example_record/program to find your “positions.txt” file.

### To Play Back:
	1: Open the example_playback folder:

	2: Open playback,sln

	3: Open Dynamixel Wizard 2.0 and click on the options tab to check your serial com number 		     for the Dynamixel arm.

	4: Check to make sure the variable “com” (line 18) is matching your Dynamixel Arm. Our value 	    was “COM14.”

	5: Navigate to Build in the top menu and select rebuild playback

	6: Navigate in your file explorer to ../example_playback/x64/Release and drag your       	 		    positions.txt file form the record process here. Replace the current existing file if you must.

	7: Double-click on the playback application and the program will make the robot arm re-enact 		    the recorded actions.


## Demonstration of the playback of some arm wriggling: ##
[![Programming By Demonstration](https://img.youtube.com/vi/8cN5FqJM9ko/0.jpg)](https://www.youtube.com/watch?v=8cN5FqJM9ko)

