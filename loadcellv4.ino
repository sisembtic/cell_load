#include "HX711.h"
#include <Preferences.h>
#include "JVSD.h"
#include "JVLCD.h"
#include "JVRTC.h"

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;
TaskHandle_t Task5;
TaskHandle_t Task6;
TaskHandle_t Task7;
TaskHandle_t Task8;

const int DOUT_CELL1 = 17;
const int SCK_CELL1 = 16;
const int DOUT_CELL2 = 34;
const int SCK_CELL2 = 26;
const int DOUT_CELL3 = 35;
const int SCK_CELL3 = 25;
const int DOUT_CELL4 = 32;
const int SCK_CELL4 = 27;
const int DOUT_CELL5 = 33;
const int SCK_CELL5 = 14;
const int DOUT_CELL6 = 39;
const int SCK_CELL6 = 4;
const int DOUT_CELL7 = 36;
const int SCK_CELL7 = 15;


HX711 scale1, scale2, scale3, scale4, scale5, scale6, scale7;
Preferences preferences;

JVSD SDI;
JVLCD LCDI;
JVRTC RTCI;

float taraCell1 = 0;
float taraCell2 = 0;
float taraCell3 = 0;
float taraCell4 = 0;
float taraCell5 = 0;
float taraCell6 = 0;
float taraCell7 = 0;

float loadCell1 = 0.0, loadCell2 = 0.0, loadCell3 = 0.0, loadCell4 = 0.0, loadCell5 = 0.0, loadCell6 = 0.0, loadCell7 = 0.0;


bool endCell1 = false;
bool endCell2 = false;
bool endCell3 = false;
bool endCell4 = false;
bool endCell5 = false;
bool endCell6 = false;
bool endCell7 = false;
bool start = false;

String loadCellsValues, fileName;

int buttonState = 0;
bool actionState = false;

unsigned long startTime, endTime, elapsedTime;
byte samples;

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT);
  pinMode(2, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  LCDI.initLCD();
  RTCI.initRTC();
  SDI.initSD();
  LCDI.lcdHome();
  preferences.begin("app", false);

  Serial.println("Initializing the scale");
  scale1.begin(DOUT_CELL1, SCK_CELL1);
  scale2.begin(DOUT_CELL2, SCK_CELL2);
  scale3.begin(DOUT_CELL3, SCK_CELL3);
  scale4.begin(DOUT_CELL4, SCK_CELL4);
  scale5.begin(DOUT_CELL5, SCK_CELL5);
  scale6.begin(DOUT_CELL6, SCK_CELL6);
  scale7.begin(DOUT_CELL7, SCK_CELL7);
  delay(500);
  for (int x = 0; x < 10; x++) {
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
  }

  if (!digitalRead(0)) {
    LCDI.lcdCalibrate();
    menu();
  }

  samples = preferences.getFloat("samples", 1);
  scale1.set_scale(preferences.getFloat("factor1", 0));
  scale2.set_scale(preferences.getFloat("factor2", 0));
  scale3.set_scale(preferences.getFloat("factor3", 0));
  scale4.set_scale(preferences.getFloat("factor4", 0));
  scale5.set_scale(preferences.getFloat("factor5", 0));
  scale6.set_scale(preferences.getFloat("factor6", 0));
  scale7.set_scale(preferences.getFloat("factor7", 0));
  scale1.tare();
  scale2.tare();
  scale3.tare();
  scale4.tare();
  scale5.tare();
  scale6.tare();
  scale7.tare();

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task3code, "Task3", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task4code, "Task4", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task5code, "Task5", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task6code, "Task6", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task7code, "Task7", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task8code, "Task8", 10000, NULL, 1, NULL, 0);
}

void loop() {
  String time = RTCI.getDate() + " " + RTCI.getTime();
  String state;
  if (buttonState == 0)
    state = "(Kg) Stop";
  if (buttonState == 1)
    state = "(Kg) Tara";
  if (buttonState == 2)
    state = "(Kg) Start";
  LCDI.lcdLine(time, "c1: " + String((loadCell1 - taraCell1)/1000.0, 2), "c2: " + String((loadCell2 - taraCell2)/1000.0, 2), "c3: " + String((loadCell3 - taraCell3)/1000.0, 2), "c4: " + String((loadCell4 - taraCell4)/1000.0, 2), "c5: " + String((loadCell5 - taraCell5)/1000.0, 2), "c6: " + String((loadCell6 - taraCell6)/1000.0, 2), "c7: " + String((loadCell7 - taraCell7)/1000.0, 2), state);
  delay(1000);
}

void Task1code(void* parameter) {
  Serial.println("Task1 Cell1");
  for (;;) {
    if (!endCell1) {
      loadCell1 = scale1.get_units(samples);
      endCell1 = true;
    }
    vTaskDelay(1);
  }
}

void Task2code(void* parameter) {
  Serial.println("Task2 Cell2");
  for (;;) {
    if (!endCell2) {
      loadCell2 = scale2.get_units(samples);
      endCell2 = true;
    }
    vTaskDelay(1);
  }
}

void Task3code(void* parameter) {
  Serial.println("Task3 Cell3");
  for (;;) {
    if (!endCell3) {
      loadCell3 = scale3.get_units(samples);
      endCell3 = true;
    }
    vTaskDelay(1);
  }
}

void Task4code(void* parameter) {
  Serial.println("Task4 Cell4");
  for (;;) {
    if (!endCell4) {
      loadCell4 = scale4.get_units(samples);
      endCell4 = true;
    }
    vTaskDelay(1);
  }
}

void Task5code(void* parameter) {
  Serial.println("Task5 Cell5");
  for (;;) {
    if (!endCell5) {
      loadCell5 = scale5.get_units(samples);
      endCell5 = true;
    }
    vTaskDelay(1);
  }
}

void Task6code(void* parameter) {
  Serial.println("Task6 Cell6");
  for (;;) {
    if (!endCell6) {
      loadCell6 = scale6.get_units(samples);
      endCell6 = true;
    }
    vTaskDelay(1);
  }
}

void Task7code(void* parameter) {
  Serial.println("Task7 Cell7");
  for (;;) {
    if (!endCell7) {
      loadCell7 = scale7.get_units(samples);
      endCell7 = true;
    }
    vTaskDelay(1);
  }
}

void Task8code(void* parameter) {
  Serial.println("Task6 Capture");
  for (;;) {
    if (!start) {
      loadCell1 = 0.0;
      loadCell2 = 0.0;
      loadCell3 = 0.0;
      loadCell4 = 0.0;
      loadCell5 = 0.0;
      loadCell6 = 0.0;
      loadCell7 = 0.0;
    }
    if (endCell1 && endCell2 && endCell3 && endCell4 && endCell5 && endCell6 && endCell7 && start) {
      endTime = micros();
      elapsedTime = endTime - startTime;
      loadCellsValues = String(elapsedTime) + "," + String(loadCell1 - taraCell1, 1) + "," + String(loadCell2 - taraCell2, 1) + "," + String(loadCell3 - taraCell3, 1) + "," + String(loadCell4 - taraCell4, 1) + "," + String(loadCell5 - taraCell5, 1) + "," + String(loadCell6 - taraCell6, 1) + "," + String(loadCell7 - taraCell7, 1) + "\n";

      SDI.appendFile(fileName.c_str(), loadCellsValues.c_str());
      endCell1 = false;
      endCell2 = false;
      endCell3 = false;
      endCell4 = false;
      endCell5 = false;
      endCell6 = false;
      endCell7 = false;
    }

    if (!digitalRead(0)) {
      buttonState++;
      if (buttonState == 3)
        buttonState = 0;
      actionState = true;
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    if (buttonState == 0 && actionState == true) {
      start = false;
      // loadCell1 = 0.0;
      // loadCell2 = 0.0;
      // loadCell3 = 0.0;
      // loadCell4 = 0.0;
      // loadCell5 = 0.0;
      // loadCell6 = 0.0;
      // loadCell7 = 0.0;
    }

    if (buttonState == 1 && actionState == true) {
      taraCell1 = scale1.get_units(10);
      taraCell2 = scale2.get_units(10);
      taraCell3 = scale3.get_units(10);
      taraCell4 = scale4.get_units(10);
      taraCell5 = scale5.get_units(10);
      taraCell6 = scale6.get_units(10);
      taraCell7 = scale7.get_units(10);
      actionState = false;
    }

    if (buttonState == 2 && actionState == true) {
      SDI.initSD();
      fileName = RTCI.getFileNameDate();
      SDI.appendFile(fileName.c_str(), "Time(us),LoadCell1,LoadCell2,LoadCell3,LoadCell4,LoadCell5,LoadCell6,LoadCell7\n");
      start = true;
      startTime = micros();
      actionState = false;
    }   

    vTaskDelay(1);
  }
}

void menu() {
  Serial.println("MENU DE OPCIONES");
  Serial.println("0. Calibrar todo");
  Serial.println("1. Calibrar celda de carga 1");
  Serial.println("2. Calibrar celda de carga 2");
  Serial.println("3. Calibrar celda de carga 3");
  Serial.println("4. Calibrar celda de carga 4");
  Serial.println("5. Calibrar celda de carga 5");
  Serial.println("6. Calibrar celda de carga 6");
  Serial.println("7. Calibrar celda de carga 7");
  Serial.println("8. Muestras por captura");
  Serial.println("9. Configurar hora y fecha");
  Serial.println("Seleccione una opción: ");
  int opcion = inputInt();
  if (opcion < 0 || opcion > 9) {
    Serial.println("Opción no válida");
    Serial.println("");
    menu();
  } else {
    switch (opcion) {
      case 0:
        calibrateAll();
        break;
      case 1:
        calibrate1();
        break;
      case 2:
        calibrate2();
        break;
      case 3:
        calibrate3();
        break;
      case 4:
        calibrate4();
        break;
      case 5:
        calibrate5();
        break;
      case 6:
        calibrate6();
        break;
      case 7:
        calibrate7();
        break;
      case 8:
        captures();
        break;
      case 9:
        setRTC();
        break;
    }
  }
}

void calibrate1() {
  scale1.set_scale();
  scale1.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 1).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value1 = scale1.get_units(10);
  float factor1 = value1 / knownWeight;
  preferences.putFloat("factor1", factor1);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale1.set_scale(factor1);
  scale1.tare();
  Serial.print("Calibración completa. LoadCell 1");
}


void calibrate2() {
  scale2.set_scale();
  scale2.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 2).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value2 = scale2.get_units(10);
  float factor2 = value2 / knownWeight;
  preferences.putFloat("factor2", factor2);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale2.set_scale(factor2);
  scale2.tare();
  Serial.print("Calibración completa. LoadCell 2");
}


void calibrate3() {
  scale3.set_scale();
  scale3.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 3).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value3 = scale3.get_units(10);
  float factor3 = value3 / knownWeight;
  preferences.putFloat("factor3", factor3);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale3.set_scale(factor3);
  scale3.tare();
  Serial.print("Calibración completa. LoadCell 3");
}

void calibrate4() {
  scale4.set_scale();
  scale4.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 4).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value4 = scale4.get_units(10);
  float factor4 = value4 / knownWeight;
  preferences.putFloat("factor4", factor4);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale4.set_scale(factor4);
  scale4.tare();
  Serial.print("Calibración completa. LoadCell 4");
}

void calibrate5() {
  scale5.set_scale();
  scale5.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 5).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value5 = scale5.get_units(10);
  float factor5 = value5 / knownWeight;
  preferences.putFloat("factor5", factor5);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale5.set_scale(factor5);
  scale5.tare();
  Serial.print("Calibración completa. LoadCell 5");
}

void calibrate6() {
  scale6.set_scale();
  scale6.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 6).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value6 = scale6.get_units(10);
  float factor6 = value6 / knownWeight;
  preferences.putFloat("factor6", factor6);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale6.set_scale(factor6);
  scale6.tare();
  Serial.print("Calibración completa. LoadCell 6");
}

void calibrate7() {
  scale7.set_scale();
  scale7.tare();
  Serial.println("Coloque un peso de referencia conocido (loadcell 7).");
  pressKeyEnter();
  Serial.print("Ingresa el peso de referencia en gramos:");
  float knownWeight = inputFloat();
  float value7 = scale7.get_units(10);
  float factor7 = value7 / knownWeight;
  preferences.putFloat("factor7", factor7);
  Serial.println("Retire el peso de referencia de la balanza.");
  Serial.print("");
  pressKeyEnter();
  scale7.set_scale(factor7);
  scale7.tare();
  Serial.print("Calibración completa. LoadCell 7");
}

void calibrateAll() {
  calibrate1();
  calibrate2();
  calibrate3();
  calibrate4();
  calibrate5();
  calibrate6();
  calibrate7();
  Serial.print("Calibración completa");
}

void captures() {
  Serial.print("Ingresa la cantidad de muestras por captura:");
  float numberOfSamples = inputFloat();
  preferences.putFloat("samples", numberOfSamples);
  Serial.print("Guardado.");
}

void setRTC(void) {
  int8_t seconds, minutes, hours, date, month;
  int16_t year;
  Serial.println("Por favor, ingrese el día del mes (1-31):");
  date = inputInt();
  Serial.println("Por favor, ingrese el mes, 1 para Enero (1-12):");
  month = inputInt();
  Serial.println("Por favor, ingrese el año (YYYY):");
  year = inputInt();
  Serial.println("Por favor, ingrese la hora (0-23):");
  hours = inputInt();
  Serial.println("Por favor, ingrese los minutos (0-59):");
  minutes = inputInt();
  Serial.println("Por favor, ingrese los segundos (0-59):");
  seconds = inputInt();
  RTCI.set(seconds, minutes, hours, date, month, year);
}

float inputFloat() {
  float value;
  while (true) {
    if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      float val = strtof(data.c_str(), NULL);
      if (val != 0.0) {
        value = data.toFloat();
      } else {
        value = 0.0;
      }
      Serial.println(value, 2);
      break;
    }
  }
  return value;
}

int inputInt() {
  int value;
  while (true) {
    if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      int val = atoi(data.c_str());
      if (val != 0) {
        value = data.toInt();
      } else {
        value = 0;
      }
      Serial.println(value);
      break;
    }
  }
  return value;
}

void pressKeyEnter() {
  Serial.println("Presione la tecla enter para continuar.");
  while (true) {
    if (Serial.available() > 0) {
      Serial.readStringUntil('\r');
      break;
    }
  }
}