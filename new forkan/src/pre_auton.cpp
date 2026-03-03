#include "robot-config.h"
#include "drive.h"

using namespace vex;

void pre_auton(void) {
  imu.calibrate();
  imu.setHeading(0, degrees);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(10, 20, "Calibrating IMU...");
  while (imu.isCalibrating()) wait(20, msec);

  wait(300, msec);

  opticalSensor.setLightPower(100, percent);
  opticalSensor.setLight(ledState::on);

  Drive::init();
}