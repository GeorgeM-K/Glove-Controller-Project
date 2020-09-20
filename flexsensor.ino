#include <Wire.h>
#include <ArduinoSTL.h>
#include <SparkFunLSM9DS1.h> // SparkFun LSM9DS1 library
#include <SPI.h> // SPI library included for SparkFunLSM9DS1
using namespace std;
const int FLEX_PIN = A0; // Pin connected to voltage divider output
const int FLEX_PIN2 = A1;
const int LED_PIN = 2;
//const int MPU_addr=0x68;
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
LSM9DS1 imu;
#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.74; // Measured voltage of Ardunio 5V line
const float R_DIV = 47000.0; // Measured resistance of 3.3k resistor
const float R_DIV2 = 47160.0;

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 26780.0; // resistance when straight
const float BEND_RESISTANCE = 47500.0; // resistance at 90 deg
const float STRAIGHT_RESISTANCE2 = 25300.0;
const float BEND_RESISTANCE2 = 46000.0;
void setup() 
{
  /*
   Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  */
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  pinMode(FLEX_PIN, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  imu.settings.device.commInterface = IMU_MODE_SPI; // Set mode to SPI
  imu.settings.device.mAddress = 9; // Mag CS pin connected to D9
  imu.settings.device.agAddress = 10; // AG CS pin connected to D10
  imu.settings.accel.scale = 16; // Set accel range to +/-16g
   imu.settings.gyro.scale = 2000; // Set gyro range to +/-2000dps
  imu.settings.mag.scale = 8; // Set mag range to +/-8Gs
  imu.begin(); // Call begin to update the sensor's new settings
  imu.begin();
}

void loop() 
{
  /*// Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();


///////////////////////////////////////////////////////////////////////////////////////////////////
int flexADC2 = analogRead(FLEX_PIN2);
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexR2 = R_DIV2 * (VCC / flexV2 - 1.0);
  Serial.println("Resistance: " + String(flexR2) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle2 = map(flexR2, STRAIGHT_RESISTANCE2, BEND_RESISTANCE2,
                   0, 90.0);
  Serial.println("Bend: " + String(angle2) + " degrees");
  Serial.println();

  if(angle2 <= 45 || angle <= 45){
    blinkInner();
  }
  else if(angle2 > 45 && angle > 45){
    blinkOuter();
  }*/

  accelgyro();
  delay(500);

  
}

void accelgyro(){
  imu.readAccel(); // Update the accelerometer data
  Serial.print(imu.ax); // Print x-axis data
  Serial.print(", ");
  Serial.print(imu.ay); // print y-axis data
  Serial.print(", ");
  Serial.println(imu.az); // print z-axis data
  
  imu.readGyro(); // Update gyroscope data
  Serial.print(imu.calcGyro(imu.gx)); // Print x-axis rotation in DPS
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy)); // Print y-axis rotation in DPS
  Serial.print(", ");
  Serial.println(imu.calcGyro(imu.gz)); // Print z-axis rotation in DPS

  

}

void blinkOuter(){
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}
void blinkInner(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
}
