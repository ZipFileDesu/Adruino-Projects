int ledPin = 10;
int switchPin = 8;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;
int ledLevel = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
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

void loop() {
  // put your main code here, to run repeatedly:
//First programm
  Serial.println(lastButton);
  currentButton = debounce(lastButton);
  if(lastButton == LOW && currentButton == HIGH)
  {
    ledLevel = ledLevel + 51;
  }
    lastButton = currentButton;
    if (ledLevel > 255){
      ledLevel = 0;
    }
    ledLevel += 1;
    delay(10);
  analogWrite(ledPin, ledLevel);
}
