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

// Bluetooth BLE Library Includes for ESP32
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>