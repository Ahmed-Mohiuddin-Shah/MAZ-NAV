// Basic Library Include for Arduino Framework
#include <Arduino.h>

// Library Includes for Sensors and I2C
// TCS34725 Color Sensor
// MPU 6050 Gyroscope and Accelerometer
#include "Adafruit_TCS34725.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Library Includes for Stepper Drivers
#include <AccelStepper.h>
#include <MultiStepper.h>

#include "BluetoothSerial.h"

// Misc.
#include <string>

// Headers files
#include <macros.h>

// Sensor Global Variables
Adafruit_TCS34725 tcsColorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_MPU6050 mpuGyroModule;

// Stepper Drivers Global Variables
AccelStepper stepper1(AccelStepper::DRIVER, STEP, MOTOR_DIR_1);
AccelStepper stepper2(AccelStepper::DRIVER, STEP1, MOTOR_DIR_2);
MultiStepper steppers;

long positions[2]; // Array of desired stepper positions
BluetoothSerial SerialBT;

// Setup Code
void setup()
{
  Serial.begin(9600);
  SerialBT.begin("MAZ-NAV"); // Bluetooth device name
  // Configure each stepper
  stepper1.setMaxSpeed(MOTOR_MAX_SPEED);
  stepper1.setAcceleration(MOTOR_ACCELERATION);

  stepper2.setMaxSpeed(MOTOR_MAX_SPEED);
  stepper2.setAcceleration(MOTOR_ACCELERATION);

  // Assign to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  // Configuring Inputs and Outputs
  pinMode(SERVOPWM, OUTPUT); // Servo pin OUT
  pinMode(WHITELED, OUTPUT); // RGB Sensor LED OUT
  pinMode(RIGHTSENS, INPUT); // Right Line Sensor Input
  pinMode(FRONTSENS, INPUT); // Front Line Sensor Input
  pinMode(LEFTSENS, INPUT);  // Left Line Sensor Input

  // Setting up the MPU6050
  mpuGyroModule.begin(0x68);
  mpuGyroModule.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpuGyroModule.setGyroRange(MPU6050_RANGE_500_DEG);
  mpuGyroModule.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop()
{
  String inputFromOtherSide;
  if (SerialBT.available())
  {
    inputFromOtherSide = SerialBT.readString();
    SerialBT.println("You had entered: ");
    SerialBT.println(inputFromOtherSide);
  }

  // positions[0] = 200;
  // positions[1] = 200;
  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();

  // delay(500);

  // positions[0] = -200;
  // positions[1] = -200;
  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();
}