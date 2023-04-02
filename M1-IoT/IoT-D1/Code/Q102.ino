#define DHT22_Pin 15 
#include "DHTesp.h" 
DHTesp dht; 
void setup() { 
 Serial.begin(115200); 
 Serial.println(); 
 //Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)"); 
 dht.setup(DHT22_Pin, DHTesp::DHT22); // Connect DHT sensor to GPIO 15 
} 
void loop() { 
 delay(dht.getMinimumSamplingPeriod()); 
 float humidity = dht.getHumidity(); 
 float temperature = dht.getTemperature();  
 Serial.print("Temperature: "); 
 Serial.print(temperature, 1); 
 Serial.print("C / ");  
 Serial.print(dht.toFahrenheit(temperature), 1); 
 Serial.print("F. "); 
 Serial.print("Humidity: "); 
 Serial.print(humidity, 1); 
 Serial.print("%");  
 Serial.println(" ");  
 delay(2000); 
} 
