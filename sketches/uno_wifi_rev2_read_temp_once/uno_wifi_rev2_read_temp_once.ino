/*
  Take a single temperature measurement from Arduino LSM6DS3

  This example reads a temperature value from the LSM6DS3
  sensor and print it to the Serial Monitor.

  Based on SimpleTempSensor.ino
  https://github.com/arduino-libraries/Arduino_LSM6DS3/blob/master/examples/SimpleTempSensor/SimpleTempSensor.ino
  created 15 Mar 2020
  by Alex Hoppe

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Temperature sensor sample rate = ");
  Serial.print(IMU.temperatureSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Temperature reading in degrees C");
  Serial.println("T");
}

void loop() {
  float t;

  if (IMU.temperatureAvailable()) {
    // after IMU.readTemperature() returns, t will contain the temperature reading
    IMU.readTemperature(t);

    Serial.println(t);
    delay(1000000000)
  }
}