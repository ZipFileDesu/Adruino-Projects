int dataPin  = 9;   //Пин подключен к DS входу 74HC595
int latchPin = 10;  //Пин подключен к ST_CP входу 74HC595
int clockPin = 11;  //Пин подключен к SH_CP входу 74HC595
int buttonPin = 2;

byte leds[8] = {
  B00000000,
  B01000000,
  B01100000,
  B00110000,
  B00011000,
  B00001100,
  B00000110,
  B00000010};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);     
  pinMode(buttonPin, INPUT);           
}

void loop() {
  for (int i = 0; i < 8; ++i){
    digitalWrite(latchPin, LOW);                        // устанавливаем синхронизацию "защелки" на LOW
    shiftOut(dataPin, clockPin, LSBFIRST, leds[i]);   // передаем последовательно на dataPin
    digitalWrite(latchPin, HIGH); 
    delay(50);  
  }
}
