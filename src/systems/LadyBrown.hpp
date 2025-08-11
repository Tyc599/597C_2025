#pragma once


#include "../Systems/Constants.hpp"


#include "../autonomous/PIDController.hpp"
#include "../../include/pros/motors.hpp"
#include "pros/motor_group.hpp"

using namespace Constants;
using namespace pros;
using namespace adi;




//New wing will work with motors




struct LadyBrown {
    private:
        pros::Motor LB_mtr = pros::Motor(LB_p);
   
        MotorGroup LB_mtrGroup = MotorGroup({LB_p});
        PIDController pidController = PIDController(kP, kI, kD,0.1);




    public:
        LadyBrown() {
            LB_mtrGroup.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        }






        void turnAngle(double TurnAngle){
            double direction = (TurnAngle < 0) ? -1 : 1;
            int elapsedTime = 0;
       
            TurnAngle = std::abs(TurnAngle);


            int ticks = std::abs((TurnAngle / 360.0) * LB_ticks_per_rev);


            //Reseting the position of the left and right group of motors
            LB_mtrGroup.tare_position();


            //Setting the target ticks
            pidController.setTargetTicks(ticks);
       
            while (std::abs(LB_mtr.get_position()) < ticks) {
                double controlRPM = direction * pidController.compute(std::abs(LB_mtr.get_position())); // unessecary but lit is a precuation


                LB_mtrGroup.move_velocity(controlRPM);


                delay(20);
                elapsedTime += 20;

                if (elapsedTime > 2000){
                    break;
                }


            }




            LB_mtrGroup.move_velocity(0);
       
            pidController.reset();


            delay(delayMove);
        }

        void turnUp() {
            LB_mtrGroup.move(57);
        }

        void turnDown() {
            LB_mtrGroup.move(-57);
        }

        void stop() {
            LB_mtrGroup.move(0);
        }




};



