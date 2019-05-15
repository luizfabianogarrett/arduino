/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space
  #define BLYNK_PRINT DebugSerial*/
#define BLYNK_MAX_READBYTES 2048

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

//WidgetTerminal terminal(V1);

BlynkTimer timer;


const int vermelho = 11;
const int amarelo = 12;
const int verde = 13;
const int button = 8;
const int falante = 7;

void myTimerEvent()
{
  //Blynk.virtualWrite(V0, "http://test.com.br/api/v1/healthcheck");
  Blynk.virtualWrite(V30, "1");
  //terminal.print("Timer Executado");
  //V4variable++;
  //terminal.print(V4variable);
  count();
  validate();
}


int response;
int request;

void count()
{
  request++;
  //terminal.print("Request " + (String)request);

}


void validate()
{

  if ((request - response) > 3)
  {
    for (int i = 0; i < 10; i++) {
      sirene();
      digitalWrite(verde, LOW);
      digitalWrite(vermelho, HIGH);
      delay(30);
      digitalWrite(vermelho, LOW);
      digitalWrite(amarelo, HIGH);
      delay(30);
      digitalWrite(amarelo, LOW);
      delay(30);

    }
    request = 1;
    response = 1;
  }
  else
  {
    for (int i = 0; i < 10; i++) {
      digitalWrite(vermelho, LOW);
      digitalWrite(verde, HIGH);
      delay(30);
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, HIGH);
      delay(30);
      digitalWrite(amarelo, LOW);
      delay(30);
    }

  }

}


float seno;
int frequencia;

void sirene() {
  for (int x = 0; x < 180; x++) {
    //converte graus para radiando e depois obtém o valor do seno
    seno = (sin(x * 3.1416 / 180));
    //gera uma frequência a partir do valor do seno
    frequencia = 2000 + (int(seno * 1000));
    tone(falante, frequencia);
    delay(2);
  }
}



BLYNK_WRITE(V30)
{
  //String webhookdata = param.asStr();

  response++;
  //StaticJsonBuffer<200> jsonBuffer;

  //char jsonArray[300];
  //webhookdata.toCharArray(jsonArray, 200);

  //JsonObject& root = jsonBuffer.parseObject(jsonArray);

  //yield();

  //const char* store = root[0]["Store"];
  //terminal.println(store);
  //terminal.println(webhookdata);
  //terminal.println("Response " + (String)response );
  //terminal.println(request);

  //terminal.print("Data size: ");
  //terminal.println(webhookdata.length());

  //if (store[0] == 'w')
  //{


  //}
  //else
  //{


  //}

  //terminal.flush();

  //webhookdata = "";

  //yield();


}


void setup()
{
  timer.setInterval(65000L, myTimerEvent);

  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(button, INPUT);
  pinMode(falante, OUTPUT);

  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

}

void loop()
{
  if (digitalRead(button) == HIGH)
  {
    apaga(verde);
    apaga(vermelho);
    apaga(amarelo);
    noTone(falante);
  }

  Blynk.run();
  timer.run();

}

void apaga(int cor) {
  digitalWrite(cor, LOW);
}
