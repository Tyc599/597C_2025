#pragma once

#include <cmath>
#include <cstdint>
#include <stdint.h>
namespace Constants {
    const int8_t fl_p = 11; // Port of Front Left motor
    static constexpr unsigned char ml_p = 12; // Port of Middle Left motor
    static constexpr unsigned char bl_p = 13; // Port of Back Left motor
    static constexpr unsigned char fr_p = 1; // Port of Front Right motor
    static constexpr unsigned char mr_p = 2; // Port of Middle Right motor
    static constexpr unsigned char br_p = 3; // Port of Back Right motor

    static constexpr unsigned char it1_p = 16; // Port of the Elevation mech
    static constexpr unsigned char it2_p = 15; // Port of the Elevation mech

    static constexpr unsigned char hinge_p = 'A'; // Port for the Catapult's button

    static constexpr unsigned char threshold = 11; // Threshhold for controller to start moving the robot
    
    //static constexpr float trackwidth = 4.6f; // The distance between both the left and an right motors

    static const double pi = 3.14159265358979323846; // pi
    static const double radToDeg = 180/pi;
    static constexpr float wheelDiameter = 3.25f; // Diameter of drive wheels

    //drive train auton values---------------
    static const float trackwidth = 14.18f;
    static const float kP = 0.5;
    static const float kI = 0.5;
    static const float kD  = 0.5;
    static const float radius = trackwidth; // can be found by measuring the width of the drive train and then dividing by two
    
    //Darshaan's Code (597C)
    //static const double wheelDiameter = 3.25; // Diameter of drive wheels(inches)
    static const double gearRatio = 3.0/5.0;
    static const int encoder_ticks_per_rev = 1800;
    static const double wheelCircumference = 3.25 * pi;
    static const double distancePerTick = wheelCircumference/(encoder_ticks_per_rev*gearRatio);
    /// @brief 
    static const int maxRPM = 100;
    static const int maxVolt = 127;
    static const int delayMove = 20;
    static const int offsetInches = 11;
    //-------------------------------


    static const double integral_threshold = 10;

    /*
    1800 ticks/rev with 36:1 gears (BLUE)
    900 ticks/rev with 18:1 gears (GREEN)
    300 ticks/rev with 6:1 gears (RED)
    */

    static constexpr double unitsToRevolution = 642.8571429; // Motor units per revolution for drive wheels (900 * 5/7)
    static const double inchesPerTick = wheelDiameter*pi/unitsToRevolution; // The inches per tick for the drive encoders

    static inline double headingRestrict(double heading) {
        if (heading <= 0) heading += pi*2;
        heading = fmod(std::abs(heading),pi*2);
        return heading;
    }
    static constexpr unsigned char LB_p = 17; // lady brown port 1


    static const int LB_ticks_per_rev = 900;
    static const double LBTurnUpAngle = 100.0;
};