//Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6ehgcTddD"
#define BLYNK_TEMPLATE_NAME "D3Q2"
#define BLYNK_AUTH_TOKEN "ffaNF8m0Qzycu_tHIY_lcZfAq1toMz-V"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#define DHT22_Pin 15
const int btnPin = 18; //
boolean btnState = false;
WidgetLED blynk_LED(V5);
BlynkTimer timer; // Announcing the timer
const int btnPin2 = 19; //
boolean btnState2 = false;
WidgetLED blynk_LED2(V6);
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "105/766-2.4G";
char pass[] = "0999128910";
DHTesp dht;
//boolean btnState = false;
void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.setup(DHT22_Pin, DHTesp::DHT22); // Connect DHT sensor to GPIO 15
  pinMode(btnPin, INPUT_PULLDOWN);
  pinMode(btnPin2, INPUT_PULLDOWN);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}
void myTimerEvent() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  boolean isPressed = (digitalRead(btnPin) == LOW);
  if (isPressed != btnState)
  { if (isPressed)
      blynk_LED.on();
    else
      blynk_LED.off();
    btnState = isPressed;
    Serial.print(" LED Status = ");
    Serial.println(btnState);
    if (isPressed)
      blynk_LED2.on();
    else
      blynk_LED2.off();
    btnState2 = isPressed;
    Serial.print(" LED Status = ");
    Serial.println(btnState2);
  }
  Serial.print(" Temp('C) >> "); Serial.print(temperature, 1);
  Serial.print(", Humidity(%) >> "); Serial.println(humidity, 1);
}
void loop()
{
  Blynk.run();
  timer.run();
}
