# Robot-Kinematics
![widowX200](https://raw.githubusercontent.com/CoachGeorgia/Robot-Kinematics/main/docs/images/RoboticArmWidowX200.PNG)
## Robot Kinematics & Machine Learning 
Robotic Arm software for Kinematics and Learning. 
Code examples modified from DynamixelSDK and easyDyamixel.


![widowX200 In Motion](https://raw.githubusercontent.com/CoachGeorgia/Robot-Kinematics/main/docs/images/Model%20Recording_4.gif)

## Training ##
[![Robot Arm Plays Chess](https://github.com/CoachGeorgia/Robot-Kinematics/blob/main/docs/images/RoboticArmChessPlayBack.PNG)](https://youtu.be/VSL-L6GrsGc "Robot Arm Plays Chess")
## Hardware ##
### Robotic Arm 
[WidowX200]( https://www.trossenrobotics.com/widowx-200-robot-arm.aspx)

### Robotic Arm Firmware 
[Dynamixel Communication Protocol 2.0]( https://emanual.robotis.com/docs/en/dxl/protocol2/#instruction-packet)

## Software ##
### OS:
Windows 10
### IDE:
Visual Studio

# Examples

## Programming by Demonstration ##
This project records a robot arm's actions in the record project folder and exports it to a text file. You can then playback those recorded actions in the playback project folder.

### Record:
Record.exe or Record.sln will record the angles of a connected robot arm and export the poositions into a file called "positions.txt."

In the folder "example_record" you will find the files necessary for recording a robot arm's actions. Open up the record.sln file in visual studio and make sure your the com value is set in the source.cpp file to the correct serial port on your device before running. You can find the port number of your arm by downloading and opening up Dynamixel Wizard 2.0 and checking the options tab.

### Playback
Playback.exe takes a text file in the same directory, gets the motor angles from each line of the file, and sets the motor's angles to the retrieved values.
In other words, it plays back a recorded behavior

In the folder "example_playback" you will find the files necessary for recording a robot arm's actions.
// Note: running from the local windows debugger will not work. Build the playback application file and run that instead.
The application will be built in ../Programming by Demonstration/example_playback/x64/Release/playback.exe
//REQUIRED: You need a file called "positions.txt" in the same directory as the application file for it to run properly. (Or rename the target file in ode)
Each line in the text document must containr 6 comma separated values, one for each motor angle.

## Motion Primitives ##
In this project, we record several action behaviors and calculate Gaussian Mixture Models to fit change in angles over time for each motor. We then take these models and make the robot arm move based on these models. We have combined 3 different actions (cradle to home position, drawing a line, home position to cradle) and used interpolation bettween the end of one action and the beginnning of the next action. 

In the Motion Primitives Folder, there is a project Folder titled "Gaussian Mixture Model" that contains a python file to run Gaussian Mixture Model fitting to a provided csv file. In this example, we used the Record project from the Programming By Demonstration to record a training data set so that we can fit a Gaussian Mixture Model to it.

We then copy the output of the Gaussian Mixture Model Fitting into the Motion Primitive project and use a loop from 0 to 1 with a small incrementing step to iterate over each of the 6 Gaussian Mixture Models and update the output angles of these models to each motor. To put things simply, we are playing back recorded actions by using a calculated model of these actions.

### Training by Demo:
![Draw Line](https://raw.githubusercontent.com/CoachGeorgia/Robot-Kinematics/main/docs/images/Training%20Recording_2.gif)

### Motor Data:
![widowX200](https://github.com/CoachGeorgia/Robot-Kinematics/blob/main/Examples/MotionPrimitives%20(FK)/DrawLine%20Visualization.png?raw=true)

## Forward Kinematics ##
We calculated Denavit Hartenburg values for each of the motors and calculated the position of the end effector of the robot arm in 3D space. In this project, we combined a motion primitve from the previous project with Forward Kinematics so we can compare the calculated position with the position from the training data.

We have a folder titled "Motion Primited Refactored" which contains a completely refactored version of MOtion Primitives. At this point in time, we have not completed the refactored implementation but it would allow for real time comparison between the calculated 3D space postitions of rht training data and the calculated positions from our fit Gaussian Mixture Models for a task.

## Inverse Kinematics ##
NOT FUNCTIONING: We calculate a Jacobian from the Denavit Hartenburg parameters we calculated in the previous project. We have a goal end effector position and rotaation and use the Jacobian to calculate the angles required to move the robot arm to the desired position.

## Download & Installation (Windows) ##
### Dynamixel Install

Download the Dynamixel Wizard 2.0
Select the version for your specific platform:
[Dynamixel Wizard 2.0](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_wizard2)

Install and Open the Dynamixel Wizard.
Click on the “Options” gear icon.

On the right side of Options select the Scan tab the settings should be:
The Scan tab the settings should be:
~Protocol to Scan:  Protocol 2.0
~Select Port to Scan: Select All
~Select Baudrate to Scan: 1,000,000
~Set ID range to Scan. Start: 0 End: 7
Click OK

Now Click on Scan.

You should now see the motors of the Robot Arm show up in the Dynamixel Wizard.


Install Visual Studio
Download Visual Studio 2022 Community from Microsoft’s website.
[Visual Studio 2022](https://visualstudio.microsoft.com/vs/)

Run the VS installer.

Check to install the “Desktop development with C++”
Click “Install” in the bottom right corner.
This installation will take around 10 minutes.

Install Dynamixel / Easy Dynamixel
Download the github source code from the github repository.
[Dynamixel / Easy Dynamixel](https://github.com/prof-eaton/dynamixel)

If necessary, Extract the downloaded zip file.


## Getting Started ##
### Example_Read: Reads Motor output and displays in terminal. 
Open up the example_read folder in the file explorer.
Open example_read.sln file with MS Visual Studio.

On the right side of Visual Studio in the Solution Explorer, you should see a “Source Files” folder.
Double click on source.cpp file to open it.

In source.cpp replace:
COM3 with  the Dynamixel Wizard reported as the port. 
On Windows, its COM followed by a number.

Ensure the two drop down menus on the top say “Release” and “x64”. If not, change them.

In the Solution Explorer on the right side of Visual Studio: 
Right-click on “Solution ‘read’ (1 of 1 project)” then Select “Build Solution”.


Now locate your newly built Read Executable file in your file explorer. 

The compiled exe should be in the “example_read\x64\Release” folder.

The file should be named “read.exe”


## Links ##
[WidowX200]( https://www.trossenrobotics.com/widowx-200-robot-arm.aspx)

[Interbotix]( http://support.interbotix.com/html/specifications/wx200.html)

[DynamixelSDK](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/#concept)

[EasyDynamixel]( https://github.com/prof-eaton/dynamixel)

[Dynamixel Communication Protocol 2.0]( https://emanual.robotis.com/docs/en/dxl/protocol2/#instruction-packet)

[Eigen C++ Library](https://eigen.tuxfamily.org)
