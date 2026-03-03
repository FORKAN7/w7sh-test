#pragma once

#include "robot-config.h"

namespace Intake {

  // ------------------------------------------------------------
  // Control API
  // ------------------------------------------------------------

  //  1  = intake in
  // -1  = intake out
  //  0  = stop
  void setState(int state);

  // Returns current intake state
  int getState();

  // Runs intake + sorting logic
  // Must be called periodically (e.g., every 20ms)
  
  void apply();

}