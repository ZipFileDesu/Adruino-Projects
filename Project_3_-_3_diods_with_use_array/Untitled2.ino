int ledPin[3] = {9, 10, 11};
int switchPin = 8;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = true;
int ledLevel = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  
  for (int i = 0; i < 3; ++i)
    pinMode(ledPin[i], OUTPUT);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(switchPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}

void ledLight(int i){
  ledLevel += 1;
  if (ledLevel > 255){
      ledLevel = 0;
    }
  delay(10);
  analogWrite(ledPin[i], ledLevel);
}

void loop() {
  // put your main code here, to run repeatedly:
//First programm
  Serial.println(currentButton);
  currentButton = debounce(lastButton);
  if (currentButton == HIGH && lastButton == LOW){
    ledLevel = 0;
    analogWrite(ledPin[i], ledLevel);
    ++i;
    if (i > 2) i = 0;
  }
  lastButton = currentButton;
  ledLight(i);
}