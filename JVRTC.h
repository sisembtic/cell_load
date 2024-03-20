#ifndef JVRTC_H
#define JVRTC_H

#include "Arduino.h"


class JVRTC {
public:
  JVRTC();
  void initRTC();
  void set(int8_t seconds, int8_t minutes, int8_t hours, int8_t date, int8_t month, int16_t year);
  String getTime();
  String getDate();
  String getFileNameDate();
private:
};

#endif