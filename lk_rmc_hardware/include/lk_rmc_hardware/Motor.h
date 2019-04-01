#ifndef LK_MOTOR_H
#define LK_MOTOR_H

// wrapper class for CTRE's TalonSRX

#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
// #include "ctre/Phoenix.h"

#include <string>

using namespace ctre;
using namespace phoenix;

// contains all of the motor-specific info
class MotorInfo
{
public:
	enum MotorType
	{
		// are more descriptive names necessary?
		NULLMOTOR = -1,
		BASE_FL,		 // front left drive		(BAG w/ encoder)
		BASE_FR,		 // front right drive 	(BAG w/ encoder)
		BASE_BL,		 // back left drive			(BAG w/ encoder)
		BASE_BR,		 // back right drive		(BAG w/ encoder)
		DEPO,				 // deposition motor		(BAG w/ encoder)
		INTK_DRV,		 // intake drive				(CIM)
		INTK_LIFT_L, // intake left lift		(stepper)
		INTK_LIFT_R	// intake right lift		(stepper)
	};

	MotorType id;
	std::string name;
	int canId;
	bool hasEncoder;

public:
	MotorInfo(MotorType id);
	~MotorInfo(void);
	MotorType getType(void);
	int getCanId(void);
	std::string typeToString(void);
};

class Motor : public motorcontrol::can::TalonSRX
{
private:
	MotorInfo info;

public:
	Motor(MotorInfo info);
	~Motor(void);
	MotorInfo getInfo(void);
};

#endif
