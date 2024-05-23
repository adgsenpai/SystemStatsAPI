#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// OLED display setup
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 12, U8X8_PIN_NONE);

// WiFi credentials
const char* ssid = "<your_wifi>";
const char* password = "<your_wifipwd>";

// HTTP client
WiFiClientSecure client;
HTTPClient http;

void setup(void) {
  Serial.begin(115200);
  u8g2.begin();
  WiFi.begin(ssid, password);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14B_tr);
  u8g2.drawStr(0, 10, "Connecting to WiFi...");
  u8g2.sendBuffer();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  u8g2.clearBuffer();
  u8g2.drawStr(0, 10, "WiFi connected");
  u8g2.sendBuffer();
  delay(2000); // Show the message for 2 seconds

  // Configure the client to trust the SSL certificate of the server
  client.setInsecure(); // This is for testing purposes only. You should configure the certificate for production use.
}

void loop(void) {
  http.begin(client, "https://<yourdomain>/api/system");
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println("HTTP Response payload:");
    String payload = http.getString();
    Serial.println(payload);
    
    DynamicJsonDocument doc(8192); // Adjust size as needed
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    // Extract system stats
    JsonObject memory = doc["memory"];
    uint64_t totalMemory = memory["total"].as<uint64_t>();
    uint64_t usedMemory = memory["used"].as<uint64_t>();
    float memoryPercent = memory["percent"].as<float>();

    JsonObject cpu = doc["cpu"];
    float cpuPercent = cpu["cpu_percent"].as<float>();

    JsonObject swap = doc["swap"];
    uint64_t totalSwap = swap["total"].as<uint64_t>();
    uint64_t usedSwap = swap["used"].as<uint64_t>();
    float swapPercent = swap["percent"].as<float>();

    // Debugging: Log parsed values
    Serial.printf("Total Memory: %llu\n", totalMemory);
    Serial.printf("Used Memory: %llu\n", usedMemory);
    Serial.printf("Memory Percent: %.2f\n", memoryPercent);
    Serial.printf("CPU Percent: %.2f\n", cpuPercent);
    Serial.printf("Total Swap: %llu\n", totalSwap);
    Serial.printf("Used Swap: %llu\n", usedSwap);
    Serial.printf("Swap Percent: %.2f\n", swapPercent);

    // Display system stats
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawStr(0, 10, "RAM:");
    u8g2.drawStr(40, 10, String(usedMemory / 1024 / 1024).c_str());
    u8g2.drawStr(80, 10, "/");
    u8g2.drawStr(90, 10, String(totalMemory / 1024 / 1024).c_str());
    u8g2.drawStr(0, 30, "CPU:"); // Moved down from 25 to 30
    u8g2.drawStr(40, 30, String(cpuPercent, 1).c_str());
    u8g2.drawStr(90, 30, "%");
    u8g2.drawStr(0, 45, "Swap:"); // Moved down from 40 to 45
    u8g2.drawStr(40, 45, String(usedSwap / 1024 / 1024).c_str());
    u8g2.drawStr(80, 45, "/");
    u8g2.drawStr(90, 45, String(totalSwap / 1024 / 1024).c_str());
    u8g2.drawStr(0, 60, "Mem :"); // Moved down from 55 to 60
    u8g2.drawStr(40, 60, String(memoryPercent, 1).c_str());
    u8g2.drawStr(90, 60, "%");
    u8g2.sendBuffer();
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpCode);

    // Display error message
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawStr(0, 10, "Failed to fetch data");
    u8g2.sendBuffer();
  }

  http.end();
  delay(60000); // Update every minute
}
