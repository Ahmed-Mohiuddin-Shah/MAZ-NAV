#include <Arduino.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <AccelStepper.h>
#include <MultiStepper.h>

#define MOTOR_STEPS 200
#define RPM 30
#define MICROSTEPS 1

#define DIR 12
#define STEP 14
#define DIR1 27
#define STEP1 26
#define WHITELED 25
#define RIGHTSENS 33
#define FRONTSENS 32
#define LEFTSENS 35
#define SCL 22
#define SDA 21
#define SERVOPWM 13

AccelStepper stepper1(AccelStepper::DRIVER, STEP, DIR);
AccelStepper stepper2(AccelStepper::DRIVER, STEP1, DIR1);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_MPU6050 mpu;

MultiStepper steppers;

void setup()
{

  // Configure each stepper
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);

  stepper1.setAcceleration(50);
  stepper2.setAcceleration(50);

  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  pinMode(SERVOPWM, OUTPUT);
  pinMode(WHITELED, OUTPUT);
  pinMode(RIGHTSENS, INPUT);
  pinMode(FRONTSENS, INPUT);
  pinMode(LEFTSENS, INPUT);

  mpu.begin(0x68);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop()
{
  long positions[2]; // Array of desired stepper positions

  positions[0] = 200;
  positions[1] = 200;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);

  // Move to a different coordinate
  positions[0] = -200;
  positions[1] = -200;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}