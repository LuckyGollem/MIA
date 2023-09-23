//To answer the question the best filter is the low pass filter(LPF)
//and the recommended cutoff frequency is 10Hz

#include <Wire.h>

#define GyroScope 0x68
#define DLPF 0x1A
#define Sensitivity 0x1B
#define PowerSettings 0x6B
#define YawOutput 0x47

int16_t YawReadingNow;
int16_t LastYawReading=0;
float Yaw  = 0;
float Z = 0;
float LastTime;

void StartGyro(){
  //Turn on DLPS(Digital Low Pass Filter) with cutoff frequence 10Hz
  Wire.beginTransmission(GyroScope);
  Wire.write(DLPF);
  Wire.write(0x05);
  Wire.endTransmission();
  //Configurating the gyroscope's sensitivity
  Wire.beginTransmission(GyroScope);
  Wire.write(Sensitivity);
  Wire.write(0x18);
  Wire.endTransmission();
  //Seting the power settings
  Wire.beginTransmission(GyroScope);
  Wire.write(PowerSettings);
  Wire.write(0x00);
  Wire.endTransmission();
}

void setup() {
  
  Wire.begin();//Enter the bus as a master
  

  StartGyro();
  //Getting the starting time
  LastTime = 1.0 * millis() / 1000;

  Serial.begin(9600);
}

void loop() {
  
  //Requesting the Yaw reading
  Wire.beginTransmission(GyroScope);
  Wire.write(YawOutput);
  Wire.endTransmission();
  Wire.requestFrom(GyroScope, 2);
  //Waiting for the bytes
  while(Wire.available() < 2 );
  //Taking the gyroscope reading
  YawReadingNow = Wire.read() << 8  | Wire.read();
  //Changing the format from integer to degree
  YawReadingNow = map(YawReadingNow,-32768,32768,-2000,2000);
  float TimeNow = 1.0 * millis() / 1000;
  float DeltaTime = TimeNow - LastTime;
  float Yaw = YawReadingNow + LastYawReading;
  LastYawReading = YawReadingNow;
  LastTime = TimeNow;

  Z += Yaw * DeltaTime * 0.5;

  while (Z >= 360){;
    Z -= 360;
  }
  while (Z <= -360){
    Z += 360;
  }  
  Serial.println(Z);
}

