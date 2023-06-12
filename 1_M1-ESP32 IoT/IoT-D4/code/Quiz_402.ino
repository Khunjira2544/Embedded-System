#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <TM1638plus.h>
#include "DHTesp.h"
#include <TridentTD_LineNotify.h> 
const char *My_SSID = "Gg";
const char *My_Pass = "0935463156";
const char *MQTT_Server = "things.ubidots.com";
const char *MQTT_User = "BBFF-7CfZiYPIr8CDn3s7OZQtcnw0GbzH76";
const char *MQTT_Pass = "BBFF-7CfZiYPIr8CDn3s7OZQtcnw0GbzH76";

#define LINE_TOKEN "mMQFHYzIN2RsoAbVq5zQlNMHr1HA3cGzEDfjbuN0Njo"

const char *PTopic1 = "/v2.0/devices/gg007test";
const char *STopic1 = "/v2.0/devices/gg007test/humid";
const char *STopic2 = "/v2.0/devices/gg007test/temppp";
#define Brd_STB 18 // strobe = GPIO connected to strobe line of module 
#define Brd_CLK 19 // clock = GPIO connected to clock line of module 
#define Brd_DIO 5 // data = GPIO connected to data line of module 
bool high_freq = true; //default false,, If using a high freq CPU > ~100 MHZ set to true.
TM1638plus tm(Brd_STB, Brd_CLK , Brd_DIO, high_freq);
#define MQTT_Port 1883
#define Pin_DHT22 15

DHTesp dht;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
void Setup_Wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(My_SSID);
  WiFi.begin(My_SSID, My_Pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect()
{ while (!client.connected()) // Loop until we're reconnected
  { Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32 Client-";
    clientId += String(random(0xffff), HEX); // Create a random client ID
    if (client.connect(clientId.c_str(), MQTT_User, MQTT_Pass)) // Attempt to connect
    { Serial.println("connected"); // Once connected, publish an announcement...
      client.subscribe(STopic1);
      client.subscribe(STopic2);
    } else
    { Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void setup()
{
  tm.displayBegin();
  dht.setup(Pin_DHT22, DHTesp::DHT22);
  Serial.begin(115200);
  Setup_Wifi();
  client.setServer(MQTT_Server, MQTT_Port);

  Serial.println(LINE.getVersion()); 
  Serial.println(WiFi.localIP()); 
  LINE.setToken(LINE_TOKEN); 
}
void loop()
{ if (!client.connected()) reconnect();
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000)
  { lastMsg = now;
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

    snprintf (msg, 75, "{ \"humid\" : %.2f, \"tempp\": %.2f}", humidity, temperature);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(PTopic1, msg);

    Serial.println();
    Serial.print("\nTemperature('C) = ");
    Serial.print(temperature, 1);
    Serial.print("\tHumidity(%) = ");
    Serial.print(humidity, 1);
    Serial.println();
    

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      Serial.print("HTTP Response code: ");
      http.end();
    }
    /// if temp > 28 C send notifications >> line
    if (temperature > 25) {
      Serial.println(LINE.getVersion()); 
      Serial.println(WiFi.localIP()); 
      LINE.setToken(LINE_TOKEN); 
      LINE.notify("อุณหภูมิ เกินกําหนด"); 
      LINE.notify("Temperature");
      LINE.notify(temperature); 
      LINE.notify("Humidity");
      LINE.notify(humidity);

    }
    /*Display */
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
}
