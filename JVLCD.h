#ifndef JVLCD_H
#define JVLCD_H

#include "Arduino.h"


class JVLCD {
public:
  JVLCD();
  void initLCD();
  void lcdHome();
  void lcdCalibrate();
  void lcdLine(String time, String m1, String m2, String m3, String m4, String m5, String m6, String m7, String m8);
private:
};

#endif