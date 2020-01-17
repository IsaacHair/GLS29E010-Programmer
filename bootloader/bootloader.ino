//1 kHz instruction speed, pwm program for 25%/100%
int i[8][11]={
  {0,0,0, 1,1,1,0, 0, 0,0,1},
  {0,0,1, 0,1,0,0, 0, 0,1,0},
  {0,1,0, 1,1,0,0, 1, 0,1,1},
  {0,1,1, 0,1,0,0, 1, 1,0,0},
  {1,0,0, 0,0,0,1, 1, 1,0,1},
  {1,0,1, 1,1,1,1, 0, 1,1,0},
  {1,1,0, 0,0,0,1, 0, 1,1,1},
  {1,1,1, 1,1,1,1, 0, 0,0,0},
};
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  delay(5000);
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, HIGH);
    delayMicroseconds(125);
    digitalWrite(13, LOW);
    delayMicroseconds(125);
  }
  delay(5000);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  int a, b;
  for(a = 0; a < 8; a++) {
    delayMicroseconds(125);
  for(b = 0; b < 11; b++)
    if(i[a][b])
      digitalWrite(12-b, HIGH);
    else
      digitalWrite(12-b, LOW);
  delayMicroseconds(125);
  digitalWrite(13, HIGH);
  delayMicroseconds(125);
  digitalWrite(13, LOW);
  delayMicroseconds(125);
  }
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  delay(5000);
  while (1) {
    digitalWrite(13, HIGH);
    delayMicroseconds(125);
    digitalWrite(13, LOW);
    delayMicroseconds(125);
  }
}

void loop() {}
