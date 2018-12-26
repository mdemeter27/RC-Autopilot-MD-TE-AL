#include <Adafruit_Sensor_Set.h>
#include <Adafruit_Simple_AHRS.h>
#include <Madgwick.h>
#include <Mahony.h>


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

int roll;//In degrees(?);
int pitch;
int yaw;


Adafruit_LSM9DS1     lsm(1000);
Adafruit_Simple_AHRS ahrs(&lsm.getAccel(), &lsm.getMag());

/*#define LSM9DS1_SCK A5
  #define LSM9DS1_MISO 12
  #define LSM9DS1_MOSI A4
  #define LSM9DS1_XGCS 6
  #define LSM9DS1_MCS 5*/
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);


void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);

  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}


void accelSetup()
{
  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }

  Serial.println("LSM9DS1 data read demo");

  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
}

void accelLoop()
{
  // lsm.read();  /* ask it to read in the data */

  sensors_vec_t  orientation;

  // Use the simple AHRS function to get the current orientation.
  if (ahrs.getOrientation(&orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
    Serial.print(F("Orientation: "));
    Serial.print((int)orientation.roll);
    roll = (int)orientation.roll;
    Serial.print(F(" "));
    Serial.print((int)orientation.pitch);
    pitch = (int)orientation.pitch;
    Serial.print(F(" "));
    Serial.print((int)orientation.heading);
    Serial.println(F(""));
  }
}

