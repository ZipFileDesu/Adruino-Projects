int buttonPin = 7;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 5;    // the debounce time; increase if the output flickers
boolean lastButtonStatus = LOW;
boolean buttonStatus = LOW;
unsigned long count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

boolean debounce(boolean reading){
  if (reading != lastButtonStatus) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonStatus) {
      Serial.println("debounce entered");
      buttonStatus = reading;
      return buttonStatus;
    }
  }
  return LOW;
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);

  if (debounce(reading) == HIGH) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    count += 1;
    Serial.print("Count: = ");
    Serial.println(count);
  }
  
  lastButtonStatus = reading;
}
