#include "JVRTC.h"
#include <microDS3231.h>
MicroDS3231 rtc;

JVRTC::JVRTC() {
}


void JVRTC::initRTC() {
  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
  }
}

void JVRTC::set(int8_t seconds, int8_t minutes, int8_t hours, int8_t date, int8_t month, int16_t year) {
  rtc.setTime(seconds, minutes, hours, date, month, year);
}

String JVRTC::getTime() {
  return rtc.getTimeString();
}

String JVRTC::getDate() {
  return rtc.getDateString();
}

String JVRTC::getFileNameDate() {
  String result = "/";
  result += rtc.getDate();
  result += "_";
  result += rtc.getMonth();
  result += "_";
  result += rtc.getYear();
  result += "_";
  result += rtc.getHours();
  result += "_";
  result += rtc.getMinutes();
  result += "_";
  result += rtc.getSeconds();
  result += ".csv";
  return result;
}