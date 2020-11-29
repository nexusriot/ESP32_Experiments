#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"


AsyncWebServer server(80);
const char *ssid = "NetworkName";
const char *password = "NetworkPassword";


void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); // Station mode
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed to initialize\n");
  }
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"message\":\"Wassup, man!\"}");
      });


  server.on("/networks", HTTP_GET, [](AsyncWebServerRequest *request) {

    auto n = WiFi.scanNetworks();
    DynamicJsonDocument root(1024);
    JsonArray aps = root.createNestedArray("APS");
        for (int i = 0; i < n; ++i) {
          JsonObject ap = aps.createNestedObject();
          ap["SSID"] = WiFi.SSID(i);
          ap["BSSID"] = WiFi.BSSIDstr(i);
          ap["RSSI"] = WiFi.RSSI(i);
          ap["ENC"] = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*";

      }
    String response;
    serializeJson(root, response);
    request->send(200, "application/json", response);
      });

  server.on("/get-query-param", HTTP_GET, [](AsyncWebServerRequest *request) {
    // example with qqery param
  StaticJsonDocument<100> data;
  if (request->hasParam("query-param"))
  {
    data["query-param"] = request->getParam("query-param")->value();
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
  }
  else {
    data["query-param"] = "No query parameter";
    String response;
    serializeJson(data, response);
    request->send(400, "application/json", response);
  }

});
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
}
