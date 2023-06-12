//Quiz_101_กดติด กดดับ 2 ชุด
#define pushButton1 22
#define LEDPin1 19
#define pushButton2 23
#define LEDPin2 18
int buttonState1 = 0;
int buttonState2 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(LEDPin1, OUTPUT);
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(LEDPin2, OUTPUT);
}
void loop() {
  if (digitalRead(pushButton1) == LOW) {
    delay(20);
    buttonState1 = 1 - buttonState1;
    digitalWrite(LEDPin1, buttonState1);
    while (digitalRead(pushButton1) == LOW);
    delay(20);}

  if (digitalRead(pushButton2) == LOW) {
    delay(20);
    buttonState2 = 1 - buttonState2;
    digitalWrite(LEDPin2, buttonState2);
    while (digitalRead(pushButton2) == LOW);
    delay(20);
    }
  
}
