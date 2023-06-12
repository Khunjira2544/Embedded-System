//Blynk
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6tSFFxJrg"
#define BLYNK_TEMPLATE_NAME "D3"
#define BLYNK_AUTH_TOKEN "BVnnV_3B38dKjYOj8wLmKkpc82r6tUTk"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "105/766-2.4G";
char pass[] = "0999128910";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
