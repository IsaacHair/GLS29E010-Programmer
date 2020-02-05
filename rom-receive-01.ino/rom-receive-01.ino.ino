void setup()
{
  int incomingByte;
  Serial.begin(9600, SERIAL_8N1);
  // send data only when you receive data:
  while(1)
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
  
      // say what you got:
      Serial.println(incomingByte);
    }
}

void loop() {}
