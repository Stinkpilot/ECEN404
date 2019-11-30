#include <Wire.h>


void setup()
{
  Wire.begin(101);

  //Wake up sensor
  Wire.beginTransmission(101);
  Wire.write(byte(0x22));
  Wire.endTransmission();

  delay(100);
  //configure analog settings
  Wire.beginTransmission(101);
  Wire.write(byte(0x14));
  
  Wire.write(byte(0x00));
  Wire.write(byte(0x79));
  Wire.endTransmission();

  //configure chennel selection settings
  Wire.beginTransmission(101);
  Wire.write(byte(0x10));
  
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.write(byte(0x35));
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.endTransmission();

  Serial.begin(9600);
  while (!Serial);             
}


void loop() {
  byte error, address, fifo_status;
  address = 101;

  Wire.beginTransmission(address);
  Wire.write(byte(0x04));
  Wire.endTransmission(0);
  
  Wire.requestFrom(address, 1); 
  fifo_status = Wire.read();

  fifo_status = fifo_status & 0b00011110;
  fifo_status = fifo_status >> 1;
  
  while (fifo_status > 0b00000000) {
    Wire.beginTransmission(address);
    Wire.write(byte(0x08));
    Wire.endTransmission(0);

    Wire.requestFrom(address, 5);
    while (Wire.available()) { 
      byte c = Wire.read(); 
      Serial.print(c, HEX); 
      Serial.print(" ");       
    }
    Wire.beginTransmission(address);
    Wire.write(byte(0x0A));
    Wire.endTransmission();
    fifo_status -= 0b1;
    Serial.println();
  }
  
  Serial.println("*********");    

//Wire.beginTransmission(address);
//Wire.write(byte(0x0E));
//Wire.endTransmission(0);
//
//
//Wire.requestFrom(address, 5);
//while (Wire.available()) { 
//  byte c = Wire.read(); 
//  Serial.print(c, BIN); 
//  Serial.print(" ");       
//}
//
//  delay(100000);
}
