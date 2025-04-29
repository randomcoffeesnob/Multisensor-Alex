#include <Arduino.h>
#include "DFRobot_EnvironmentalSensor.h"
#include <TFT_eSPI.h>

#define TFT_BL 38       // Backlight control pin
#define PIN_POWER_ON 15 // LCD and battery Power Enable

DFRobot_EnvironmentalSensor environment(/*addr =*/SEN050X_DEFAULT_DEVICE_ADDRESS, /*s =*/&Serial1);
TFT_eSPI tft = TFT_eSPI();
void setup()
{

  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 3, 2);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Turn on the backlight
  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);

  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK); 

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  while (environment.begin() != 0)
  {
    Serial.println(" Sensor initialize failed!!");
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Initializing Sensor", 10, 10, 1);
    delay(1000);
  }
  Serial.println("Sensor  initialize success!!");
  tft.fillScreen(TFT_BLACK);

  tft.drawString("Environmental Sensor", 10, 10, 1);
}

void loop()
{
  float uvIntensity = environment.getUltravioletIntensity();
  if (uvIntensity < 0) {
    uvIntensity = 0;
  }

  tft.fillRect(10, 30, 320, 240, TFT_BLACK);
  tft.drawString(String(environment.getTemperature(TEMP_C)-3, 1) + "C", 10, 30, 1);
  tft.drawString(String(environment.getHumidity(), 1) + "%", 10, 50, 1);
  tft.drawString(String(uvIntensity, 1) + "mw/cm2 - UVI: " + String(abs(uvIntensity / 400), 0), 10, 70, 1);
  tft.drawString(String(environment.getLuminousIntensity(), 1) + "lx", 10, 90, 1);
  tft.drawString(String(environment.getAtmospherePressure(HPA)) + "hpa", 10, 110, 1);
  delay(2000);

}
