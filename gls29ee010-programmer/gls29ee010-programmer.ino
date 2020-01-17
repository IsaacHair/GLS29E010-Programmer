adr[17] = { //assuming A0 on datasheet is the lsd and A16 is the msd

void setup() {
  int i;
  for (i = 24, i <= 53; i++)
    pinMode(i, INPUT);
  pinMode(24, OUTPUT);
  digitalWrite(24, HIGH);
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
  pinMode(34, OUTPUT);
  digitalWrite(34, LOW);
  pinMode(53, OUTPUT);
  digitalWrite(53, LOW);
}

void loop() {}
