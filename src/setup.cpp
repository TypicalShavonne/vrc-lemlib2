#include "api.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"


pros::Motor left_front_motor(3, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor left_back_motor(4, pros::E_MOTOR_GEARSET_18, false); 
pros::Motor right_front_motor(1, pros::E_MOTOR_GEARSET_36, true); 
pros::Motor right_back_motor(2, pros::E_MOTOR_GEARSET_36, true); 

pros::Motor intake_roller(11, pros::E_MOTOR_GEARSET_36);
pros::Motor intake_open(10, pros::E_MOTOR_GEARSET_36);
pros::Motor madeuplift(12, pros::E_MOTOR_GEARSET_36);

pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});

pros::Controller master(pros::E_CONTROLLER_MASTER);

lemlib::Drivetrain_t drivetrain {
    &left_side_motors, 
    &right_side_motors, 
    39, 
    3.25, 
    360
};
 

lemlib::OdomSensors_t sensors {
    nullptr,
    nullptr,
    nullptr,
    nullptr, 
    nullptr 
};
 

lemlib::ChassisController_t lateralController {
    8, 
    30, 
    1, 
    100, 
    3, 
    500, 
    5 
};
 

lemlib::ChassisController_t angularController {
    4, 
    40, 
    1, 
    100, 
    3, 
    500, 
    40 
};
 
 

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
