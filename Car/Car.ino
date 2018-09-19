#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#include "Motor.h"

#define frontLED1   A0
#define frontLED2   A1

RF24 radio(7, 8);
//CE, CSN

const byte address[6] = "00001";

void setup() {
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(115);
  radio.startListening();
  
  delay(200);

  Serial.begin(9600);
  Serial.println("Car Initialized");
  
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(frontLED1, OUTPUT);
  pinMode(frontLED2, OUTPUT);

  while (!radio.available())
  {
    front_light(150);
    delay(150);
  }

  front_light(1);
}

int ticksSinceLastConnection = 0;

int prevThrottle = 0;
int prevSteer = 0;

void loop() {

  read_and_drive();

  if (ticksSinceLastConnection >= 40)
  {
    prevThrottle = 0;
    prevSteer = 0;

    front_light(150);
    delay(150);
  }
  else
  {
    front_light(1);
  }

  delay(10);
}

bool isConnected = false;

void print_data()
{
  if (radio.available())
  {
    int package = -1;
    radio.read(&package, sizeof(int));
    
    int xState = package/100;
    int yState = package - xState*100;

    Serial.print("Package: ");
    Serial.print(package);
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(xState);
    Serial.print(" ");
    Serial.print("Y: ");
    Serial.print(yState);
    Serial.println();
  }
}

void read_data(int* xState, int* yState)
{
    int package = -1;
    radio.read(&package, sizeof(int));
    
    int x = package/100;
    int y = 0;
    
    if (x > 0)
      y = package - x*100 - 50;
    else
      y = package - x*100 + 50;

    if (x == 0)//Failed transmission, uses previous state
    {
      *xState = prevThrottle;
      *yState = prevSteer;

      ticksSinceLastConnection++;
    }
    else
    {
      if (x == 1)//Zero value transmitted
        *xState = 0;
      else//Nonzero value transmitted
        *xState = x;

      *yState = y*2;
        
      prevThrottle = *xState;
      prevSteer = *yState;

      Serial.print("Package: ");
      Serial.print(package);
      Serial.print("\t");
      Serial.print("X: ");
      Serial.print(*xState);
      Serial.print(" ");
      Serial.print("Y: ");
      Serial.print(*yState);
      Serial.println();

      ticksSinceLastConnection = 0;
    }
}

int xState = 0;
int yState = 0;

void read_and_drive()
{
  read_data(&xState, &yState);

  drive(xState + yState, xState - yState, 50);
}

void front_light(int dur)//if dur is 1, turns on, if dur is 0, turns off
{
  if (dur == 1)
  {
    digitalWrite(frontLED1, HIGH);
    digitalWrite(frontLED2, HIGH);
  }
  else if (dur == 0)
  {
    digitalWrite(frontLED1, LOW);
    digitalWrite(frontLED2, LOW);
  }
  else
  {
    digitalWrite(frontLED1, HIGH);
    digitalWrite(frontLED2, HIGH);
  
    delay(dur);
  
    digitalWrite(frontLED1, LOW);
    digitalWrite(frontLED2, LOW);
  }
}


