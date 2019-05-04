#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <unistd.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

/* make some talons for drive train */

// void initDrive()
// {
// 	/* both talons should blink green when driving forward */
// 	talRght.SetInverted(true);
// }

void drive(TalonSRX *talLeft, TalonSRX *talRight, double fwd, double turn)
{
	double left = fwd - turn;
	double rght = fwd + turn; /* positive turn means turn robot LEFT */

	talLeft->Set(ControlMode::PercentOutput, left);
	talRght->Set(ControlMode::PercentOutput, rght);
}
/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main()
{
	/* don't bother prompting, just use can0 */
	//std::cout << "Please input the name of your can interface: ";
	std::string interface;
	//std::cin >> interface;
	interface = "can0";
	ctre::phoenix::platform::can::SetCANInterface(interface.c_str());

	// TalonSRX talLeft(0);
	// TalonSRX talRight(1);

	while (true)
	{

		/* yield for a bit */
		sleepApp(20);

		ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);

		/* we've left the loop, likely due to gamepad disconnect */
		// drive(&talLeft, &talRight, 0, 0);
	}

	return 0;
}
