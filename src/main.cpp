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
	//left
	/*
	mbc.clamp(); // clamp and unclamp and reversed. clamp unclamps. unclamp clamps.
	dt.moveHorizontal(-24.5,70); 
	mbc.unClamp();
	mbc.unClamp();
	//LB.turnAngle(200);
	delay(1500);
	
	it.spinUp();
	dt.turnAngle(90);
	dt.moveHorizontal(22);
	delay(2500);
	it.stop();
	dt.turnAngle(-185);
	dt.moveHorizontal(20);
	//dt.moveHorizontal(-10);
	*/

	//24 inches
	//NEW SKILLS AUTONOMUS
	mbc.clamp(); // unclaamps
//dt.moveHorizontal(-24.0 + 7.0 );
//dt.turnAngle(-90.0);
dt.moveHorizontal(-3.0);

delay(200)

mbc.unClamp(); // this clamps the robot
mbc.unClamp();

dt.moveHorizontal(-3.0);


dt.turnAngle(-90);

dt.moveHorizontal(-24.0);
dt.turnAngle(-45.0);
dt.moveHorizontal((1.414 * -24.0) / 2.0);
mbc.clamp(); // unclamps

/*
dt.moveHorizontal((1.414 * 24.0) / 2.0);
dt.turnAngle(-135.0);
dt.moveHorizontal(3.0 * -24.0 + 2.0);
mbc.unClamp(); // clamps down
mbc.unClamp(); // clamps down harder
dt.moveHorizontal(-(24.0 + 2.0));
dt.turnAngle(45.0);
dt.moveHorizontal((1.4141 * -24.0) / 2.0);
mbc.clamp(); // unclamps

dt.moveHorizontal((1.4141 * 24.0) / 2.0);
dt.turnAngle(45.0);
dt.moveHorizontal(4.0 * 24.0);
dt.turnAngle(90.0);
dt.moveHorizontal((-24.0 * 2.0) + 2.0);
mbc.unClamp(); // clamps onto goal
mbc.unClamp(); // clamps extra hard
dt.moveHorizontal((24.0 * 2.0) + 2.0);
dt.turnAngle(135.0);
dt.moveHorizontal((1.4141 * -24.0) / 2.0);
mbc.clamp(); // unclamps the mobile goal

dt.moveHorizontal((1.4141 * 24.0) / 2.0);
dt.turnAngle(45.0);
dt.moveHorizontal(3.0 * 24.0);
dt.turnAngle(-90.0);
dt.moveHorizontal(-5.0);
mbc.unClamp(); // clamps down
dt.moveHorizontal(5.0);
dt.turnAngle(-90.0);
dt.moveHorizontal(-24.0);
dt.turnAngle(45.0);
dt.moveHorizontal((1.414 * -24.0) / 2.0);
mbc.clamp(); // unclamps



*/

	


	

//SKILLS AUTONOMOUS DO NOT TOUCH
	/*
    dt.moveHorizontal(-5);
	mbc.clamp();
	dt.turnAngle(-90);
	it.spinUp();
	dt.moveHorizontal(12);
	dt.moveHorizontal(-3);
	dt.turnAngle(-20):
	dt.moveHorizontal(5);
	dt.turnAngle(20);
	dt.moveHorizontal(8);
	dt.moveHorizontal(-4);
	dt.turnAngle(-90);
	dt.moveHorizontal(12);
	dt.turnAngle(90);
	dt.moveHorizontal(12);
	dt.moveHorizontal(-22);
	dt.turnAngle(90);
	dt.moveHorizontal(-22);
	mbc.unClamp();
	dt.moveHorizontal(-5);

	

	/*it.spinUp();
	it.autonSpin(maxVolt, 4000); //duration is in milliseconds
	dt.moveHorizontal(-20);
	dt.turnAngle(230);
	dt.moveHorizontal(22);
	it.spinDown();	
	delay(700);
	it.stop();

    debugWait();
	/*dt.tankDrive(127,127);//move forward to touch the ladder
	delay(900);
	dt.tankDrive(0,0);*/
	/*mbc.unClamp();
	dt.tankDrive(-80,-80);
	delay(800);
	dt.tankDrive(0,0);
	mbc.clamp();
	it.spinUp();
	delay(2000);
	dt.turnAngle(90);
	it.stop();
	dt.tankDrive(60,60);
	delay(900);
	dt.turnAngle(90);
	dt.tankDrive(127,127);
	delay(1300);
	dt.turnAngle(45);
	dt.tankDrive(127,127);
	delay(400);
	dt.tankDrive(0,0);
	it.stop();*/

	

	/*dt.tankDrive(127,127);
	delay(1500);
	dt.tankDrive(0,0);
	dt.turnAngle(-180);
	it.spinUp();
	dt.tankDrive(-127,-127);
	delay(700);
	dt.turnAngle(180);
	dt.tankDrive(127,127);
	delay(1250);
	dt.tankDrive(0,0);
	

	/*dt.turnAngle(90);
	it.spinUp();//make intake spin up
	delay(2220);
	it.stop();//stops intake
dt.tankDrive(-60,-60);
delay(500);
dt.turnAngle(180);
dt.tankDrive(60,60);

	mbc.changeClampState(true); // clamps the mobile clamp
	mbc.changeClampState(false); //unclamps the mobile clamp

	dt.turnAngle(90);//makes the robot turb 90 degrees(hopefully)


	//dt.tankDrive(0, 0);
	//programs -> 597A ->  competition -> programming skills -> */

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