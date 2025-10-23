#pragma once

#include "../Systems/Constants.hpp"

#include "../../include/pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake {
    private:
        Motor it1_mtr = Motor(it1_p);
        Motor it2_mtr = Motor(it2_p);
        Motor it3_mtr = Motor(it3_p);


        MotorGroup it_mtr = MotorGroup({it1_p, it2_p,-it3_p});
    public:
        Intake() {
            it_mtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        }

        void stop() {
            it_mtr.move(0);
        }

        void spinUp() {
            MotorGroup it_mtr = MotorGroup({it1_p, it2_p,-it3_p});
            it_mtr.move(127);
        }

        void spinDown() {
            MotorGroup it_mtr = MotorGroup({-it1_p, it2_p,-it3_p});
            it_mtr.move(-127);
        }

        void spinout() {
            MotorGroup it_mtr = MotorGroup({-it1_p, it2_p, it3_p});
            it_mtr.move(127);
        }

        void autonSpin(int voltage, int duration){
            it_mtr.move(-(voltage));
            delay(duration);
            it_mtr.move(0);
        }
};