// Basic Library Include for Arduino Framework
#include <Arduino.h>

// Library Includes for Sensors and I2C
// TCS34725 Color Sensor
// MPU 6050 Gyroscope and Accelerometer
#include <SPI.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_Sensor.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

// Library Includes for Stepper Drivers
#include <AccelStepper.h>
#include <MultiStepper.h>

#include "BluetoothSerial.h"

// Misc.
#include <string>
#include <vector>
#include <sstream>

// Headers files
#include <macros.h>

// Sensor Global Variables
Adafruit_TCS34725 tcsColorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
MPU6050 mpuGyroModule(Wire);

// Stepper Drivers Global Variables
AccelStepper stepper1(AccelStepper::DRIVER, STEP, MOTOR_DIR_1);
AccelStepper stepper2(AccelStepper::DRIVER, STEP1, MOTOR_DIR_2);
MultiStepper steppers;

long positions[2] = {3350, 3350}; // Array of desired stepper positions

BluetoothSerial SerialBT;

// Setup Code
void setup()
{
  Wire.begin();
  mpuGyroModule.begin();
  mpuGyroModule.calcGyroOffsets(true);
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
}

String inputFromOtherSide;

void loop()
{
  if (SerialBT.available())
  {
    inputFromOtherSide = SerialBT.readString();
    std::vector<std::string> moves;

    std::string word;
    std::stringstream stream(inputFromOtherSide.c_str());

    while (stream >> word)
    {
      moves.push_back(word);
    }

    for (auto move : moves)
    {
      if (move.compare("init") == 0)
      {
        int counter = 0;
        initOptions option;
        String s;
        for (auto move : moves)
        {
          if (move.compare("init") == 0)
          {
            continue;
          }
          if (counter % 2)
          {
            s = String(move.c_str());
            switch (option)
            {
            case ACCELERATION:
              stepper1.setAcceleration(s.toInt());
              stepper2.setAcceleration(s.toInt());
              break;
            case MAX_SPEED:
              stepper1.setMaxSpeed(s.toInt());
              stepper2.setMaxSpeed(s.toInt());
              break;
            case POSITIONS:
              positions[0] = s.toInt();
              positions[1] = s.toInt();
              break;
            case STEPS_PER_90:
              STEPS_FOR_90 = s.toInt();
              break;
            default:
              break;
            }
          }
          else
          {
            if (move == "-accel")
            {
              option = ACCELERATION;
            }
            else if (move == "-mSpeed")
            {
              option = MAX_SPEED;
            }
            else if (move == "-pos")
            {
              option = POSITIONS;
            }
            else if (move == "-s90")
            {
              option = STEPS_PER_90;
            }
          }
        }
      }
      else if (move.compare("right") == 0)
      {
        Serial.println("right");
        stepper1.setCurrentPosition(MOTOR_STEPS + STEPS_FOR_90);
        stepper2.setCurrentPosition(MOTOR_STEPS - STEPS_FOR_90);
        steppers.moveTo(positions);
        steppers.runSpeedToPosition();
      }
      else if (move.compare("left") == 0)
      {
        Serial.println("left");
        stepper1.setCurrentPosition(MOTOR_STEPS - STEPS_FOR_90);
        stepper2.setCurrentPosition(MOTOR_STEPS + STEPS_FOR_90);
        steppers.moveTo(positions);
        steppers.runSpeedToPosition();
      }
      else if (move.compare("move") == 0)
      {
        stepper1.setCurrentPosition(0);
        stepper2.setCurrentPosition(0);
        steppers.moveTo(positions);
        steppers.runSpeedToPosition();
      }
    }

    SerialBT.print("Move Done");
  }
}