#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class TemperatureClient {
  private:
    const char* ssid;
    const char* password;
    const char* serverAddress;
    int serverPort;
    
  public:
    TemperatureClient(const char* ssid, const char* password, const char* serverAddress, int serverPort) {
      this->ssid = ssid;
      this->password = password;
      this->serverAddress = serverAddress;
      this->serverPort = serverPort;
    }
    
    void connectToWiFi() {
      WiFi.begin(ssid, password);
      Serial.println("Connecting to WiFi...");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
      }
      Serial.println("Connected to WiFi");
    }
    
    float getAverageTemperature(const String& payload) {
      DynamicJsonDocument doc(512);
      deserializeJson(doc, payload);
      if (doc.containsKey("values")) {
        float sum = 0;
        int count = doc["values"].size();
        for (const auto& value : doc["values"].as<JsonArray>()) {
          sum += value.as<float>();
        }
        return sum / count;
      }
      return 0;
    }
    
    void sendPostRequest(float temperature, const String& location) {
      WiFiClient client;
      HTTPClient http;
      DynamicJsonDocument json(128);
      json["location"] = location;
      json["value"] = temperature;
      String jsonString;
      serializeJson(json, jsonString);
      http.begin(client, "http://" + String(serverAddress) + ":" + String(serverPort) + "/add_value");
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(jsonString);
      if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
        Serial.println("POST request sent successfully");
      } else {
        Serial.print("Error sending POST request, HTTP code: ");
        Serial.println(httpCode);
      }
      http.end();
    }
    
    void fetchDataAndSend() {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        WiFiClient client;
        http.begin(client, "http://" + String(serverAddress) + ":" + String(serverPort) + "/get_values?location=string");
        int httpCode = http.GET();
        if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          float averageTemperature = getAverageTemperature(payload);
          sendPostRequest(averageTemperature, "string");
        }
        http.end();
      }
    }
};

TemperatureClient temperatureClient("test", "123456789", "172.20.10.10", 5000);

void setup() {
  Serial.begin(115200);
  temperatureClient.connectToWiFi();
}

void loop() {
  temperatureClient.fetchDataAndSend();
  delay(5000);
}
