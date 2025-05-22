#include <Arduino.h>
#include <VL53L0X.h>

VL53L0X distanceSensor;
float vzdialenost;
unsigned long cas;
bool bezi = false;
bool vypis = false;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Wire.begin();
  distanceSensor.setTimeout(100);
  if (!distanceSensor.init())
  {
    Serial.println("Failed to detect and initialize sensor VL53L0X !");
    while (1)
      ;
  }
  Serial.println("Sensor VL53L0X online!");
}

void loop() {
  vzdialenost = (float)distanceSensor.readRangeSingleMillimeters();
  if(vzdialenost>0 && vzdialenost<300 && !vypis) {
    Serial.printf("---------------- Rychlost: %lu\n",millis() - cas);
    vypis = true;
  }
  if(vzdialenost>0 && vzdialenost<400 && !bezi) {
    bezi = true;
    cas=millis();
  }
  if(vzdialenost>400 && vzdialenost<600) {
    bezi = false;
    vypis = false;
  }
  //delay(10);// put your main code here, to run repeatedly:
  //Serial.printf("b:%d v:%d ", bezi, vypis);
  //Serial.println((float)distanceSensor.readRangeSingleMillimeters());
}
