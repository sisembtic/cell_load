#include "JVLCD.h"

#include <Wire.h>
#include "SH1106Wire.h"

SH1106Wire display(0x3c, SDA, SCL);


JVLCD::JVLCD() {
}


void JVLCD::initLCD() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.clear();
  display.display();
}

void JVLCD::lcdHome() {
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 10, "SISEMB");
  display.drawString(64, 20, "TIC- ELECTRÓNICA");
  display.drawString(64, 30, "2023"); 
  display.display();
  delay(2000);
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 5, "SISTEMA DE MEDICIÓN");
  display.drawString(64, 15, "CELDAS DE CARGA");    
  display.drawString(64, 40, "Presione el botón para");  
  display.drawString(64, 50, "configurar por puerto serial");  
  display.display();
}

void JVLCD::lcdCalibrate() {
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, "Calibrando"); 
  display.setFont(ArialMT_Plain_10);  
  display.drawString(64, 35, "Use Puerto Serial PC"); 
  display.drawString(64, 45, "115200 Bd"); 
  display.display();
}


void JVLCD::lcdLine(String time, String m1, String m2, String m3, String m4, String m5, String m6, String m7, String m8) {
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, time);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 12, m1);
  display.drawString(0, 22, m2);
  display.drawString(0, 32, m3);
  display.drawString(0, 42, m4);
  display.drawString(0, 52, m5);
  display.drawString(64, 12, m6);
  display.drawString(64, 22, m7);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(115, 35, m8);
  display.setFont(ArialMT_Plain_10);
  if (m8 == "Start")
    display.drawString(128, 52, "No retirar SD");
  else
    display.drawString(128, 52, "Retirar SD");
  display.display();
}