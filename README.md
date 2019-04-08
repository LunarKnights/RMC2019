# RMC2019
RMC 2019 Repository

**Package Breakdown**
* lk_rmc
  * lk_rmc_description
    * Contains the URDF & meshes for the robot model
  * lk_rmc_teleop
    * Contains code to handle custom cmd_vel input from gui/keyboard/joystick
  * lk_rmc_hardware
    * Contains custom robot hw code, and hardware interface for ros-control
  * lk_rmc_navigation
    * Handles move-base and mapping
  * lk_rmc_slam
    * Handles slam & gmapping server
  * lk_rmc_gazebo
    * Contains worlds & required code for gazebo simulation
  * lk_rmc_mc
    * High-level mission controller for setting goals and handling state machines