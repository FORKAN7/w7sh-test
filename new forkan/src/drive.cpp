#include "robot-config.h"

using namespace vex;
static const int DEADBAND = 5;

// If your robot drives backward, flip these signs.
static const int DRIVE_FWD_SIGN  = -1;  // forward on stick = forward robot
static const int DRIVE_TURN_SIGN = 1; // right on stick = right turn

// ---- Drive speed tuning ----
static const int DRIVE_SPEED = 100;   // overall drive speed (0–100)
static const int TURN_SPEED  = 70;   // turning sensitivity (0–100)

// Distance driving assumptions (edit later when you know wheel size)
static const double WHEEL_DIAM_IN = 4.0; // common
static const double WHEEL_CIRC_IN = WHEEL_DIAM_IN * M_PI;

namespace Drive {

  void init() {
    leftDrive.setStopping(coast);
    rightDrive.setStopping(coast);
    leftDrive.setVelocity(100, percent);
    rightDrive.setVelocity(100, percent);
  }

  void arcade(int forwardPct, int turnPct) {
  if (abs(forwardPct) < DEADBAND) forwardPct = 0;
  if (abs(turnPct)    < DEADBAND) turnPct    = 0;

  // Base directions (fixed defaults)
  int f = DRIVE_FWD_SIGN  * forwardPct * DRIVE_SPEED / 100;
  int t = DRIVE_TURN_SIGN * turnPct    * TURN_SPEED  / 100;

  int left  = f + t;
  int right = f - t;

  // Clamp
  if (left > 100) left = 100;
  if (left < -100) left = -100;
  if (right > 100) right = 100;
  if (right < -100) right = -100;

  leftDrive.spin(forward, left, percent);
  rightDrive.spin(forward, right, percent);
  }


  void stop(brakeType b = brake) {
    leftDrive.stop(b);
    rightDrive.stop(b);
  }

  void driveDistance(double inches, int speedPct = 60) {
    double revs = inches / WHEEL_CIRC_IN;

    leftDrive.resetPosition();
    rightDrive.resetPosition();

    directionType dir = (inches >= 0) ? fwd : reverse;
    double absRevs = fabs(revs);

    leftDrive.spinFor(dir, absRevs, rotationUnits::rev, speedPct, velocityUnits::pct, false);
    rightDrive.spinFor(dir, absRevs, rotationUnits::rev, speedPct, velocityUnits::pct, true);
  }

  // Turn to an absolute heading (0..360). We'll use headings: 0, 90, 180, 270.
  void turnToHeading(double targetDeg, int maxSpeedPct = 40, int timeoutMs = 2500) {
    while (targetDeg >= 360) targetDeg -= 360;
    while (targetDeg < 0) targetDeg += 360;

    int start = Brain.Timer.time(msec);

    while (Brain.Timer.time(msec) - start < timeoutMs) {
      double current = imu.heading();
      double error = targetDeg - current;

      if (error > 180) error -= 360;
      if (error < -180) error += 360;

      if (fabs(error) < 2.5) break;

      double kP = 1.1;
      int turnPower = (int)(kP * error);

      if (turnPower > maxSpeedPct) turnPower = maxSpeedPct;
      if (turnPower < -maxSpeedPct) turnPower = -maxSpeedPct;

      if (abs(turnPower) < 12) turnPower = (turnPower > 0) ? 12 : -12;

      leftDrive.spin(fwd,  turnPower, percent);
      rightDrive.spin(fwd, -turnPower, percent);
      wait(15, msec);
    }

    stop(brake);
    wait(80, msec);
  }
}