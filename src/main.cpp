#include "main.h"

#include "pros/rtos.hpp"
#include "systems/DriveTrain.hpp"
#include "systems/Intake.hpp"
#include "systems/MobileClamp.hpp"
#include "systems/LadyBrown.hpp"
//I love you raul
using namespace pros;


Controller master(E_CONTROLLER_MASTER);
DriveTrain dt = DriveTrain();
Intake it = Intake();
MobileClamp mbc = MobileClamp();
LadyBrown LB = LadyBrown();


/*
lvgl::LV_IMG_DECLARE(normal);
lv_obj_t* bgImg = lv_img_disp(&normal);
*/
char lY,rY,rX = 0;
/*
bool arcade;
inline lv_res_t toggleDriveMode(lv_obj_t* btn)
{
	arcade = !arcade;
    if (arcade) {
		dt.teleMove = [=]{dt.arcadeDrive(lY,rX);};
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Arcade Drive");
		} else {
		dt.teleMove = [=]{dt.tankDrive(lY,rY);};
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Tank Drive");
    }
	btnSetToggled(btn, arcade);
    return LV_RES_OK;
}

bool skills_auton;
inline lv_res_t toggleAutonType(lv_obj_t* btn)
{
	skills_auton = !skills_auton;
	if (skills_auton) {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Skills Auton");
	} else {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Match Auton");
	}
	btnSetToggled(btn, skills_auton);
    return LV_RES_OK;
}

bool right_auton;
inline lv_res_t toggleAutonSide(lv_obj_t* btn)
{
	right_auton = !right_auton;
	if (right_auton) {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Right Auton");
	} else {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Left Auton");
	}
	btnSetToggled(btn, right_auton);
    return LV_RES_OK;
}
*/
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	/*lv_obj_t* odometryInfo = createLabel(lv_scr_act(), 20, DISP_CENTER, 300, 40, "Odom Info");
	//Odometry odom = Odometry(&dt, &odometryInfo);
*/
	dt.arcadeDrive(lY,rX);/*
	lv_obj_t* driveBtn = createBtn(lv_scr_act(), 50, DISP_CENTER, 300, 20, "Tank Drive", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_btn_set_action(driveBtn, LV_BTN_ACTION_CLICK, toggleDriveMode);

	lv_obj_t* autonTypeBtn = createBtn(lv_scr_act(), 80, DISP_CENTER, 300, 20, "Match Auton", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_btn_set_action(autonTypeBtn, LV_BTN_ACTION_CLICK, toggleAutonType);

	lv_obj_t* autonSideBtn = createBtn(lv_scr_act(), 110, Display::DISP_CENTER, 300, 20, "Match Left", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_btn_set_action(autonSideBtn, LV_BTN_ACTION_CLICK, toggleAutonSide);
	lv_obj_t* odometryInfo = createLabel(lv_scr_act(), 20, DISP_CENTER, 300, 40, "Odom Info");
	lv_obj_t* pickleT = createLabel(lv_scr_act(), 140, DISP_CENTER, 300, 100,
		"Current pickle high scores (5 min)\nEsteban: 11\nJayleen: 10\nJI: 9");
	*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

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

void debugWait() {
	dt.arcadeDrive(0, 0);
	delay(1000); // change to 500 when running fr
}

void autonomous() {
	//dt.moveforward(1000, 100); // move forward for 1 second at 100% speed
	//dt.turnAngle(90, 100); // turn right 90 degrees at 100% speed
	//dt.moveBackward(1000, 100); // move backward for 1 second at 100% speed
	//dt.turnAngle(-90, 100); // turn left 90 degrees at 100% speed
	//dt.arcadeDrive(0, 0); // stop the robot
	//it.spinUp();// spin up the intake
	//it.spinDown();// spin down the intake
	//programs -> 597C ->  competition -> programming skills -> */

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
	bool prcsM = false;
	int prcsET = 0;
	bool clampState = false;
	bool LBState = false;

	while (true) {
		// Set precision mode (dont repeat until half a second)
		if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && (millis() - prcsET > 500)) {prcsM = !prcsM; prcsET = millis();}

		{ // Set input for the drivetrain's teleMove according to precision mode.
			lY = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)/2 : master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			rY = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)/2 : master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
			rX = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)/2 : master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		}

		dt.arcadeDrive(lY, rX);

		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
			clampState = !clampState;
			mbc.changeClampState(clampState);
		}

		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
			LBState = !LBState;

			if (LBState){
				LB.turnAngle(LBTurnUpAngle);
			}else{
				LB.turnAngle(-LBTurnUpAngle);
			}

			
		}

		if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
            it.spinUp();
        } else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
            it.spinDown();
        } else {
			it.stop();
		}


		delay(20);
	}
}