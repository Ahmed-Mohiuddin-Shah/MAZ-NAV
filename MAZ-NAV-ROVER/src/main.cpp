#include <Arduino.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// Bluetooth Includes for ESP32
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "Definitions.h"

AccelStepper stepper1(AccelStepper::DRIVER, STEP, DIR);
AccelStepper stepper2(AccelStepper::DRIVER, STEP1, DIR1);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_MPU6050 mpu;

MultiStepper steppers;

// For Bluetooth functionality
#define SERVICE_UUID "0000180d-0000-1000-8000-00805f9b34fc"
#define CHARACTERISTIC_UUID "00002a37-0000-1000-8000-00805f9b34fc"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Device connected");
  }

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Device disconnected");
  }
};

class MyCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0)
    {
      String inputData, username, password;
      for (int i = 0; i < value.length(); i++)
      {

        inputData = inputData + value[i];
      }
      int spaceIndex = inputData.indexOf(' '); // Find the index of the space character
      if (spaceIndex != -1)
      {                                                 // If space character is found
        username = inputData.substring(0, spaceIndex);  // Extract the first word
        password = inputData.substring(spaceIndex + 1); // Extract the second word
      }
      else
      {
        Serial.println("No space Found in" + inputData);
      }
      Serial.println("Username: " + username);
      Serial.println("Password: " + password);
      Serial.println();

      // Handle the received data, e.g., save WiFi credentials, etc.
    }
  }

  void onRead(BLECharacteristic *pCharacteristic)
  {
    // Implement read operation if needed
  }
};

void setup()
{

  // Create the BLE Device
  BLEDevice::init("MAZ-NAV-ROVER");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  // Add a descriptor for the characteristic
  pCharacteristic->addDescriptor(new BLE2902());


  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

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