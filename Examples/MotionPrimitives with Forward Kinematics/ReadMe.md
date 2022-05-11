# Motion Primitives With Forward Kinematics 

In this project wwe add upon the motion primitives project and add in Forward Kinematics. We calculated the Denavit Hartenburg parameters for each motor in the robot arm and used these to calculate the position of the arm's end effector in 3D space based on the angles of the motors. We have two project folders so that we can compare the calculated positions of our motion primitives in comparison to our training Data set.
 
 ##Contents:
 In this project folder, you will see 2 Project folders: "Forward Kinematics" and "Forward Kinematics - Training Data/" The first folder uses Forward Kinematics with our motion primitive while the latter forlder calculates positions of the end effector with our training data set.
 
 There are 3 tasks that the motion primitive and training set cover: "Cradle to Home Position," "Drawing a Line," and "Home Position to Cradle." There are 3 visualization images in the "Motion Primitive Visualizations" folder that display the angles of the motors over time of each action. 
 
 ## Demonstration of the playback of some arm wriggling: ##
[![Programming By Demonstration](https://img.youtube.com/vi/ID7LfaNjIwk/0.jpg)](https://www.youtube.com/watch?v=ID7LfaNjIwk)
 
## How To Run: ##
### To record: 
	1: Open either the "Forward Kinematics" or "Forward Kinematics - Training Data" Folders.

	2: Open either "forwardKinematics.sln" or "fkTrainingData.sln"

	3: Open Dynamixel Wizard 2.0 and click on the options tab to check your serial com number for the Dynamixel arm.

	4: Check to make sure the variable “com” (line 18) is matching your Dynamixel Arm. Our value was “COM14.”

	5: Build the program.
  
  6:Navigate to ../x64/Release and run the "Forward Kinematics" or "FKTraining" applications.

	6: The numbers that are scrolling across the screen are the end effector distances from the ground underneath the base motor in millimeters on the X, Y, and Z planes.

## Code Breakdown ##
 At the top, we use the Eigen library to build our matrix from the calculated Denavit Hartenburg parameters. Following this we have our Forward Kinematic and MOtion Primitive Functions and in the main loop, we increment over a normalized time interval of 0 to 1 to play through all 3 actions and calculate the 3D positions of the end effector in real time.

