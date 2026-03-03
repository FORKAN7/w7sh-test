#include "scoring.h"

using namespace vex;

// ------------------------------------------------------------
// File-local constants
// ------------------------------------------------------------

static const int SCORE_SPEED = 100;
// static const int FEED_SPEED  = 50;

// ------------------------------------------------------------
// Internal State
// ------------------------------------------------------------

namespace Scoring {

  // static int upperState  = 0;   // 1 = running
  // static int middleState = 0;   // 1 = running
static int dirState = 0;

  // ----------------------------------------------------------
  // Public Control Functions
  // ----------------------------------------------------------

   void setUpper(int state) {
    // نستخدمها كـ forward
    dirState = (state == 1) ? 1 : 0;
  }

   void setMiddle(int state) {
    // نستخدمها كـ reverse
    dirState = (state == 1) ? -1 : 0;
  }

  void stop() {
    dirState = 0;
    ScoringDrive.stop(coast);
  }


  // ----------------------------------------------------------
  // Apply Scoring Logic
  // ----------------------------------------------------------

  void apply() {

   if (dirState == 1) {
      ScoringDrive.spin(fwd, SCORE_SPEED, percent);
    } else if (dirState == -1) {
      ScoringDrive.spin(reverse, SCORE_SPEED, percent);
    } else {
      ScoringDrive.stop(coast);
    }
  }
  }

 // namespace Scoring