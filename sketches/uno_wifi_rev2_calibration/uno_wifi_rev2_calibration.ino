#include <Arduino_LSM6DS3.h>

const int CALIBRATION_COUNT = 30000;
const float CALIBRATION_DELAY = 10;  // milliseconds
const float LOOP_DELAY = 2000000;  // milliseconds
const float LOCAL_GRAVITY = 9.8039 / 9.80665;  // g's
const int OFFSET_PRECISION = 4;  // The number of decimal places

float a_x, a_y, a_z;
float w_x, w_y, w_z;
float a_x_offset, a_y_offset, a_z_offset;
float w_x_offset, w_y_offset, w_z_offset;
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
  
  //Zero the gyroscope and accelerometers
  Serial.println("Let the board lie flat and still for a couple of minutes");
  float a_x_sum = 0.0, a_y_sum = 0.0, a_z_sum = 0.0;
  float w_x_sum = 0.0, w_y_sum = 0.0, w_z_sum = 0.0;
  int acc_count = 0, gyro_count = 0;
  bool done = false;
  while (!done) {
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(a_x, a_y, a_z);
        a_x_sum += a_x;
        a_y_sum += a_y;
        a_z_sum += a_z;
        acc_count ++;
    }
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(w_x, w_y, w_z);
        w_x_sum += w_x;
        w_y_sum += w_y;
        w_z_sum += w_z;
        gyro_count ++;
    }

    Serial.print(acc_count);
    Serial.print("   ");
    Serial.println(1000 * (a_z - 1.01), 2);
    if (acc_count >= CALIBRATION_COUNT and gyro_count >= CALIBRATION_COUNT) {
      done = true;
    }
    delay(CALIBRATION_DELAY);
  }
  a_x_offset = -a_x_sum / acc_count;    
  a_y_offset = -a_y_sum / acc_count;
  a_z_offset = -a_z_sum / acc_count + LOCAL_GRAVITY;

  w_x_offset = -w_x_sum / gyro_count;    
  w_y_offset = -w_y_sum / gyro_count;
  w_z_offset = -w_z_sum / gyro_count;
}

void loop() {
  Serial.println();
  Serial.println("acceleration offsets (g)");
  Serial.print(a_x_offset, OFFSET_PRECISION);
  Serial.print('\t');
  Serial.print(a_y_offset, OFFSET_PRECISION);
  Serial.print('\t');
  Serial.println(a_z_offset, OFFSET_PRECISION);

  Serial.println();
  Serial.println("angular velocity offsets (dps)");
  Serial.print(w_x_offset, OFFSET_PRECISION);
  Serial.print('\t');
  Serial.print(w_y_offset, OFFSET_PRECISION);
  Serial.print('\t');
  Serial.println(w_z_offset, OFFSET_PRECISION);

  delay(LOOP_DELAY);
}