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
char auth[] = "1c5e50ad1bcd430b860e380b29b96ce3";

//WidgetTerminal terminal(V1);

BlynkTimer timer;

const int red = 11;
const int yellow = 12;
const int green = 13;
const int button = 8;
const int buzzer = 7;

void myTimerEvent()
{
  //Blynk.virtualWrite(V0, "http://demo7950991.mockable.io/api/account");

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
      alert();
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      delay(30);
      digitalWrite(red, LOW);
      digitalWrite(yellow, HIGH);
      delay(30);
      digitalWrite(yellow, LOW);
      delay(30);

    }
    request = 1;
    response = 1;
  }
  else
  {
    for (int i = 0; i < 10; i++) {
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(30);
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      delay(30);
      digitalWrite(yellow, LOW);
      delay(30);
    }

  }

}


float seno;
int freq;

void alert() {
  for (int x = 0; x < 180; x++) {
    //converte graus para radiano e depois obtém o valor do seno
    seno = (sin(x * 3.1416 / 180));
    //gera uma frequência a partir do valor do seno
    freq = 2000 + (int(seno * 1000));
    tone(buzzer, freq);
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

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

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
    off(green);
    off(red);
    off(yellow);
    noTone(buzzer);
  }

  Blynk.run();
  timer.run();

}

void off(int color) {
  digitalWrite(color, LOW);
}
