#include "robot-config.h"
#include "drive.h"
#include "intake+sorting.h"
#include "scoring.h"


using namespace vex;

void autonomous(void);

void usercontrol() {

  opticalSensor.setLightPower(100, percent);
  opticalSensor.setLight(ledState::on);

 bool r1Prev = false;
bool r2Prev = false;
int intakeState = 0;

  while (true) {

    // manual autonomous trigger
  if (Controller1.ButtonDown.pressing() && Controller1.ButtonB.pressing()) {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10, 50, "Running AUTONOMOUS...");
    autonomous();
  }

    // -----------------------------
    // Drive (joysticks)
    // -----------------------------
    int forwardPct = -Controller1.Axis3.position();
    int turnPct    = Controller1.Axis1.position();
    Drive::arcade(forwardPct, turnPct);

  
    // -----------------------------
    // Intake (R1 / R2 HOLD)
    // -----------------------------
   // 1 forward, -1 reverse, 0 stop
// -----------------------------
// Intake (R1 / R2 TOGGLE)
// -----------------------------
bool r1Now = Controller1.ButtonR1.pressing();
bool r2Now = Controller1.ButtonR2.pressing();

// R1 toggle forward
if (r1Now && !r1Prev) {
  intakeState = (intakeState == 1) ? 0 : 1;
}

// R2 toggle reverse
if (r2Now && !r2Prev) {
  intakeState = (intakeState == -1) ? 0 : -1;
}

r1Prev = r1Now;
r2Prev = r2Now;

Intake::setState(intakeState);
Intake::apply();
    // -----------------------------
    // Scoring /L1/L2 (HOLD TO RUN)
    // -----------------------------
    if (Controller1.ButtonL1.pressing()) {
      ScoringDrive.spin(forward, 100, percent); 
    }
    else if (Controller1.ButtonL2.pressing()) {
      ScoringDrive.spin(reverse, 100, percent);
    }
    else {
      ScoringDrive.stop(coast);
    }
  }

  if (Controller1.ButtonUp.pressing()) {
  DigitalOutA.set(true);
  DigitalOutB.set(true);
} 
else if (Controller1.ButtonDown.pressing()) {
  DigitalOutA.set(false);
  DigitalOutB.set(false);
}

if (Controller1.ButtonLeft.pressing()) {
  DigitalOutH.set(false);
} 
else if (Controller1.ButtonRight.pressing()) {
  DigitalOutH.set(true);
}
}