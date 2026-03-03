#pragma once

#include "robot-config.h"

namespace Scoring {

  // 0 = stop
  // 1 = run upper scoring
  void setUpper(int state);

  // 0 = stop
  // 1 = run middle scoring
  void setMiddle(int state);

  // Stop everything
  void stop();

  // Apply scoring state (call periodically)
  void apply();

}