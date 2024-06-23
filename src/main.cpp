
#include <WiFiNINA.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <Arduino_LSM6DS3.h>

const char *ssid = "YoYo-2G";            // replace with your WiFi SSID
const char *password = "Happy$Boys!!2G"; // replace with your WiFi password

WiFiServer server(80);
WiFiClient client;

void connectToWiFi()
{
  Serial.print("Attempting to connect to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WiFi");
}
void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ; // Wait for Serial Monitor to open

  // Connect to WiFi
  connectToWiFi();

  // Initialize IMU sensor
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }
  Serial.println("IMU initialized");

  Wire.begin();

  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Check if a client has connected
  client = server.available();
  if (client)
  {
    Serial.println("New client connected");
    while (client.connected())
    {
      if (client.available())
      {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();

        // Read IMU data
        float accX, accY, accZ;
        float gyroX, gyroY, gyroZ;

        // Read accelerometer data
        IMU.readAcceleration(accX, accY, accZ);

        // Read gyroscope data
        IMU.readGyroscope(gyroX, gyroY, gyroZ);

        // Create JSON object
        JSONVar imuData;
        imuData["acceleration"]["x"] = accX;
        imuData["acceleration"]["y"] = accY;
        imuData["acceleration"]["z"] = accZ;
        imuData["gyroscope"]["x"] = gyroX;
        imuData["gyroscope"]["y"] = gyroY;
        imuData["gyroscope"]["z"] = gyroZ;

        // Convert JSON object to string
        String jsonString = JSON.stringify(imuData);

        // Send the response to the client
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println("Access-Control-Allow-Origin: *"); // Add CORS header
        client.println("Connection: close");
        client.println();
        client.println(jsonString);
        break;
      }
    }

    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}