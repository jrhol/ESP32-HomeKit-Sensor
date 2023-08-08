#include "HomeSpan.h"


#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 14
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

#include "DEV_TemperatureSens.h"
#include "DEV_HumiditySens.h"

void setup()
{

  Serial.begin(115200);
  homeSpan.setPairingCode("35724499");

  homeSpan.begin(Category::Sensors, "Bedroom Air Sensor");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
    new TempSensor();
    new HumSensor();
}

void loop()
{

  homeSpan.poll();
}

