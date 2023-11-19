// Include all of Includes for project
#include <Includes.h>

// Misc.
#include <string>

// Headers files
#include <Definitions.h>

// Sensor Global Variables
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_MPU6050 mpu;

// Stepper Drivers Global Variables
AccelStepper stepper1(AccelStepper::DRIVER, STEP, DIR);
AccelStepper stepper2(AccelStepper::DRIVER, STEP1, DIR1);
MultiStepper steppers;

// BLE ESP32 Global Variables
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

long positions[2]; // Array of desired stepper positions

// Custom Server Call Backs
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

// Custom Characteristic Call Backs
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();

  }

  void onRead(BLECharacteristic *pCharacteristic)
  {
    pCharacteristic->setValue("69");
  }
};

// Setup Code
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
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(10);

  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(10);
  

  // Assign to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  // Configuring Inputs and Outputs
  pinMode(SERVOPWM, OUTPUT);      // Servo pin OUT
  pinMode(WHITELED, OUTPUT);      // RGB Sensor LED OUT
  pinMode(RIGHTSENS, INPUT);      // Right Line Sensor Input
  pinMode(FRONTSENS, INPUT);      // Front Line Sensor Input
  pinMode(LEFTSENS, INPUT);       // Left Line Sensor Input

  // Setting up the MPU6050
  mpu.begin(0x68);
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop()
{

}