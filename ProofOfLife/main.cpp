#define Phoenix_No_WPI

#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "ctre/phoenix/motorcontrol/ControlMode.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"

#include <string>
#include <iostream>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

TalonSRX backLeft(3), backRight(1), frontLeft(4), frontRight(2);

double cap(double n)
{
	if (n > 1)
		return 1;
	if (n < -1)
		return -1;
	return n;
}

void initDrive(void)
{
	// backLeft.SetInverted(true);
	backLeft.Follow(frontLeft);
	backRight.Follow(frontRight);
}

void drive(double fwd, double turn)
{
	double left = cap(fwd - turn), right = cap(fwd + turn);

	frontLeft.Set(ControlMode::PercentOutput, left);
	frontRight.Set(ControlMode::PercentOutput, right);
}

void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main(void)
{
	int fwd = 0, turn = 0;
	std::string canPort = "can0";
	int32_t error;

	if (error = ctre::phoenix::platform::can::SetCANInterface(canPort.c_str()))
	{
		std::cout << "CAN Initialization returned error code: " << error << "\n";
		return 0;
	}

	initDrive();

	std::cout << "input fwd and turn\n";

	while (true)
	{
		// scanf("%d %d\n", &fwd, &turn);

		// if (fwd == 5 && turn == 5)
		// 	break;

		// drive(fwd, turn);

		drive(0, 0);

		ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);

		sleepApp(20);

		break;
	}

	drive(0, 0);

	return 0;
}
