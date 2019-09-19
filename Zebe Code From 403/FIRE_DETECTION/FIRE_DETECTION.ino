#include <VirtualWire.h>

int ir_val = 0;
int uv_val = 0;
int ir_pin = A4;
int uv_pin = A5;
int fire_led = 4;
int good_led = 7;

void setup() {
  Serial.begin(9600);
  vw_setup(2000);
  pinMode(ir_pin, INPUT);
  pinMode(uv_pin, INPUT);
  pinMode(fire_led, OUTPUT); 
  pinMode(good_led, OUTPUT); 
//  while(!Serial);
//  Serial.println("Beginning");
}

void loop() {
  ir_val = analogRead(ir_pin); 
  uv_val = analogRead(uv_pin); 
  
  Serial.print(ir_val);
  Serial.print(" ");
  Serial.print(uv_val);
  Serial.print("\n");

  if ((ir_val < 900) && (uv_val > 50)) {
    digitalWrite(fire_led, HIGH);
    digitalWrite(good_led, LOW);
    send("FIRE");
  } else {
    digitalWrite(fire_led, LOW);
    digitalWrite(good_led, HIGH);
  }
  delay(500);
}

void send (char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
}
