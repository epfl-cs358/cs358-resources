#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "<your_wifi_ssid>";
const char* password = "<your_wifi_password>";

ESP8266WebServer server;

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Connect to Wifi
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi..");
    delay(1000);
  }

  Serial.println("\nConnected.");
  Serial.print("IP Adress: ");
  Serial.println(WiFi.localIP());

  // Handle POST requests arriving at /data
  server.on("/data", HTTP_POST, handleData);

  server.begin();
}

void loop() {
  // Internally calls handleData on POST requests arriving at /data
  server.handleClient();
}

void handleData() {
  String json = server.arg("plain");

  // We specify a maximal size of 256B, you may want to change this value
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonArray controllers = doc["controllers"].as<JsonArray>();
  for(JsonObject controller : controllers) {
    if (controller.containsKey("buttons")) {
      JsonArray buttons = controller["buttons"].as<JsonArray>();
      for(JsonObject button : buttons) {
        int id = button["id"].as<int>();
        bool pressed = button["pressed"].as<bool>();
        float val = button["val"].as<float>();
        Serial.printf("Button %d with value %g\n", id, val);
      }
    }

    if (controller.containsKey("axes")) {
      JsonArray axes = controller["axes"].as<JsonArray>();
      for(JsonObject axis : axes) {
        int id = axis["id"].as<int>();
        float val = axis["val"].as<float>();
        Serial.printf("Axis %d with value %g\n", id, val);
      }
    }
  }
  
  server.send(200);
}
