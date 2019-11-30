#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
byte test[4] = {'F', 'I', 'R', 'E'};
void setup() {
  Serial.begin(9600);
  vw_setup(2000);

  pinMode(4, OUTPUT);
  
  Serial.println("Beginning");
  vw_rx_start(); // Start the receiver
}

void loop() {
int correct_count = 0;
if (vw_get_message(message, &messageLength)) // Non-blocking {
  for (int i = 0; i < messageLength; i++) {
    if (message[i] == test[i]) {
      //Serial.println(1);
      correct_count =  correct_count + 1;
      //Serial.println(correct_count);
    } else {
      //Serial.println(0);
    }
  }
   
  if (correct_count == 4) {
    Serial.println("FIRE");
    digitalWrite(4, HIGH);
    delay(5000);
  } else {
    digitalWrite(4, LOW);
  }
}
