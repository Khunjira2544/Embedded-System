#include <WiFi.h>
#include <HTTPClient.h>
#define WIFI_SSID "105/766-2.4G"
#define WIFI_PASS "0999128910"
#define WebHooksKey "dbrBCoc3b7tMyPoF__5yjk"
#define WebHooksEventNane "Test_Key"
#define testSwitch0 22 // 
#define testSwitch1 23 // 
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(testSwitch0, INPUT_PULLUP);
  pinMode(testSwitch1, INPUT_PULLUP);
  randomSeed(analogRead(33));
}
void loop() {
  if (digitalRead(testSwitch0) == LOW) {
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String("Door Open Alarm");
    Serial.println("Server Name :" + serverName);
    Serial.println("json httpRequestData :" + httpRequestData);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 200)
        Serial.println("Successfully sent");
      else
        Serial.println("Failed!");
    }
    else {
      Serial.println("WiFi Disconnected");
    }

    Serial.print(" >> Wait for 10 Sec --> ");
    for (int i = 9; i >= 0; i--) {
      Serial.print(i);
      delay(1000);
    }
    Serial.println(" >> Ready");
  }

  if (digitalRead(testSwitch1) == LOW) {
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String("Intruders Alarm");
    Serial.println("Server Name :" + serverName);
    Serial.println("json httpRequestData :" + httpRequestData);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 200)
        Serial.println("Successfully sent");
      else
        Serial.println("Failed!");
    }
    else {
      Serial.println("WiFi Disconnected");
    }

    Serial.print(" >> Wait for 10 Sec --> ");
    for (int i = 9; i >= 0; i--) {
      Serial.print(i);
      delay(1000);
    }
    Serial.println(" >> Ready");
  }
}
