// This is an attempt at the hardware interface

#include <lk_rmc_hardware/lk_hardware.h>
#include "ros/ros.h"

using namespace hardware_interface;

// this notation "::" means extends
class RobotHW : public hardware_interface::RobotHW, public hardware_interface::HardwareInterface
{
	public: Robot()
	{

	//  this is if we were to put it all into a method

	//	Robot lunarBot();
	//	lunarBot.initBase();

	//	if(lunarBot.baseReady())
	//		registerBase(A,B);



		// connecting and registering the joint state interface
		// ideally write all of this in a method
		JointStateHandle state_handle_a("BASE_FL", &pos[0], &vel[0], &eff[0]);
		jnt_state_interface.registerHandle(state_handle_a);

		JointStateHandle state_handle_b("BASE_FR", &pos[1], &vel[1], &eff[1]);
		jnt_state_interface.registerHandle(state_handle_b);

		JointStateHandle state_handle_c("BASE_BL", &pos[2], &vel[2], &eff[2]);
		jnt_state_interface.registerHandle(state_handle_c);

		JointStateHandle state_handle_d("BASE_BR", &pos[3], &vel[3], &eff[3]);
		jnt_state_interface.registerHandle(state_handle_d);

		JointStateHandle state_handle_e("DEPO", &pos[4], &vel[4], &eff[4]);
		jnt_state_interface.registerHandle(state_handle_e);

		JointStateHandle state_handle_f("INTK_DRV", &pos[5], &vel[5], &eff[5]);
		jnt_state_interface.registerHandle(state_handle_f);


		// should these have the same position, velocity, eff?
		JointStateHandle state_handle_g("INTK_LIFT_L", &pos[6], &vel[6], &eff[6]);
		jnt_state_interface.registerHandle(state_handle_g);

		JointStateHandle state_handle_h("INTK_LIFT_R", &pos[7], &vel[7], &eff[7]);
		jnt_state_interface.registerHandle(state_handle_h);



		registerInterface(&jnt_state_interface);

		
		// connecting and registering the joint position interface
		JointHandle pos_handle_a(jnt_state_interface.getHandle("BASE_FL"), &cmd[0]);
		jnt_pos_interface.registerHandle(pos_handle_a);

		JointHandle pos_handle_b(jnt_state_interface.getHandle("BASE_FR"), &cmd[1]);
		jnt_pos_interface.registerHandle(pos_handle_b);

		JointHandle pos_handle_c(jnt_state_interface.getHandle("BASE_BL"), &cmd[2]);
		jnt_pos_interface.registerHandle(pos_handle_c);

		JointHandle pos_handle_d(jnt_state_interface.getHandle("BASE_BR"), &cmd[3]);
		jnt_pos_interface.registerHandle(pos_handle_d);

		JointHandle pos_handle_e(jnt_state_interface.getHandle("DEPO"), &cmd[4]);
		jnt_pos_interface.registerHandle(pos_handle_e);

		JointHandle pos_handle_f(jnt_state_interface.getHandle("INTK_DRV"), &cmd[5]);
		jnt_pos_interface.registerHandle(pos_handle_f);

		JointHandle pos_handle_g(jnt_state_interface.getHandle("INTK_LIFT_L"), &cmd[6]);
		jnt_pos_interface.registerHandle(pos_handle_g);

		JointHandle pos_handle_h(jnt_state_interface.getHandle("INTK_LIFT_R"), &cmd[7]);
		jnt_pos_interface.registerHandle(pos_handle_h);


		registerInterface(&jnt_pos_interface);


		//registerInterface(this);
	}



	// this is the example from the ros github
	private:
		JointStateInterface jnt_state_interface;
		PositionJointInterface jnt_pos_interface;

		double cmd[8];
		double pos[8];
		double vel[8];
		double eff[8];


};

// no TUNER SOFTWARE