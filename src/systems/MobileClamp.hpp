#pragma once

#include "pros/motors.hpp"
#include "../Systems/Constants.hpp"

#include "../../include/pros/adi.hpp"

using namespace Constants;
using namespace pros;
using namespace adi;

struct MobileClamp {
    private:
        DigitalOut piston = DigitalOut(hinge_p);

    public:
        MobileClamp() {
        }

        void unClamp() {
            piston.set_value(false);
        }

        void clamp() {
            piston.set_value(true);
        }

        void changeClampState(bool newState) {
            piston.set_value(newState);
        }

};