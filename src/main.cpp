#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

BLEService imuService("19b10010-e8f2-537e-4f6c-d104768a1214");
BLECharacteristic imuCharacteristic("19b10011-e8f2-537e-4f6c-d104768a1214", BLERead | BLENotify, 50);

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

  BLE.setLocalName("Nano33IMU");
  BLE.setAdvertisedService(imuService);
  imuService.addCharacteristic(imuCharacteristic);
  BLE.addService(imuService);
  imuCharacteristic.setValue("Hello IMU!");
  BLE.advertise();

  // Set min and max connection interval to 7.5 ms
  BLE.setConnectionInterval(6, 6);

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
        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);

        // uint8_t imuData[50];
        // snprintf((char *)imuData, sizeof(imuData), "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", ax, ay, az, gx, gy, gz);
        // imuCharacteristic.setValue(imuData, sizeof(imuData));
        char imuData[50];
        snprintf(imuData, sizeof(imuData), "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", ax, ay, az, gx, gy, gz);
        imuCharacteristic.setValue((uint8_t *)imuData, strlen(imuData));

        delay(17); // Adjust delay to target 60 packets per second
      }
    }

    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
