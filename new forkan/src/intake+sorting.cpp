#include "robot-config.h"

using namespace vex;

// ============================================================
// Intake / Sorting Settings (file-local)
// ============================================================

  // هنا تختار "لون فريقك" اللي تبغى تحتفظ فيه
  // مثال: KEEP MY COLOR = 2 (blue)  1 (red)
  // static const int MY_COLOR = 1; //1 (red)
 static const int MY_COLOR = 2; //2 (blue) 
static const int INTAKE_SPEED_MAIN  = 100;
// ============================================================
// Intake Namespace
// ============================================================
namespace Intake {

  static int intakeState = 0;
  void setState(int state) {
    intakeState = state;
  }
  int getState() {
    return intakeState;
  }
  // ------------------------------------------------------------
  // Internal Color Classification
  // ------------------------------------------------------------
  static int classifyColor() {
  opticalSensor.setLightPower(100, percent);
  opticalSensor.setLight(ledState::on);

    int h1 = opticalSensor.hue(); wait(7, msec);
    int h2 = opticalSensor.hue(); wait(7, msec);
    int h3 = opticalSensor.hue();
    int hue = (h1 + h2 + h3) / 3;

    bool isBlue = (hue >= 190 && hue <= 270);
    bool isRed  = (hue <= 20 || hue >= 345);
    if (isRed)  return 1;
    if (isBlue) return 2;
    return 0;  // unknown
  }
  // ------------------------------------------------------------
  // Main Intake + Sorting Logic
  // ------------------------------------------------------------
  void apply() {
  // STOP
  if (intakeState == 0) {
    intakeMain.stop(coast);
    intakeOpp.stop(coast);
    // sorterMotor.stop(coast);  // إذا ما تبغاه علّقه
    return;
  }
  // تشغيل الانتيك حسب حالتك (in/out)
  if (intakeState == 1) {
    intakeMain.spin(fwd, INTAKE_SPEED_MAIN, percent);
    intakeOpp.spin(fwd, INTAKE_SPEED_MAIN, percent);

  } else if (intakeState == -1) {
    intakeMain.spin(reverse, INTAKE_SPEED_MAIN, percent);
    intakeOpp.spin(reverse, INTAKE_SPEED_MAIN, percent);
    return; 
  }
  // ---- Color sorting دائماً ----
  int color = classifyColor(); // 1=red, 2=blue, 0=unknown

  // إذا اللون 0: خله طبيعي ولا تسوي reverse
  if (color == 0) return;
  
  if (color != MY_COLOR) {
    sorterMotor.spin(reverse, INTAKE_SPEED_MAIN, percent);  
    wait(200, msec);
    sorterMotor.spin(fwd, INTAKE_SPEED_MAIN, percent);
  }
}

} 