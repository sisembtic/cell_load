#ifndef JVSD_H
#define JVSD_H

#include "Arduino.h"


class JVSD {
public:
  JVSD();
  void initSD();
  void appendFile(const char *path, const char *message);
  String readFile(const char *path);
  void deleteFile(const char *path);

private:
};

#endif