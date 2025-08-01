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

float temp_filtered = 0.0;
float adaptation_rate = 0.10;

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
}

void loop() {
  float temp_raw, temp_corrected, temp_f;
  float sensitivity_correction;
  unsigned long milliseconds_between_measurements = 1000ul * 60;

  if (IMU.temperatureAvailable()) {
    // after IMU.readTemperature() returns, t will contain the temperature reading
    IMU.readTemperature(temp_raw);

    /*
    Noteworthy quirk: There are 2 different variants of the IMU chip used in these boards,
    and they have different ways of computing temperature. As luck would have it,
    the chip on my board is different than the one represented in the library.
    The tiny "S4" printed on the chip body indicates that it should have a temperature
    sensitivity of 256, rather than 16.

    temp_c = reported_temp / temp_sensitivity + 25.0
    
    Correction included below.
    https://github.com/arduino-libraries/Arduino_LSM6DS3/pull/12#issuecomment-1844884777
    */
    sensitivity_correction = 16.0 / 256.0;
    temp_corrected = (temp_raw - 25.0) * sensitivity_correction + 25.0;
    temp_filtered = (1.0 - adaptation_rate) * temp_filtered + adaptation_rate * temp_corrected;
    temp_f = temp_filtered * 9.0 / 5.0 + 32.0;
    

    Serial.println(temp_filtered, 3);
    //Serial.print(" (");
    //Serial.print(temp_f, 3);
    //Serial.println(")");
    delay(milliseconds_between_measurements);
  }
}