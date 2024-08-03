int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int led5 = 10;
int led6 = 11;

int onOffSwitch = 8;
int onOffLed = 12;

bool on = false;

void setup() {

  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  pinMode(onOffSwitch, INPUT_PULLUP);
}

void loop() {

  on = digitalRead(onOffSwitch) == 1;

  // int switchVal = digitalRead(12);
  int val0 = analogRead(A0);
  int val1 = analogRead(A1);
  int val2 = analogRead(A2);
  int val3 = analogRead(A3);
  int val4 = analogRead(A4);
  int val5 = analogRead(A5);


  // Serial.print(val0);
  // Serial.print("\t");
  // Serial.print(val1);
  // Serial.print("\t");
  // Serial.print(val2);
  // Serial.print("\t");
  // Serial.print(val3);
  // Serial.print("\t");
  // Serial.print(val4);
  // Serial.print("\t");
  // Serial.print(val5);
  // Serial.print("\t");
  // Serial.println("");

  // Serial.println(switchVal);

  // if (switchVal == 1) {
  //   analogWrite(3, map(val0, 0, 1023, 0, 50));
  //   analogWrite(5, map(val2, 0, 1023, 0, 50));
  // } else {
  //   analogWrite(3, 0);
  //   analogWrite(5, 0);    
  // }

  analogWrite(led1, map(val0, 0, 1023, 0, 50));
  analogWrite(led2, map(val1, 0, 1023, 0, 50));
  analogWrite(led3, map(val2, 0, 1023, 0, 50));

  analogWrite(led4, map(val3, 0, 1023, 0, 50));
  analogWrite(led5, map(val4, 0, 1023, 0, 50));
  analogWrite(led6, map(val5, 0, 1023, 0, 50));


  if (on){
    digitalWrite(onOffLed, 255);
  }  else {
    digitalWrite(onOffLed, LOW);
  }

  delay(50);
}
