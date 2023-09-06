//To answer the question the best filter is the low pass filter(LPF)
//and the recommended cutoff frequency is 10Hz
#include <Wire.h>
int16_t GyroYaw;
void setup() {
  Wire.begin();//Enter the bus as a master
  Serial.begin(9600);
}

void loop() {
  //Turn on LPS with cutoff frequence 10Hz
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  //Configurating the gyroscope's sensitivity
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x18);
  Wire.endTransmission();
  //Seting the power settings
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  //Requesting the Yaw reading
  Wire.requestFrom(0x68, 2);
  GyroYaw = Wire.read() << 8  | Wire.read();
  Serial.println(GyroYaw);
  delay(400);
}
