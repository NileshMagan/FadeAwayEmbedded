
#include "Orientation.h"

void setupOrientation()
{
    if (!IMU.begin())
    {
        Serial.println("Failed to initialize IMU!");
        while (1)
            ;
    }
    Serial.println("IMU initialized!");
}

void readOrientation()
{
    float x, y, z;

    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(x, y, z);
        Serial.print("Acceleration X: ");
        Serial.print(x);
        Serial.print(", Y: ");
        Serial.print(y);
        Serial.print(", Z: ");
        Serial.println(z);
    }

    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(x, y, z);
        Serial.print("Gyroscope X: ");
        Serial.print(x);
        Serial.print(", Y: ");
        Serial.print(y);
        Serial.print(", Z: ");
        Serial.println(z);
    }
}