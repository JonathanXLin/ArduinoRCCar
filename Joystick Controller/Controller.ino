#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#include "joystick.h"

RF24 radio(7, 8);
//CE, CSN

const byte address[6] = "00001";

void setup() {
  setup_joystick();
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(115);
  radio.stopListening();
  
  delay(200);

  Serial.begin(9600);
}

//Instantaneous -100 to 100 joystick positions
int xState = 0;
int yState = 0;

//All info sent via digits of package to radio
long package = 0;

void loop() {

    get_joystick_location(&xState, &yState);

    if (xState>0)//State represented by 4 digit long integer, abcd, where ab is xState (-99 to 99), and cd is yState (0 to 99)
      package = xState * 100 + yState + 50;
    else
      package = xState * 100 - yState + 50;
      
    Serial.println(package);

    radio.write(&package, sizeof(package));

    delay(10);
}
