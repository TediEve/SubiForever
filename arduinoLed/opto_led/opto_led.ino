void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  //return;
  
  digitalWrite(2, HIGH); // sets the digital pin 13 on
  delay(500);            // waits for a second
  digitalWrite(2, LOW);  // sets the digital pin 13 off
  delay(2000);            // waits for a second

  
  digitalWrite(3, HIGH); // sets the digital pin 13 on
  delay(500);            // waits for a second
  digitalWrite(3, LOW);  // sets the digital pin 13 off
  delay(2000);

  digitalWrite(4, HIGH); // sets the digital pin 13 on
  delay(500);            // waits for a second
  digitalWrite(4, LOW);  // sets the digital pin 13 off
  delay(2000);

   digitalWrite(5, HIGH); // sets the digital pin 13 on
  delay(500);            // waits for a second
  digitalWrite(5, LOW);  // sets the digital pin 13 off
  delay(2000);
}
