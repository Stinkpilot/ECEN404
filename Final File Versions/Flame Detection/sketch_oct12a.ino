#include <Wire.h>

#define sensor_enable_pin 10
#define rf_enable_pin 11
#define rf_data 12
#define fire_detected_led 13

//default address given to the pyro sensor
byte address = 101;

void setup() 
{
  pinMode(sensor_enable_pin, OUTPUT);
  pinMode(rf_enable_pin, OUTPUT);
  pinMode(rf_data, OUTPUT);

  digitalWrite(sensor_enable_pin, HIGH);
  digitalWrite(rf_enable_pin, LOW);
  digitalWrite(fire_detected_led, LOW);

  pyro_setup();
  
  Serial.begin(9600);
  while(!Serial);
}

void loop() 
{
  bool pyro_buffer[56];
  int flag_count = 0;

  flush_pyro_fifo(); 
  delay(10);

  for (size_t i = 0; i < 56; i++)
  {
    pyro_buffer[i] = read_fifo_packet();
  }

  for (size_t i = 0; i < 56; i++)
  {
    if (pyro_buffer[i] == true)
    {
      flag_count += 1;
    }
  } 
  if (flag_count > 20) {
    Serial.println(flag_count);
    digitalWrite(fire_detected_led, HIGH);
  } else {
    digitalWrite(fire_detected_led, LOW);
  }
  delay(1000);
}

void pyro_setup() 
{
  Wire.begin(address);

  //Wake up sensor
  Wire.beginTransmission(address);
  Wire.write(byte(0x22));
  Wire.endTransmission();

  delay(10);
  //configure analog settings
  Wire.beginTransmission(address);
  Wire.write(byte(0x14));
  
  Wire.write(byte(0x00));
  Wire.write(byte(0x79));
  Wire.endTransmission();

  //configure chennel selection settings
  Wire.beginTransmission(address);
  Wire.write(byte(0x10));
  
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.write(byte(0x35));
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  return;
}

bool read_fifo_packet()
{
  byte fifo_buffer[5] = {0, 0, 0, 0, 0};
  int i = 0;

  byte fifo_status = check_fifo_status();
  fifo_status = fifo_status & 0b00011110;
  fifo_status = fifo_status >> 1;

  if (fifo_status > 0b00000000)
  {
    Wire.beginTransmission(address);
    Wire.write(byte(0x08));
    Wire.endTransmission(0);
    
    Wire.requestFrom(address, 5);
    while (Wire.available()) { 
      fifo_buffer[i] = Wire.read(); 
      i += 1;       
    }
    Wire.beginTransmission(address);
    Wire.write(byte(0x0A));
    Wire.endTransmission();
  
    if (fifo_buffer[0] == byte(128))
    {
      return true;
    } 
    else 
    {
      return false;
    } 
  }
  else
  {
    Serial.println("Ran out of fifo");
    return false;
  }
}

byte check_fifo_status()
{
  Wire.beginTransmission(address);
  Wire.write(byte(0x04));
  Wire.endTransmission(0);
  
  Wire.requestFrom(address, 1); 
  return Wire.read();
}

void flush_pyro_fifo()
{
  Wire.beginTransmission(address);
  Wire.write(byte(0x0C));
  Wire.endTransmission();
  return;
}
