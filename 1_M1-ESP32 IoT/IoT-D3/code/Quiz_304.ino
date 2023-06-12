#include <WiFi.h>
#include <HTTPClient.h>
#include "DHTesp.h"
#include <TM1638plus.h>
#define WIFI_SSID "105/766-2.4G"
#define WIFI_PASS "0999128910"
#define WebHooksKey "dbrBCoc3b7tMyPoF__5yjk"
#define WebHooksEventNane "gg"
#define WebHooksEventNane_LINE "Test_Key"
#define My_NAME "B6321451"
#define Pin_DHT22 15
#define Brd_STB 18
#define Brd_CLK 19
#define Brd_DIO 5
bool high_freq = true;
TM1638plus tm(Brd_STB, Brd_CLK , Brd_DIO, high_freq);
DHTesp dht;
void setup() {
  Serial.begin(115200);
  tm.displayBegin();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  dht.setup(Pin_DHT22, DHTesp::DHT22);
}
void loop() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.println();
  Serial.print("\nTemperature('C) = ");
  Serial.print(temperature, 1);
  Serial.print("\tHumidity(%) = ");
  Serial.print(humidity, 1);
  String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane) + "/with/key/" +
                      String(WebHooksKey);
  String httpRequestData = "value1=" + String(My_NAME) + "&value2=" + String(temperature) + "&value3=" +
                           String(humidity);
  Serial.println();
  Serial.println("Server Name >> " + serverName);
  Serial.println("json httpRequestData >> " + httpRequestData);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(httpRequestData);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    if (httpResponseCode == 200)
      Serial.println(" --> Successfully sent");
    else
      Serial.println(" --> Failed!");
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  if (temperature > 28) {
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane_LINE) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String(temperature);
    Serial.println();
    Serial.println("Server Name >> " + serverName);
    Serial.println("json httpRequestData >> " + httpRequestData);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 200)
        Serial.println("[Line] --> Successfully sent");
      else
        Serial.println("[Line] --> Failed!");
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
  int t = int(temperature * 100);
  int Tempp2 = (int)temperature / 10; int Tempp1 = (int)temperature % 10; int Tempp0 = (int)(temperature * 10) % 10;
  int Humi2 = (int)humidity / 10; int Humi1 = (int)humidity % 10; int Humi0 = (int)(humidity * 10) % 10;
  tm.displayHex(0, Tempp2);
  tm.displayASCIIwDot(1, Tempp1 + '0'); // turn on dot
  tm.displayHex(2, Tempp0);
  tm.display7Seg(3, B01011000); // Code=tgfedcba
  tm.displayHex(4, Humi2);
  tm.displayASCIIwDot(5, Humi1 + '0'); // turn on dot
  tm.displayHex(6, Humi0);
  tm.display7Seg(7, B01110100); // Code=tgfedcba
  delay(2000);
  int WaitTime = 60;
  Serial.print(" >> Wait for next time --> ");
  for (int i = WaitTime; i >= 0; i -= 5) {
    Serial.print(",");
    Serial.print(i);
    delay(5000);
  }
}
