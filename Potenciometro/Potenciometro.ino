const int pinoPot = 4;
const int pinoLed = 9;

float luminosidade = 0;

void setup() {
  pinMode(pinoPot, INPUT);
  pinMode(pinoLed, OUTPUT);

}

void loop() {
  luminosidade = map(analogRead(pinoPot), 0, 1023, 0, 255);
  analogWrite(pinoLed, luminosidade);
}
