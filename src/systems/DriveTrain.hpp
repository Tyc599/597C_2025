#pragma once

#include "../Systems/Constants.hpp"

#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "../autonomous/PIDController.hpp"
#include <functional>

using namespace Constants;
using namespace pros;

class DriveTrain {
    Motor fl_mtr = Motor(fl_p);
    Motor btl_mtr = Motor(ml_p);
    Motor bl_mtr = Motor(bl_p);
    Motor fr_mtr = Motor(fr_p);
    Motor btr_mtr = Motor(mr_p);
    Motor br_mtr = Motor(br_p);

    MotorGroup left_g  = MotorGroup({-fl_p, -ml_p, -bl_p});
    MotorGroup right_g = MotorGroup({fr_p, mr_p, br_p});

    PIDController pidController = PIDController(kP, kI, kD, integral_threshold); 


    std::function<void(void)> teleMove;
    double average_vector(std::vector<double> input){
        double output = 0;
        for(int i = 0; i < input.size(); i++){
            output += input[i];
        }
        output /= input.size();
        return output;
    }
    public:

    DriveTrain() {
        left_g.tare_position();
        right_g.tare_position();
    }

    inline void tankDrive(signed char leftY, signed char rightY){
        left_g.move(abs(leftY)<threshold ? 0 :leftY);
        right_g.move(abs(rightY)<threshold ? 0 :rightY);
    }

    inline void arcadeDrive(signed char leftY, signed char rightX) {
        leftY = abs(leftY)<threshold ? 0 : leftY;
        rightX = abs(rightX)<threshold ? 0 : rightX;
        left_g.move(leftY + rightX);
        right_g.move(leftY - rightX);
    }

    //This code is from Darshaan Karthikeyan (597C)
    //Function allows for the forward and backward motion of the drivetrain based on the given inches
    inline void moveHorizontal(double inches){
        if (fabs(inches) > offsetInches){
            inches = (inches > 0) ? inches-offsetInches:inches+offsetInches;
        }
        int ticksToMove = (inches)/distancePerTick;

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();

        left_g.move_relative(ticksToMove, maxRPM);
        right_g.move_relative(ticksToMove, maxRPM);
        
        while (std::abs(left_g.get_position()) <= abs(ticksToMove) && std::abs(right_g.get_position()) <= abs(ticksToMove)) {
            delay(20); // Prevents busy waiting
        }

        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        delay(delayMove);
    }

    //Function allows for the angled turned allowing for the drivetrain to turn left or right at any assigned angle
    inline void turnAngle(double angle){
        double direction = (angle < 0) ? 1: -1;
        angle = std::abs(angle);

        double distanceTravel = (trackwidth * angle * pi) / (360*2);
        int ticks = (distanceTravel / distancePerTick);

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();

        //Setting the target ticks
        pidController.setTargetTicks(ticks);
        
        while (std::abs(left_g.get_position()) < ticks && std::abs(right_g.get_position()) < ticks) {
            double controlRPM = direction * pidController.compute(std::abs(left_g.get_position()));

            left_g.move_velocity(controlRPM);
            right_g.move_velocity(-(controlRPM));

            delay(20);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        
        pidController.reset();

        delay(delayMove);
    }

    inline void turnAngleNew(double angle, signed char Direction){
        double distanceTravel = ((trackwidth)*angle*pi)/(360.0*2.0);
        int ticks = distanceTravel/distancePerTick;

        //Reseting the position of the left and right group of motorsp
        left_g.tare_position();
        right_g.tare_position();
        
        left_g.move_relative(Direction * ticks, maxRPM);
        right_g.move_relative(Direction * -(ticks), maxRPM);

        while (std::abs(left_g.get_position()) <= abs(ticks) && std::abs(right_g.get_position()) <= abs(ticks)) {
            delay(20); // Prevents busy waiting
        }

        delay(delayMove);
    }

    inline void turnAngle_sohan(signed char turnAngle) {
        left_g.tare_position();
        right_g.tare_position();

        double arc_length = ((turnAngle*pi*radius)/180) ;
        double theta = arc_length/radius;

        double error = arc_length;
        double prevError = error;
        double proportional = 0;
        double integral = 0;
        double derivative = 0;

        while (fabs(error) >= 1.0) {
            proportional = error;
            integral += error;
            derivative = prevError - error;

            double speed = proportional * kP + integral * kI + derivative * kD;
            left_g.move(speed);
            right_g.move(-speed);
            error = left_g.get_position() - right_g.get_position();
            error /= 2;
            error *= radius *  pi / 180.0;
            error = arc_length - error;
        }
        left_g.move(0);
        right_g.move(0);
    }

    inline void moveForward(signed char moveAmount) {
        left_g.move_relative(moveAmount,100);
        right_g.move_relative(moveAmount,100);
    }

    inline void moveBackward(signed char moveAmount) {
        // 360 
        // 5 : 3
        float rotations = moveAmount * 5 / 3;
        float circumference = 3.25 * pi;
        int ticks = rotations * circumference;
        left_g.move_absolute(ticks, 100);
        left_g.move_absolute(ticks, 100);
    }
 
    inline void moveHorizontalNewTest(double inches, int32_t velocity){
        if (fabs(inches) > offsetInches){
            inches = (inches > 0) ? inches-offsetInches:inches+offsetInches;
        }
        int ticksToMove = (inches)/distancePerTick;


        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();


        left_g.move_relative(ticksToMove, velocity);
        right_g.move_relative(ticksToMove, velocity);
       
        while (std::abs(left_g.get_position()) <= abs(ticksToMove) && std::abs(right_g.get_position()) <= abs(ticksToMove)) {
            delay(20); // Prevents busy waiting
        }


        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


        delay(delayMove);
    }



};