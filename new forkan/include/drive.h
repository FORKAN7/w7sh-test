#pragma once

#include "robot-config.h"

namespace Drive {

    // Initialization
    void init();

    // Driver control
    void arcade(int forwardPct, int turnPct);

    // Stop with brake type
    void stop(brakeType b = brake);

    // Autonomous helpers
    void driveDistance(double inches, int speedPct = 60);
    void turnToHeading(double targetDeg,
                       int maxSpeedPct = 40,
                       int timeoutMs = 2500);
}