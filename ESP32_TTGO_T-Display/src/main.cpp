#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "WiFi.h"

TFT_eSPI tft = TFT_eSPI();

void prepareScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
}

void printInfo(String out) {
  Serial.println(out);
  tft.println(out);  
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(5);
  tft.setTextFont(1);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  prepareScreen();
  tft.println("Initializing...\n");
  delay(500);
}

void loop() {
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  prepareScreen();
  if (n == 0) {
    printInfo("no networks");
  }
  else {
  for (int i = 0; i < n; ++i){
      printInfo(WiFi.BSSIDstr(i));
    }
  }
  delay(15000);
}