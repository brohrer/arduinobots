#include <Arduino_LSM6DS3.h>

const float LOOP_DELAY = 2000;  // milliseconds

// measured during the calibration routine in
// https://github.com/brohrer/arduinobots/blob/main/sketches/uno_wifi_rev2_calibration/uno_wifi_rev2_calibration.ino 
const float A_X_OFFSET;
const float A_Y_OFFSET;
const float A_Z_OFFSET;
const float W_X_OFFSET = -0.3;
const float W_Y_OFFSET;
const float W_Z_OFFSET;

17:55:59.046 -> acceleration offsets (g)
17:55:59.078 -> 0.0081	-0.0025	-0.0189
17:55:59.078 -> 
17:55:59.109 -> angular velocity offsets (dps)
17:55:59.142 -> -0.3186	0.0250	-0.3854

18:16:58.672 -> acceleration offsets (g)
18:16:58.704 -> 0.0077	-0.0033	-0.0199
18:16:58.737 -> 
18:16:58.737 -> angular velocity offsets (dps)
18:16:58.768 -> -0.4261	0.0387	-0.4015

18:41:47.970 -> acceleration offsets (g)
18:41:48.003 -> 0.0080	-0.0025	-0.0178
18:41:48.035 -> 
18:41:48.035 -> angular velocity offsets (dps)
18:41:48.067 -> -0.3473	0.0283	-0.3829

19:01:58.858 -> acceleration offsets (g)
19:01:58.890 -> 0.0078	-0.0028	-0.0199
19:01:58.922 -> 
19:01:58.922 -> angular velocity offsets (dps)
19:01:58.953 -> -0.4387	0.0371	-0.3997

20:04:00.152 -> acceleration offsets (g)
20:04:00.152 -> 0.0078	-0.0020	-0.0185
20:04:00.184 -> 
20:04:00.184 -> angular velocity offsets (dps)
20:04:00.216 -> -0.3499	0.0261	-0.3820

acceleration offsets (g)
0.0076	-0.0027	-0.0199

angular velocity offsets (dps)
-0.4307	0.0401	-0.3921

float a_x, a_y, a_z;
float w_x, w_y, w_z;
float t;

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
  
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();  
}

void loop() {
  if (IMU.temperatureAvailable()) {
    IMU.readTemperature(t);
    Serial.println();
    Serial.println("temperature (C)");  
    Serial.println(t);
  }  

  if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(a_x, a_y, a_z);

      Serial.println();
      Serial.println("acceleration (g)");
      Serial.print(a_x + A_X_OFFSET);
      Serial.print('\t');
      Serial.print(a_y + A_Y_OFFSET);
      Serial.print('\t');
      Serial.println(a_z + A_Z_OFFSET);
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(w_x, w_y, w_z);

    Serial.println();
    Serial.println("angular velocity (dps)");
    Serial.print(w_x + W_X_OFFSET);
    Serial.print('\t');
    Serial.print(w_y + W_Y_OFFSET);
    Serial.print('\t');
    Serial.println(w_z + W_Z_OFFSET);
  }

  delay(LOOP_DELAY);
}