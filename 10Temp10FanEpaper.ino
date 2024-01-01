#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>  // 4.2" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
//#include GxEPD_BitmapExamples
#include "ImagesForFC.h"
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Thermistor.h>
#include <NTC_Thermistor.h>

// select one, depending on your CS connection
GxIO_Class io(SPI, /*CS=*/SS, /*DC=*/8, /*RST=*/9);  // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=*/9, /*BUSY=*/7);      // default selection of (9), 7

#define DEMO_DELAY 30
// ################ alle Analogen Sensoren #################
#define Referenzwiderstand 10000 // Widerstandswert des Widerstandes der mit dem NTC in Reihe geschaltet wurde.
#define Nominalwiderstand 10000  // Widerstand des NTC bei Normaltemperatur
#define Nominaltemperatur 25
#define BWert 3950
int Sensor_Pin1 = A0;
int Sensor_Pin2 = A1;
int Sensor_Pin3 = A2;
int Sensor_Pin4 = A3;
int Sensor_Pin5 = A4;
Thermistor* thermistor1 = new NTC_Thermistor(Sensor_Pin1, Referenzwiderstand, Nominalwiderstand, Nominaltemperatur, BWert);
Thermistor* thermistor2 = new NTC_Thermistor(Sensor_Pin2, Referenzwiderstand, Nominalwiderstand, Nominaltemperatur, BWert);
Thermistor* thermistor3 = new NTC_Thermistor(Sensor_Pin3, Referenzwiderstand, Nominalwiderstand, Nominaltemperatur, BWert);
Thermistor* thermistor4 = new NTC_Thermistor(Sensor_Pin4, Referenzwiderstand, Nominalwiderstand, Nominaltemperatur, BWert);
Thermistor* thermistor5 = new NTC_Thermistor(Sensor_Pin5, Referenzwiderstand, Nominalwiderstand, Nominaltemperatur, BWert);
// ############# All Digital Sensoren ####################
#define ONE_WIRE_BUS1 21
#define ONE_WIRE_BUS2 23
#define ONE_WIRE_BUS3 25
#define ONE_WIRE_BUS4 27
#define ONE_WIRE_BUS5 29
OneWire oneWire1(ONE_WIRE_BUS1);
OneWire oneWire2(ONE_WIRE_BUS2);
OneWire oneWire3(ONE_WIRE_BUS3);
OneWire oneWire4(ONE_WIRE_BUS4);
OneWire oneWire5(ONE_WIRE_BUS5);
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);
DallasTemperature sensors4(&oneWire4);
DallasTemperature sensors5(&oneWire5);

// Fan sens (tach) wire connected to digital_8 port gelb
int fanTach1 = 22;
int fanTach2 = 24;
int fanTach3 = 26;
int fanTach4 = 28;
int fanTach5 = 30;
int fanTach6 = 32;
int fanTach7 = 34;
int fanTach8 = 36;
int fanTach9 = 38;
int fanTach10 = 40;
// Fan PWM wire connected to digital_9 port blau
int fanPWM1 = 5;
int fanPWM2 = 4;
int fanPWM3 = 3;
int fanPWM4 = 2;
int fanPWM5 = 1;
int fanPWM6 = 0;
int fanPWM7 = 18;
int fanPWM8 = 19;
int fanPWM9 = 20;
int fanPWM10 = 21;

struct ShowValueParameters {
  uint16_t x, y, w, h, cursor_y;
  const char* value;
};

int showRPM(int Tach) {
    float pulseDuration = 0;
    float frequency = 0;
    float RPMRead = 0;
    int rpm = 0;
    pulseDuration = pulseIn(Tach, HIGH);
    frequency = ((pulseDuration * 4) / 1000);
    RPMRead = (1000 / frequency);
    rpm = (RPMRead * 6);
    rpm = (rpm * 10);
    return rpm;
}

void BuildTable() {
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.fillScreen(GxEPD_WHITE);
  // 10 Fan Controller #######################
  display.setCursor(40, 44);
  display.print("Fan1 :");
  display.setCursor(40, 58);
  display.print("Fan2 :");
  display.setCursor(40, 72);
  display.print("Fan3 :");
  display.setCursor(40, 86);
  display.print("Fan4 :");
  display.setCursor(40, 100);
  display.print("Fan5 :");
  display.setCursor(40, 114);
  display.print("Fan6 :");
  display.setCursor(40, 128);
  display.print("Fan7 :");
  display.setCursor(40, 142);
  display.print("Fan8 :");
  display.setCursor(40, 156);
  display.print("Fan9 :");
  display.setCursor(40, 170);
  display.print("Fan10:");
  // Temp Sensoren########################
  display.setCursor(215, 44);
  display.print("Temp1 :");
  display.setCursor(215, 58);
  display.print("Temp2 :");
  display.setCursor(215, 72);
  display.print("Temp3 :");
  display.setCursor(215, 86);
  display.print("Temp4 :");
  display.setCursor(215, 100);
  display.print("Temp5 :");
  display.setCursor(215, 114);
  display.print("Temp6 :");
  display.setCursor(215, 128);
  display.print("Temp7 :");
  display.setCursor(215, 142);
  display.print("Temp8 :");
  display.setCursor(215, 156);
  display.print("Temp9 :");
  display.setCursor(215, 170);
  display.print("Temp10:");
  // ########### boxen ####################
  display.drawRect(0, 0, 400, 2, GxEPD_BLACK);
  display.drawRect(0, 0, 2, 300, GxEPD_BLACK);
  display.drawRect(0, 298, 400, 2, GxEPD_BLACK);
  display.drawRect(398, 0, 2, 300, GxEPD_BLACK);
  display.drawRect(35, 27, 340, 2, GxEPD_BLACK);
  display.drawRect(35, 27, 2, 150, GxEPD_BLACK);
  display.drawRect(35, 175, 340, 2, GxEPD_BLACK);
  display.drawRect(210, 27, 2, 150, GxEPD_BLACK);
  display.drawRect(370, 27, 2, 150, GxEPD_BLACK);
  display.drawBitmap(Avatar, 358, 258, 40, 40, GxEPD_BLACK, 2);
  display.drawBitmap(RechtsNavi, 318, 258, 40, 40, GxEPD_BLACK, 2);
  display.drawBitmap(LinksNavi, 278, 258, 40, 40, GxEPD_BLACK, 2);
}

const char* convert(double A, float B, int C, int Type){
  char tmp[20] = "";
  switch (Type) {
    case 1:{
      dtostrf(A, 6, 2, tmp);
      break;
    }
    case 2:{
      dtostrf(B, 6, 2, tmp);
      break;
    }
    case 3:{
      itoa(C, tmp, 10);
      break;
    }
    defaulft: {}
  }
  const char* tmp2 = tmp;
  return tmp2;
}
/*
void FanImageRun() {
  display.fillRect(2, 259, 40, 40, GxEPD_WHITE);
  display.drawBitmap(luefter1, 2, 259, 40, 40, GxEPD_BLACK, 2);
  display.fillRect(2, 259, 40, 40, GxEPD_WHITE);
  display.drawBitmap(luefter2, 2, 259, 40, 40, GxEPD_BLACK, 2);
  display.fillRect(2, 259, 40, 40, GxEPD_WHITE);
  display.drawBitmap(luefter3, 2, 259, 40, 40, GxEPD_BLACK, 2);
  display.fillRect(2, 259, 40, 40, GxEPD_WHITE);
  display.drawBitmap(luefter4, 2, 259, 40, 40, GxEPD_BLACK, 2);
};
*/
void UpdateBoxCallback(const void* parameters) {
  const ShowValueParameters* p = reinterpret_cast<const ShowValueParameters*>(parameters);
  display.fillRect(p->x, p->y, p->w, p->h, GxEPD_WHITE);
  display.updateWindow(p->x, p->y, p->w, p->h, true);
  display.setCursor(p->x, p->y + 14);
  display.print(p->value);
}

void showPartialUpdatePaged() {
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  ShowValueParameters valueParameters1 = { 105, 30, 100, 14, 105, convert(0,0,showRPM(fanTach1),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters1.x, valueParameters1.y, valueParameters1.w, valueParameters1.h, &valueParameters1);
  ShowValueParameters valueParameters2 = { 105, 44, 100, 14, 105, convert(0,0,showRPM(fanTach2),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters2.x, valueParameters2.y, valueParameters2.w, valueParameters2.h, &valueParameters2);
  ShowValueParameters valueParameters3 = { 105, 58, 100, 14, 105, convert(0,0,showRPM(fanTach3),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters3.x, valueParameters3.y, valueParameters3.w, valueParameters3.h, &valueParameters3);
  ShowValueParameters valueParameters4 = { 105, 72, 100, 14, 105, convert(0,0,showRPM(fanTach4),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters4.x, valueParameters4.y, valueParameters4.w, valueParameters4.h, &valueParameters4);
  ShowValueParameters valueParameters5 = { 105, 86, 100, 14, 105, convert(0,0,showRPM(fanTach5),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters5.x, valueParameters5.y, valueParameters5.w, valueParameters5.h, &valueParameters5);
  ShowValueParameters valueParameters6 = { 105, 100, 100, 14, 105, convert(0,0,showRPM(fanTach6),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters6.x, valueParameters6.y, valueParameters6.w, valueParameters6.h, &valueParameters6);
  ShowValueParameters valueParameters7 = { 105, 114, 100, 14, 105, convert(0,0,showRPM(fanTach7),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters7.x, valueParameters7.y, valueParameters7.w, valueParameters7.h, &valueParameters7);
  ShowValueParameters valueParameters8 = { 105, 128, 100, 14, 105, convert(0,0,showRPM(fanTach8),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters8.x, valueParameters8.y, valueParameters8.w, valueParameters8.h, &valueParameters8);
  ShowValueParameters valueParameters9 = { 105, 142, 100, 14, 105, convert(0,0,showRPM(fanTach9),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters9.x, valueParameters9.y, valueParameters9.w, valueParameters9.h, &valueParameters9);
  ShowValueParameters valueParameters10 = { 105, 156, 100, 14, 105, convert(0,0,showRPM(fanTach10),3) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters10.x, valueParameters10.y, valueParameters10.w, valueParameters10.h, &valueParameters10);
  
  //double getdegrees = thermistor1->readCelsius();
  ShowValueParameters valueParameters11 = { 290, 30, 75, 14, 105, convert(thermistor1->readCelsius(),0,0,1) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters11.x, valueParameters11.y, valueParameters11.w, valueParameters11.h, &valueParameters11);
  //getdegrees = thermistor2->readCelsius(); 
  ShowValueParameters valueParameters12 = { 290, 44, 75, 14, 105, convert(thermistor2->readCelsius(),0,0,1) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters12.x, valueParameters12.y, valueParameters12.w, valueParameters12.h, &valueParameters12);
  //getdegrees = thermistor3->readCelsius();
  ShowValueParameters valueParameters13 = { 290, 58, 75, 14, 105, convert(thermistor3->readCelsius(),0,0,1) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters13.x, valueParameters13.y, valueParameters13.w, valueParameters13.h, &valueParameters13);
  //getdegrees = thermistor4->readCelsius();
  ShowValueParameters valueParameters14 = { 290, 72, 75, 14, 105, convert(thermistor4->readCelsius(),0,0,1) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters14.x, valueParameters14.y, valueParameters14.w, valueParameters14.h, &valueParameters14);
  //getdegrees = thermistor5->readCelsius();
  ShowValueParameters valueParameters15 = { 290, 86, 75, 14, 105, convert(thermistor5->readCelsius(),0,0,1) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters15.x, valueParameters15.y, valueParameters15.w, valueParameters15.h, &valueParameters15);
  sensors1.requestTemperatures();
  float tempC1 = sensors1.getTempCByIndex(0);
  ShowValueParameters valueParameters16 = { 290, 100, 75, 14, 105, convert(0,tempC1,0,2) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters16.x, valueParameters16.y, valueParameters16.w, valueParameters16.h, &valueParameters16);
  sensors2.requestTemperatures();
  float tempC2 = sensors2.getTempCByIndex(0);
  ShowValueParameters valueParameters17 = { 290, 114, 75, 14, 105, convert(0,tempC2,0,2) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters17.x, valueParameters17.y, valueParameters17.w, valueParameters17.h, &valueParameters17);
  sensors3.requestTemperatures();
  float tempC3 = sensors3.getTempCByIndex(0);
  ShowValueParameters valueParameters18 = { 290, 128, 75, 14, 105, convert(0,tempC3,0,2) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters18.x, valueParameters18.y, valueParameters18.w, valueParameters18.h, &valueParameters18);
  sensors4.requestTemperatures();
  float tempC4 = sensors4.getTempCByIndex(0);
  ShowValueParameters valueParameters19 = { 290, 142, 75, 14, 105, convert(0,tempC4,0,2) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters19.x, valueParameters19.y, valueParameters19.w, valueParameters19.h, &valueParameters19);
  sensors5.requestTemperatures();
  float tempC5 = sensors5.getTempCByIndex(0);
  ShowValueParameters valueParameters20 = { 290, 156, 75, 14, 105, convert(0,tempC5,0,2) };
  display.drawPagedToWindow(UpdateBoxCallback, valueParameters20.x, valueParameters20.y, valueParameters20.w, valueParameters20.h, &valueParameters20);
  //display.powerDown();
}

void setup(void) {
  display.init(115200);  // enable diagnostic output on Serial
  display.drawPagedToWindow(BuildTable, 0, 0, 400, 300);
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  sensors4.begin();
  sensors5.begin();

  pinMode(fanPWM1, OUTPUT);
  pinMode(fanTach1, INPUT);
  digitalWrite(fanPWM1, HIGH);
  pinMode(fanPWM2, OUTPUT);  
  pinMode(fanTach2, INPUT);
  digitalWrite(fanPWM2, HIGH);
  pinMode(fanPWM3, OUTPUT);
  pinMode(fanTach3, INPUT);
  digitalWrite(fanPWM3, HIGH);
  pinMode(fanPWM4, OUTPUT);
  pinMode(fanTach4, INPUT);
  digitalWrite(fanPWM4, HIGH);
  pinMode(fanPWM5, OUTPUT);
  pinMode(fanTach5, INPUT);
  digitalWrite(fanPWM5, HIGH);
  pinMode(fanPWM6, OUTPUT);
  pinMode(fanTach6, INPUT);
  digitalWrite(fanPWM6, HIGH);
  pinMode(fanPWM7, OUTPUT);
  pinMode(fanTach7, INPUT);
  digitalWrite(fanPWM7, HIGH);
  pinMode(fanPWM8, OUTPUT);
  pinMode(fanTach8, INPUT);
  digitalWrite(fanPWM8, HIGH);
  pinMode(fanPWM9, OUTPUT);
  pinMode(fanTach9, INPUT);
  digitalWrite(fanPWM9, HIGH);
  pinMode(fanPWM10, OUTPUT);
  pinMode(fanTach10, INPUT);
  digitalWrite(fanPWM10, HIGH);
  //delay(500);
  //BuildTable();
}

void loop() {
  showPartialUpdatePaged();
  delay(5);
}