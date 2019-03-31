#ifndef LK_MOTOR_H
#define LK_MOTOR_H

// wrapper class for CTRE's TalonSRX

#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
// #include "ctre/Phoenix.h"

#include <string>

using namespace ctre;
using namespace phoenix;

// contains all of the info about a motor
class MotorInfo
{
	enum MotorType
	{
		// are more descriptive names necessary? (VSCode is screwing w indents)
		BASE_FL = 0,	 // front left drive		(BAG w/ encoder)
		BASE_FR = 1,	 // front right drive 	(BAG w/ encoder)
		BASE_BL = 2,	 // back left drive		(BAG w/ encoder)
		BASE_BR = 3,	 // back right drive		(BAG w/ encoder)
		DEPO = 4,		 // deposition motor		(BAG w/ encoder)
		INTK_DRV = 5,	// intake drive			(CIM)
		INTK_LIFT_L = 6, // intake left lift		(stepper)
		INTK_LIFT_R = 7, // intake right lift	(stepper)
		NULLMOTOR = -1
	};

	MotorType id;
	string name;
	int canId;
	bool hasEncoder;

  public:
	MotorInfo(MotorType id);
	~MotorInfo(void);
	MotorType getType(void);
	int getCanId(void);
	std::string typeToString(void);

}

class Motor : public motorcontrol::can::TalonSRX
{
  private:
	MotorInfo info;

  public:
	Motor(MotorInfo info); // TODO: define if construction means motor initialization
	~Motor(void);
	MotorInfo getInfo(void);
};

#endif
