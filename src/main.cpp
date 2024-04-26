#include "main.h"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
pros::Motor left_front_motor(3, pros::E_MOTOR_GEARSET_06, false); // port 1, blue gearbox, not reversed
pros::Motor left_back_motor(4, pros::E_MOTOR_GEARSET_18, false); // port 2, green gearbox, not reversed
pros::Motor right_front_motor(1, pros::E_MOTOR_GEARSET_36, true); // port 3, red gearbox, reversed
pros::Motor right_back_motor(2, pros::E_MOTOR_GEARSET_36, true); // port 4, red gearbox, reversed

pros::Motor intake_roller(5, pros::E_MOTOR_GEARSET_36);
pros::Motor intake_open(6, pros::E_MOTOR_GEARSET_36);


pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});


// drivetrain motors
lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    39, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};
 
// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr,
    nullptr,
    nullptr,
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    nullptr // inertial sensor
};
 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};
 
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.calibrate();
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

            float xValue = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            float yValue = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

            float drivetrain_left_side_speed = yValue + xValue;
            float drivetrain_right_side_speed = yValue - xValue;
                
            left_side_motors.move_velocity(drivetrain_left_side_speed*100);
            right_side_motors.move_velocity(drivetrain_right_side_speed*100);



        bool intake_roll_r1 = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        bool intake_roll_r2 = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        bool intake_open_a =  master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
        bool intake_open_b =  master.get_digital(pros::E_CONTROLLER_DIGITAL_A);

        if (intake_roll_r1) {
            intake_roller.move_velocity(50);
        }
        if (intake_roll_r2) {
            intake_roller.brake();
        }
        if (intake_open_a) {
            intake_open.move_velocity(50);
        }
        if (intake_roll_r2) {
            intake_open.move_velocity(-50);
        }
        

    		pros::delay(20);
	}
}
