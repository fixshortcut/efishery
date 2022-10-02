#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define ss 5
#define rst 14
#define dio0 2

int counter = 0, sensor1, sensor2;
unsigned long waktu_tulis;

void setup() {
  Serial.begin(115200);
  while (!Serial)
  Serial.println("LoRa Sensor");

  LoRa.setPins(ss, rst, dio0);
  
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  waktu_tulis = millis();
}

void loop() {
  // Serial.print("Sending packet: ");
  // Serial.println(counter);
  sensor1 = random(0,100);
  sensor2 = random(10,30);
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Lora: ");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
      if(LoRaData.indexOf("Pub")){
      Serial.printf("SensDev S1 = %d, S2 = %d \n",sensor1,sensor2);
      LoRa.beginPacket();
      LoRa.printf("SensDev S1 = %d, S2 = %d \n",sensor1,sensor2);
      // LoRa.print("hello ");
      LoRa.endPacket();
      }
        
      
    }
    // print RSSI of packet
    // Serial.print("' with RSSI ");
    // Serial.println(LoRa.packetRssi());
    
  }
  // while(millis() >= waktu_tulis + 1000){
  
  // //Send LoRa packet to receiver
  
  // waktu_tulis = millis();
  // } 
  // put your main code here, to run repeatedly:
}