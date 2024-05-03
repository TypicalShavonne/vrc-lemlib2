#include "api.h"
#include "pros/misc.h"
#include "setup.hpp"

bool reversey = false;

float driveCurve(float input, float scale) {
    if (scale != 0) {
        return (powf(2.718, -(scale / 10)) + powf(2.718, (fabs(input) - 127) / 10) * (1 - powf(2.718, -(scale / 10)))) * input;
    }
    return input;
}

std::pair<float, float> arcade(int throttle, int turn, float curveGain = 0) {
    // turn *= 1;
    float leftPower = driveCurve(throttle + turn, curveGain);
    float rightPower = driveCurve(throttle - turn, curveGain);
    return std::make_pair(leftPower, rightPower);
}

std::pair<float, float> curvature(int throttle, int turn, float curveGain) {
    if (abs(throttle) < 4) {
        return arcade(throttle, turn, curveGain);;
    }

    float leftPower = throttle + (std::abs(throttle) * turn) / 127.0;
    float rightPower = throttle - (std::abs(throttle) * turn) / 127.0;

    leftPower = driveCurve(leftPower, curveGain);
    rightPower = driveCurve(rightPower, curveGain);

	return std::make_pair(leftPower, rightPower);
}

void drive() {
	while (true) {
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { reversey = !reversey; }

		double power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	    
		auto [left, right] = arcade(power, turn, 0);
        // auto [left, right] = curvature(power, turn, 7.2);

        if (reversey){ left *= -1; right *= -1; }

	    left_side_motors.move(left);
	    right_side_motors.move(right);

		pros::delay(10);
	}
}

void intake_open_controller() {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake_open.move_velocity(50);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake_open.move_velocity(-50);
        } else {
            intake_open.move_velocity(0);
        }
        pros::delay(30);
    }
}

void intake_roller_controller() {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake_roller.move_velocity(600);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intake_roller.move_velocity(-600);
        } else {
            intake_roller.move_velocity(0);
        }
        pros::delay(30);
    }
}

void madeuplift_controller() {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            madeuplift.move_velocity(50);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            madeuplift.move_velocity(-50);
        } else {
            madeuplift.move_velocity(0);
        }
        pros::delay(30);
    }


    
}


void t1() {
left_side_motors.move_absolute(200, 50);
}

void t2() {
    right_side_motors.move_absolute(200, 50);
}