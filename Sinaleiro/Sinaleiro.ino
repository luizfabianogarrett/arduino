const int vermelho = 11;
const int amarelo = 12;
const int verde = 13;
const int button = 8;
const int falante = 7;

void setup() {
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(button, INPUT);
  pinMode(falante, OUTPUT);
 
}

void loop() {
  if (digitalRead(button) == LOW)
  {
    apaga(verde);
    apaga(vermelho);
    apaga(amarelo);
    noTone(falante);
  }
  else
  {
    while(digitalRead(button) == HIGH){
      policia();
      ascende(verde);
      delay(30);
      apaga(verde);
      ascende(amarelo);
      delay(30);
      apaga(amarelo);
      ascende(vermelho);
      delay(30);
      apaga(vermelho);
    }
  }  
  
}

float seno;
int frequencia;

void sirene() {
 for(int x=0;x<180;x++){
  //converte graus para radiando e depois obtém o valor do seno
  seno = (sin(x*3.1416/180));
  //gera uma frequência a partir do valor do seno
  frequencia = 2000+(int(seno*1000));
  tone(falante, frequencia);
  delay(2);
 }
}

#define tempo 10
  void policia(){
    for (frequencia = 150; frequencia < 1800; frequencia += 1) 
  {
    tone(falante, frequencia, tempo); 
    delay(1);
    yield();
  }
  for (frequencia = 1800; frequencia > 150; frequencia -= 1) 
  {
    tone(falante, frequencia, tempo); 
    delay(1);
    yield();
  }
  }

void sinaleiro() {
  ascende(verde);
  delay(10000);
  pisca(verde);
  apaga(verde);

  ascende(amarelo);
  delay(3000);
  apaga(amarelo);

  ascende(vermelho);
  delay(10000);
  pisca(vermelho);
  apaga(vermelho);

  ascende(amarelo);
  delay(3000);
  apaga(amarelo);
}



void ascende(int cor) {
  digitalWrite(cor, HIGH);
}

void apaga(int cor) {
  digitalWrite(cor, LOW);
}


void pisca(int cor) {
  
  for(int i = 0; i < 6; i++){
    if (digitalRead(cor) == HIGH)
      apaga(cor);
    else
      ascende(cor);

    delay(800);
  }
}
