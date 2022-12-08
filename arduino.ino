#include <SPI.h>
#include <Ethernet.h>
#include "MgsModbus.h"
#include "DHT.h"  //Inclus la bibliothèque de la sonde

#define DHTPIN 2          // Definit la broche de connexions à la data
#define DHTTYPE DHT11     // Definit le type de capteur utilise
MgsModbus Mb;
int inByte = 0; // incoming serial byte
DHT dht(DHTPIN, DHTTYPE);   // Declare un objet de type DHT

// Ethernet settings (depending on MAC and Local network)
byte mac[] = {0xA8, 0x61, 0x0A, 0xAE, 0x88, 0x60};
IPAddress ip(192, 168, 0, 70);
IPAddress gateway(192, 168, 0, 10);
IPAddress subnet(255, 255, 255, 0);
int temperature = dht.readTemperature()*100;


void setup()
{
  dht.begin();  // Initialise le capteur DHT11
  // serial setup
  Serial.begin(9600);
  Serial.println("Serial interface started");

  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);   // start etehrnet interface
  Serial.println("Ethernet interface started"); 

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();

  // Fill MbData
//  Mb.SetBit(0,false);
  Mb.MbData[0] = temperature;
  Mb.MbData[1] = 0;
  Mb.MbData[2] = 0;
  Mb.MbData[3] = 0;
  Mb.MbData[4] = 0;
  Mb.MbData[5] = 0;
  Mb.MbData[6] = 0;
  Mb.MbData[7] = 0;
  Mb.MbData[8] = 0;
  Mb.MbData[9] = 0;
  Mb.MbData[10] = 0;
  Mb.MbData[11] = 0;

  afficheData();  
}

void loop()
{
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
  }
serial.printIn(temperature);
//  Mb.MbmRun();
  Mb.MbsRun();
}

void afficheData()
{
  // print MbData
  for (int i=0;i<12;i++) {
    Serial.print("address: "); Serial.print(i); Serial.print("Data: "); Serial.println(Mb.MbData[i]);
  }
  // print menu
  Serial.println("0 - print the first 12 words of the MbData space");
  Serial.println("1 - fill MbData with 0x000... hex");
  Serial.println("2 - fill MbData with 0xFFF... hex");
  Serial.println("3 - fill MbData with 0x555... hex");
  Serial.println("4 - fill MbData with 0xAAA... hex");
}