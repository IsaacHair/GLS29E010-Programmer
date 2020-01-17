int prog[8][51]={
    {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,1,0},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,1,0, 1,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,1,1, 1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,1,0,0},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,1,0,0, 0,0,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,1,0,1, 0,1,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,1,1,0},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,1,1,0, 0,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,1,1,1, 0,1,0, 0,0,0,0,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0}};


void setup() {
  int i, j;

  for (i = 0; i < 54; i++)
    pinMode(i, OUTPUT);

  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH);
  
  for (i = 0; i < 1600; i++, delay(5))
    if (i%2)
      digitalWrite(19, HIGH);
    else
      digitalWrite(19, LOW);

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 52; j++)
      digitalWrite(j, LOW);
    digitalWrite(50, HIGH);
    digitalWrite(17, HIGH);

    delay(1);
    digitalWrite(52, LOW);
    delay(1);
    digitalWrite(52, HIGH);
    delay(1);

    for (j = 0; j < 52; j++)
      digitalWrite(j, LOW);
    digitalWrite(51, HIGH);
    digitalWrite(17, HIGH);

    delay(1);
    digitalWrite(52, LOW);
    delay(1);
    digitalWrite(52, HIGH);
    delay(1);
  }

  digitalWrite(52, HIGH);
  digitalWrite(53, LOW);

  for (i = 0; i < 52; i++)
    if (i != 19)
      pinMode(i, INPUT);

  for (i = 0; i < 16000; i++, delay(200))
    if (i%2)
      digitalWrite(19, HIGH);
    else
      digitalWrite(19, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
