#pragma once
#include "vex.h"

using namespace vex;

// ============================================================
// Core Devices
// ============================================================

extern brain Brain;
extern competition Competition;
extern controller Controller1;

// ============================================================
// Motors
// ============================================================

// ---- Walls motors
extern motor motor1;
extern motor motor2;
extern motor motor3;
extern motor motor4;
extern motor motor5;
extern motor motor6;
extern motor motor7;
extern motor motor8;
extern motor motor9;
extern motor motor10;

// ---- Drive motors
extern motor driveRB;
extern motor driveLB;
extern motor driveRF;
extern motor driveLF;

// ============================================================
// Motor Groups
// ============================================================

extern motor_group leftDrive;
extern motor_group rightDrive;

extern motor_group intakeMain;
extern motor_group intakeOpp;
extern motor_group ScoringDrive;

// Sorter reference (motor7)
extern motor& sorterMotor;

// ============================================================
// Sensors
// ============================================================

extern inertial imu;
extern optical opticalSensor;

////penumatic
extern digital_out DigitalOutA;
extern digital_out DigitalOutB;
extern digital_out DigitalOutH;