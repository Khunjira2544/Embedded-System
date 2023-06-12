#include <TM1638plus.h> 
#include "DHTesp.h" 
#define Pin_DHT22 15 // D15 
#define Brd_STB 18 // strobe = GPIO connected to strobe line of module 
#define Brd_CLK 19 // clock = GPIO connected to clock line of module 
#define Brd_DIO 21 // data = GPIO connected to data line of module 
bool high_freq = true; //default false,, If using a high freq CPU > ~100 MHZ set to true. 
DHTesp dht; 
TM1638plus tm(Brd_STB, Brd_CLK , Brd_DIO, high_freq); 
void setup() { 
 Serial.begin(115200); 
 dht.setup(Pin_DHT22, DHTesp::DHT22); 
 tm.displayBegin(); 
} 
void loop() { 
 float h = dht.getHumidity(); 
 float t = dht.getTemperature(); 
 Serial.print("Temperature: "); 
 Serial.print(t); Serial.print(" *C\t"); 
 Serial.print("Humidity: "); 
 Serial.print(h); Serial.print(" %\n"); 
 int Tempp2 = (int)t/10; int Tempp1 = (int)t%10; int Tempp0 = (int)(t*10)%10; 
 int Humi2 = (int)h/10; int Humi1 = (int)h%10; int Humi0 = (int)(h*10)%10; 
 tm.displayHex(0, Tempp2); 
 tm.displayASCIIwDot(1, Tempp1 + '0'); // turn on dot 
 tm.displayHex(2, Tempp0); 
 tm.display7Seg(3, B01011000); // Code=tgfedcba 
 tm.displayHex(4, Humi2); 
 tm.displayASCIIwDot(5, Humi1 + '0'); // turn on dot 
 tm.displayHex(6, Humi0); 
 tm.display7Seg(7, B01110100); // Code=tgfedcba 
 delay(2000); 
}
