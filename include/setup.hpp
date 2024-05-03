#pragma once


#include "api.h"
#include "lemlib/chassis/chassis.hpp"

// Define motors
extern pros::Motor left_front_motor;
extern pros::Motor left_back_motor;
extern pros::Motor right_front_motor;
extern pros::Motor right_back_motor;
extern pros::Motor intake_roller;
extern pros::Motor intake_open;
extern pros::Motor madeuplift;
// Define motor groups
extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;

extern pros::Controller master;
// Define drivetrain configuration
extern lemlib::Drivetrain_t drivetrain;

// Define odometry sensors
extern lemlib::OdomSensors_t sensors;

// Define lateral and angular chassis controllers
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;

// Define chassis
extern lemlib::Chassis chassis;
