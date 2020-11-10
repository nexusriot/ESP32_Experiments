#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

WebServer webServer(80);

const char *ssid = "AP_NAME";
const char *password = NULL; // "12345678";

IPAddress apIP(192, 168, 1, 4);
DNSServer dnsServer;
const char *server_name = "*";  // Can be "*" to all DNS requests

String responseHTML = "<!DOCTYPE html><html>"
                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                      "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
                      "</style></head>"
                      "<body><h1>5G Излучатель</h1>"
                      "<p>Вас здесь не ждали, уходите пожалуйста</p>"
                      "</body></html>";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(100);
  
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  const byte DNS_PORT = 53;
  dnsServer.start(DNS_PORT, server_name, apIP);

  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
