/*
 * Written by Vince Vielhaber - K8ZW.
 * 
 * This software is free to use as you wish.  There are no guarantees,
 * warranties or promises to it's usefulness.  
 * 
 * Outputs D2-D8 are to switch the filters of a Kenwood TS-440
 * board.   The Kenwood needs 12V to switch the relays (2 per band)
 * so some kind of buffering is needed.  I'm using a Toshiba TD62783AP
 * to drive the relays, Yaesu used this IC in another package in the 
 * FT-100D.
 * 
 * Output D11 thru a 1st order LPF (10K ohm resistor, 10uf cap) will 
 * give you the CI-V values for the Xiegu XPA125B amp.  Double check the 
 * voltages before you connect it to your amp as this is untested beyond
 * using a DVM to measure the voltages.
 * 
 * Input D12 is the TTL level input from the Hermes Lite 2.0's DB9 connector.
 * An external pullup resistor is not needed, it's provided by the Arduino Nano.
 * 
 */




#include <SoftwareSerial.h>

SoftwareSerial Herm(12, 10); // RX, TX

char aa[100],dd[64];
String aaa;
long unsigned fq;
int band;
char RELAYS[8];

void setup() 
{

  RELAYS[0] = 0;
  RELAYS[1] = 0x4;
  RELAYS[2] = 0x8;
  RELAYS[3] = 0x10;
  RELAYS[4] = 0x20;
  RELAYS[5] = 0x40;
  RELAYS[6] = 0x80;
  
  pinMode(12,INPUT_PULLUP);

  Serial.begin(9600);

  Herm.begin(9600);

}

void loop() 
{
  
  if(Herm.available()) {
    aaa = Herm.readStringUntil(';');
    strncpy(aa,aaa.c_str(),13);
    fq = strtoul(&aa[4],NULL,10);

    if(fq <= 2500000)
      band = 1;
    else if(fq > 2500000 && fq <= 4000000)
      band = 2;
    else if(fq > 4000000 && fq <= 7500000)
      band = 3;
    else if(fq > 7500000 && fq <= 14500000)
      band = 4;
    else if(fq > 14500000 && fq <= 22000000)
      band = 5;
    else if(fq > 22000000 && fq <= 32000000)
      band = 6;
    else
      band = 0;    

    DDRD = DDRD | B11111100;
    PORTD = RELAYS[band];    

    sprintf(dd,"%lu is band %d",fq,band);
    
    Serial.write(dd);
    Serial.write("\n");

    if(fq >= 1800000 && fq < 2000000)
      band = 12;
    else if(fq >= 3500000 && fq < 4000000)
      band = 26;
    else if(fq >= 5330000 && fq < 5410000)
      band = 40;
    else if(fq >= 7000000 && fq < 7300000)
      band = 54;
    else if(fq >= 10000000 && fq < 10150000)
      band = 67;
    else if(fq >= 14000000 && fq < 14350000)
      band = 81;
    else if(fq >= 18068000 && fq < 18168000)
      band = 95;
    else if(fq >= 21000000 && fq < 21450000)
      band = 109;
    else if(fq >= 24890000 && fq < 24990000)
      band = 122;
    else if(fq >= 28000000 && fq < 29700000)
      band = 136;
    else if(fq >= 50000000 && fq < 54000000)
      band = 150;
    else
      band = 0;

    analogWrite(11,band);

    sprintf(dd,"The band voltage setting for %lu is %d",fq,band);

    Serial.write(dd);
    Serial.write("\n");
 }

  else
    delayMicroseconds(10000);

}
