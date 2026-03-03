#include "robot-config.h"

// forkan comments her

using namespace vex;

// Forward declarations
void pre_auton(void);
void autonomous(void);
void usercontrol(void);

// Sukinah was here ;)
int main() {

    // Run pre-autonomous setup
    pre_auton();

    // Set up callbacks for competition
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Prevent main from exiting
    while (true) {
        wait(100, msec);
    }
}