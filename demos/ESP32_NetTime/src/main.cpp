#include <WiFi.h>
#include <time.h>
 
const char* ssid     = "AP_NAME";     
const char* password = "secret";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;


void setup() {
  Serial.begin(115200);         
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.println("Connection established");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  delay(1000);
}

void draw_time(char *msg) {
  Serial.println(msg);
}
 
void loop() { 
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
      char time_str[16];
      strftime(time_str, 16, "%H:%M:%S", &timeinfo);

      draw_time(time_str);
  }  
  delay(500);
}
