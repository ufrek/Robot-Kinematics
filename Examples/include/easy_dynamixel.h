/*
/////////////////////////
// Ferris Whitney 2022 //
/////////////////////////
// easy_dynamixel.h /////
///////////////////////////////////////////////////////////////////////////////////////////
// An easy to use C++ library for use with the Dynamixel SDK and WidowX 200 Robot Arm!   //
// Provides user friendly functions to read and write values from the individual motors. //
///////////////////////////////////////////////////////////////////////////////////////////
*/

#pragma once
#ifndef EASY_DYNAMIXEL_H
#define EASY_DYNAMIXEL_H

class Easydxl {
	dynamixel::PortHandler *portHandler;
	dynamixel::PacketHandler *packetHandler;
	char *com;
	//int dxl_comm_result = 0;
	uint8_t dxl_error;

public:
	double returnDoubleArray[7];
	int returnIntArray[7];
	// Sets up the dynamixel library for use with the WidowX 200 Arm.
	// @param *com Pointer to the port assigned to the motor controller.
	// Ex: Windows: "COMn", Linux: "/dev/ttyUSBn", Mac: "/dev/tty.usbserial-n"
	Easydxl(char *com);

	// Turns and LED on or off depending on the input.
	// @param id Motor ID
	// @param value 0 for LED off, 1 for LED on
	void setLed(int id, int value);

	// Enables or Disables Torque for a specified motor.
	// Torque needs to be enabled in order to use setAngle()
	// @param id motor ID
	// @param value 0 for Torque Disable, 1 for Torque Enable.
	void setTorque(int id, int value);

	// Enables or Disables Torque for multiple motors.
	// Arrays need to be of identical element size.
	// @param id Pointer to Motor ID array.
	// @param value Pointer to value array.
	// @param arrlen amount of #s in id array.
	// 0 for Torque Disable, 1 for Torque Enable.
	// Ex:
	// Set Torque enable to Motor IDs 1, 2, 3 and disable for 4, 5:
	// int[] id = {1, 2, 3, 4, 5};
	// int[] value = {1, 1, 1, 0, 0};
	// int arrlen = 5;
	void setTorqueMult(int *id, int *value, int arrlen);

	// Sets a motor position to the specified angle provided.
	// @param id Motor ID
	// @param value Angle to set specified motor to.
	void setAngle(int id, double value);

	// Sets multiple motor positions to the specified angles provided.
	// Arrays need to be of identical element size.
	// Ex:
	// To set Motor IDs 1 and 3 to 45 and 65 degrees respectively:
	// int[] id = {1, 3}
	// float[] value = {45, 65}
	// int arrlen = 2;
	// @param *id Pointer to Motor ID array.
	// @param *value Pointer to Motor ID value array.
	// @param arrlen amount of #s in id array.
	void setAngleMult(int *id, double *value, int arrlen);

	// Returns angle for specified Motor ID.
	// @param id Motor ID.
	// @return Motor angle in degrees.
	double getAngle(int id);

	// Returns a pointer to an angle array given multiple Motor IDs.
	// Arrays need to be of identical element size.
	// @param *id Pointer to Motor ID array.
	// @param arrlen amount of #s in id array.
	// @return Pointer to returnDoubleArray[]
	double * getAngleMult(int *id, int arrlen);

	// Closes the port. Use at the end of program.
	void closePort();

	////////////////////////
	// Advanced Functions //
	////////////////////////

	// Returns position value for specified Motor ID.
	// @param id Motor ID.
	// @return Signed integer of motor position value.
	int getPosition(int id);

	// Returns a pointer to an position array given multiple Motor IDs.
	// Arrays need to be of identical element size.
	// @param *id Pointer to Motor ID array.
	// @param arrlen amount of #s in id array.
	// @return Pointer to returnIntArray[]
	int * getPositionMult(int *id, int arrlen);
	
	// Sets a motor position to the specified angle provided.
	// @param id Motor ID
	// @param value Position to set specified motor to.
	void setPosition(int id, uint32_t value);

	// Sets multiple motor positions to the specified position values provided.
	// Arrays need to be of identical element size.
	// Ex:
	// To set Motor IDs 1 and 3 to 2000 and 4000 respectively:
	// int[] id = {1, 3};
	// float[] value = {2000, 4000};
	// int arrlen = 2;
	// @param *id Pointer to Motor ID array.
	// @param *value Pointer to Motor ID value array.
	// @param arrlen amount of #s in id array.
	void setPositionMult(int *id, uint32_t *value, int arrlen);

	// Sets the specified motor id to a specific operating mode.
	// 1: Velocity Control Mode
	// 3: Position Control Mode
	// *4: Extended Position Control Mode <- setup() sets all motors to mode 4.
	// 16: PWM Control Mode
	// @param id Motor ID
	// @param mode Control Mode #
	void setMode(int id, int mode);

	// Sets the Acceleration of a Motor ID when rotating.
	// value: 0 - 32767 0 = Infinite Acceleration
	// value unit = 214.577 [rev/min2]
	// @param id Motor ID
	// @param value Motor Acceleration (0-32767)
	void setAcceleration(int id, int value);

	// Sets the maximum possible velocity of the profile.
	// Look at the Motor documentation for profile curve examples.
	// value: 0 - 32767 0 = Infinite Velocity
	// value unit = 0.229 [rev/min]
	// @param id Motor ID.
	// @param value Maximum velocity value. (0-1023)
	void setMaxVelocity(int id, int value);

	// Sets the velocity target for the Motor ID.
	// @param id Motor ID.
	// @param value Velocity target.
	void setVelocityTarget(int id, int value);

	// Returns current velocity of Motor ID.
	// @param id Motor ID.
	// @return Signed integer of current velocity.
	int getVelocity(int id);
};

#endif