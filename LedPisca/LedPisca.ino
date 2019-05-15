int led = 9;                 // LED conectado ao pino digital 9

void setup()
{
  pinMode(led, OUTPUT);      // configura pino digital como saída
}

void loop()
{
  for (int i = 0; i <= 255; i++) {
    analogWrite(led, i);
    delay(10);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(led, i);
    delay(10);
  }
  
  analogWrite(led, LOW);         // Turn the LED off
  delay(1000);                   // Wait for a second
}
