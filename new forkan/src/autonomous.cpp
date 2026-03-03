#include "robot-config.h"
#include "drive.h"
#include "intake+sorting.h"
#include "scoring.h"

using namespace vex;

// -------------------- plans --------------------

static void planA() {
  // TODO: your plan A
}

static void planB() {
  // TODO: your plan B
}

static void planC() {
  // TODO: your plan C
}

// -------------------- competition callback --------------------

void autonomous(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(10, 20, "Auton...");
    
  // 🚨⚠️ Change this manually before each match, then re-download:
  planA();
  //planB();   
  //planC();

  Brain.Screen.printAt(10, 60, "Done");
}