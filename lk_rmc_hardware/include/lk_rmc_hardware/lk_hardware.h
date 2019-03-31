#ifndef LK_HARDWARE_H
#define LK_HARDWARE_H

// Robot class which provides direct communication to robot hardware devices

#include <lk_rmc_hardware/Motor.h>

#include "ctre/phoenix/platform/Platform.h"
// #include "ctre/Phoenix.h"

// Robot class which contains all of the hardware devices connected
// to the robot (motors, sensors, etc.)
class Robot
{
private:
	std::vector<Motor *> motors;
	// IMU imu;
	// Battery battery;
	int numMotors;
	bool baseReady;
	bool depoReady;
	bool intakeReady;
	bool motorReady[8];

public:
	Robot(void);
	~Robot(void);
	int getNumMotors(void);
	Motor *getMotor(MotorType id);
	bool initMotor(MotorType id);
	void stopAllMotors(void);
	void initBase(void);
	void initDepo(void);
	void initIntake(void);
	int32_t initCANInterface(void);
	// IMU getIMU(void);
	// Battery getBattery(void);
};
