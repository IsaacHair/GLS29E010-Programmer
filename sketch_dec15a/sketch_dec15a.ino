
void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 digitalWrite(9, HIGH);
 digitalWrite(10, LOW);
}

void loop() {
 recvOneChar();
}

void recvOneChar() {
  int i;
 if (Serial.available() > 0) {
  i = Serial.read()-48;
  if (i)
    digitalWrite(9, HIGH);
  else
    digitalWrite(9, LOW);
  discard();
 }
}

void discard()
{
  int i;
  while (!Serial.available()) ;
  if (Serial.available() > 0)
   i = Serial.read()-48;
}
