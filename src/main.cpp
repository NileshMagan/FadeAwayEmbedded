#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

BLEService imuService("19b10010-e8f2-537e-4f6c-d104768a1214");                                        // Define a custom BLE service
BLECharacteristic imuCharacteristic("19b10011-e8f2-537e-4f6c-d104768a1214", BLERead | BLENotify, 20); // Define a BLE characteristic for IMU data

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  if (!BLE.begin())
  {
    Serial.println("Starting BLE failed!");
    while (1)
      ;
  }

  BLE.setLocalName("Nano33IMU"); // Set a name for the Nano 33 BLE peripheral
  BLE.setAdvertisedService(imuService);

  imuService.addCharacteristic(imuCharacteristic);
  BLE.addService(imuService);

  imuCharacteristic.setValue("Hello IMU!"); // Initial dummy value
  BLE.advertise();

  Serial.println("BLE IMU Peripheral is now active, waiting for connections...");
}

void loop()
{
  BLEDevice central = BLE.central();

  if (central)
  {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected())
    {
      float ax, ay, az, gx, gy, gz;

      if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable())
      {
        // Read accelerometer and gyroscope data
        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);

        // Format IMU data into a byte array
        uint8_t imuData[20]; // Adjust the size as needed
        snprintf((char *)imuData, sizeof(imuData), "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", ax, ay, az, gx, gy, gz);

        imuCharacteristic.setValue(imuData, sizeof(imuData)); // Update BLE characteristic with IMU data
        delay(100);                                           // Adjust delay as necessary for your application
      }
      // float x, y, z;
      // if (IMU.accelerationAvailable()) {
      //   IMU.readAcceleration(x, y, z);
      //   String data = String(x) + "," + String(y) + "," + String(z);
      //   imuCharacteristic.writeValue(data.c_str());
      //   delay(100);
      // }
    }

    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
