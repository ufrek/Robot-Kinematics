# Robot-Kinematics
![widowX200](https://raw.githubusercontent.com/CoachGeorgia/Robot-Kinematics/main/docs/images/RoboticArmWidowX200.PNG)
## Robot Kinematics & Machine Learning 
Robotic Arm software for Kinematics and Learning. 
Code examples modified from DynamixelSDK and easyDyamixel.


![widowX200 In Motion](https://raw.githubusercontent.com/CoachGeorgia/Robot-Kinematics/main/docs/images/Model%20Recording_4.gif)


[![NVIDIA Robot Arm AI](https://github.com/CoachGeorgia/Robot-Kinematics/blob/main/docs/images/NVIDIA_Robot_Arm.PNG)](https://www.youtube.com/watch?v=-t-Pze6DNig "NVIDIA Robot Arm AI")
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

## Motion Primitives ##
### Training by Demo:
![Draw Line](https://raw.githubusercontent.com/CoachGeorgia/Robot-Kinematics/main/docs/images/Training%20Recording_2.gif)

### Motor Data:
![widowX200](https://github.com/CoachGeorgia/Robot-Kinematics/blob/main/Examples/MotionPrimitives%20(FK)/DrawLine%20Visualization.png?raw=true)

## Forward Kinematics ##

## Inverse Kinematics ##

## Download & Installation (Windows)##
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
