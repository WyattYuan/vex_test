// 袁梓锋 能够成功使用git
#include "main.h"
#define LEFT_FRONT_WHEELS_PORT 1
#define RIGHT_FRONT_WHEELS_PORT 10
#define LEFT_REAR_WHEELS_PORT 11
#define RIGHT_REAR_WHEELS_PORT 20
#define ARM_PORT 8
#define CLAW_PORT 3

#define LEFT_BUMPER_PORT 'a'
#define RIGHT_BUMPER_PORT 'b'
#define ARM_LIMIT_SWITCH_PORT 'h'

#define MOTOR_MAX_SPEED 100 // The motor has the 36 Gearset

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "We are GUOBAOTEGONG Team!");

	pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {
	pros::Motor left_wheels (LEFT_FRONT_WHEELS_PORT);
    pros::Motor right_wheels (RIGHT_FRONT_WHEELS_PORT);
    right_wheels.set_reversed(false); // This reverses the motor

  	right_wheels.move_relative(1000, MOTOR_MAX_SPEED);
  	left_wheels.move_relative(1000, MOTOR_MAX_SPEED);
}

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
    // 初始化左前轮电机
    pros::Motor left_front_wheel (LEFT_FRONT_WHEELS_PORT);
    // 初始化右前轮电机，并设置为反转
    pros::Motor right_front_wheel (RIGHT_FRONT_WHEELS_PORT);
    right_front_wheel.set_reversed(true);
    // 初始化左后轮电机
    pros::Motor left_rear_wheel (LEFT_REAR_WHEELS_PORT);
    // 初始化右后轮电机，并设置为反转
    pros::Motor right_rear_wheel (RIGHT_REAR_WHEELS_PORT);
    right_rear_wheel.set_reversed(true);
    // 初始化主控制器
    pros::Controller master (CONTROLLER_MASTER);

    while (true) {
        // 获取左摇杆的Y轴值，用于控制前进和后退
        int power = master.get_analog(ANALOG_LEFT_Y);
        // 获取右摇杆的X轴值，用于控制转向
        int turn = master.get_analog(ANALOG_RIGHT_X);
        int left = 2 * (power + turn);
        int right = 2 * (power - turn);  
        left_front_wheel.move(left);
        right_front_wheel.move(right);
        left_rear_wheel.move(left);
        right_rear_wheel.move(right);
        
        pros::delay(2);
    }
}