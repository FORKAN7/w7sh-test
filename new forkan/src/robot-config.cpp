#include "robot-config.h"

using namespace vex;

// ============================================================
// Core Devices
// ============================================================

brain Brain;
competition Competition;
controller Controller1(primary);

// ============================================================
// Motors
// ============================================================

// ---- Walls motors
motor motor1(PORT11,  gearSetting::ratio6_1,  true);//intakeFrontLeft
motor motor2(PORT4, gearSetting::ratio6_1,  false);//intakeFrontRight
motor motor3(PORT5,  gearSetting::ratio6_1,  false);//intakeCenter
motor motor4(PORT13,  gearSetting::ratio6_1,  false);//intakeBackDown
motor motor5(PORT14,  gearSetting::ratio6_1,  false);//ScoringCenter
motor motor6(PORT15,  gearSetting::ratio6_1,  true);//ScoringFrontr
motor motor7(PORT7, gearSetting::ratio6_1, false);//sorterMotor
motor motor8(PORT17, gearSetting::ratio6_1,  false);
motor motor9(PORT19, gearSetting::ratio6_1,  false);
motor motor10(PORT18, gearSetting::ratio6_1,  true);

// ---- Drive motors
motor driveRB(PORT8, gearSetting::ratio18_1, false);
motor driveLB(PORT3, gearSetting::ratio18_1, true);
motor driveRF(PORT2, gearSetting::ratio18_1, false);
motor driveLF(PORT1, gearSetting::ratio18_1, true);



// ============================================================
// Motor Groups
// ============================================================

motor_group leftDrive(driveLF, driveLB);
motor_group rightDrive(driveRF, driveRB);



motor_group intakeMain(motor1, motor2, motor3, motor4,motor7);
motor_group intakeOpp(motor8, motor9);
motor_group ScoringDrive(motor6, motor5);

// Sorter reference (motor7)
motor& sorterMotor = motor7;

// ============================================================
// Sensors
// ============================================================

inertial imu(PORT6);
optical opticalSensor(PORT12);

// ============================================================
// Digital Outputs (Pneumatics / Pistons)
// ============================================================

digital_out DigitalOutA(Brain.ThreeWirePort.A);
digital_out DigitalOutB(Brain.ThreeWirePort.B);
digital_out DigitalOutH(Brain.ThreeWirePort.H);