// #include <WiFiNINA.h>
// #include <WebSocketsClient.h>
// #include <Arduino_JSON.h>
// #include <Wire.h>
// #include <Arduino_LSM6DS3.h>

// const char *ssid = "YoYo-2G";            // replace with your WiFi SSID
// const char *password = "Happy$Boys!!2G"; // replace with your WiFi password
// const char *server = "10.1.1.251";       // Replace with your server's IP address
// const uint16_t port = 3000;

// WebSocketsClient webSocket;
// IPAddress ip;

// void connectToWiFi()
// {
//     Serial.begin(9600);
//     while (!Serial)
//     {
//     }

//     Serial.print("Connecting to WiFi...");
//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(1000);
//         Serial.print(".");
//     }

//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());
//     Serial.print("Attempting to connect to WS: ");
//     Serial.print(server);
//     Serial.print(":");
//     Serial.println(port);
// }

// void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
// {
//     switch (type)
//     {
//     case WStype_CONNECTED:
//         Serial.println("[WebSocket] Connected to server");
//         webSocket.sendTXT("Arduino"); // Identify as Arduino client
//         break;
//     case WStype_DISCONNECTED:
//         Serial.println("[WebSocket] Disconnected");
//         break;
//     case WStype_TEXT:
//         Serial.print("[WebSocket] Text received: ");
//         Serial.println((char *)payload);
//         break;
//     case WStype_BIN:
//         Serial.println("Binary message received");
//         break;
//     case WStype_PING:
//         Serial.println("PING!");
//         break;
//     case WStype_PONG:
//         Serial.println("PONG!");
//         break;
//     default:
//         Serial.print("Unknown event type: ");
//         Serial.print(type);
//         break;
//     }
// }

// void setup()
// {
//     connectToWiFi();

//     if (!IMU.begin())
//     {
//         Serial.println("Failed to initialize IMU!");
//         while (1)
//         {
//         }
//     }
//     Serial.println("IMU initialized");

//     // Ping the server
//     if (WiFi.hostByName(server, ip))
//     {
//         Serial.print("Server IP: ");
//         Serial.println(ip);
//         if (WiFi.ping(ip) >= 0)
//         {
//             Serial.println("Ping successful");
//         }
//         else
//         {
//             Serial.println("Ping failed");
//         }
//     }
//     else
//     {
//         Serial.println("Failed to resolve server IP");
//     }
//     webSocket.begin(server, port, "/");
//     webSocket.onEvent(webSocketEvent);
//     // Connect to the WebSocket server
//     webSocket.setReconnectInterval(1000); // try to reconnect every 5s
// }

// String getMeasurements()
// {
//     if (!IMU.accelerationAvailable() || !IMU.gyroscopeAvailable())
//         return "";
//     // Read IMU data
//     float accX, accY, accZ;
//     float gyroX, gyroY, gyroZ;

//     // Read accelerometer data
//     IMU.readAcceleration(accX, accY, accZ);

//     // Read gyroscope data
//     IMU.readGyroscope(gyroX, gyroY, gyroZ);
//     // Create JSON object
//     JSONVar imuData;
//     imuData["acceleration"]["x"] = accX;
//     imuData["acceleration"]["y"] = accY;
//     imuData["acceleration"]["z"] = accZ;
//     imuData["gyroscope"]["x"] = gyroX;
//     imuData["gyroscope"]["y"] = gyroY;
//     imuData["gyroscope"]["z"] = gyroZ;

//     // Convert JSON object to string
//     String jsonString = JSON.stringify(imuData);
//     return jsonString;
// }

// void loop()
// {
//     webSocket.loop();

//     String measurements = getMeasurements();
//     if (measurements != "")
//     {

//         String jsonString = JSON.stringify(measurements);
//         webSocket.sendTXT(jsonString);
//     }
// }

// // delay(1000 / 60); // 60 Hz

// // #include <Arduino.h>
// // #include <WiFiNINA.h>
// // #include <ArduinoWebsockets.h>

// // using namespace websockets;

// // // WiFi credentials
// // const char *ssid = "YoYo-2G";            // replace with your WiFi SSID
// // const char *password = "Happy$Boys!!2G"; // replace with your WiFi password
// // // WebSocket server address and port
// // const char *websockets_server_host = "10.1.1.251";
// // const uint16_t websockets_server_port = 3000;

// // WebsocketsClient client;

// // void onMessageCallback(WebsocketsMessage message)
// // {
// //   Serial.print("Got Message: ");
// //   Serial.println(message.data());
// // }

// // void onEventsCallback(WebsocketsEvent event, String data)
// // {
// //   if (event == WebsocketsEvent::ConnectionOpened)
// //   {
// //     Serial.println("Connnection Opened");
// //   }
// //   else if (event == WebsocketsEvent::ConnectionClosed)
// //   {
// //     Serial.println("Connnection Closed");
// //   }
// //   else if (event == WebsocketsEvent::GotPing)
// //   {
// //     Serial.println("Got a Ping!");
// //   }
// //   else if (event == WebsocketsEvent::GotPong)
// //   {
// //     Serial.println("Got a Pong!");
// //   }
// // }

// // void setup()
// // {
// //   // Start the Serial
// //   Serial.begin(9600);
// //   while (!Serial)
// //   {
// //     // wait for serial port to connect. Needed for native USB port only
// //   }

// //   // Connect to Wi-Fi
// //   Serial.print("Connecting to ");
// //   Serial.println(ssid);
// //   WiFi.begin(ssid, password);
// //   while (WiFi.status() != WL_CONNECTED)
// //   {
// //     delay(1000);
// //     Serial.print(".");
// //   }
// //   Serial.println();
// //   Serial.println("WiFi connected");

// //   // Set event & message handlers
// //   client.onMessage(onMessageCallback);
// //   client.onEvent(onEventsCallback);

// //   // Connect to the websocket server
// //   String url = String("ws://") + websockets_server_host + ":" + websockets_server_port;
// //   client.connect(url);

// //   // Send a message to the server
// //   client.send("Hello, Server!");
// // }

// // void loop()
// // {
// //   // Check for incoming messages
// //   client.poll();
// // }
