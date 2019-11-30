#include <SoftwareSerial.h>

char latitude[10], longitude[10];
char sentance[100]; // "$GPGGA,235317.000,4003.9039,N,10512.5793,W,1,08,1.6,1577.9,M,-20.7,M,,0000*5F";
char c;
int count;

SoftwareSerial mySerial(2,3);

void setup() {
  Serial.begin(115200);
  mySerial.begin(4800);
}

//void loop() {
//  while (mySerial.available()) {
//    char c = mySerial.read();
//    Serial.print(c);
//  }
//}


void loop() {
count = 0;
c = ' ';
  while (c != '\n') {
    if (mySerial.available()) {
      c = mySerial.read();
      sentance[count] = c;
      count += 1;      
    }
  }
  decode_nmea();
  memset(sentance, 0, sizeof(sentance));
  memset(latitude, 0, sizeof(latitude));
  memset(longitude, 0, sizeof(longitude));
}

void decode_nmea() {  
  if (sentance[3] == 'G' && sentance[4] == 'G' && sentance[5] == 'A') {
    for (int i = 0; i < 9; i++) {
      latitude[i] = sentance[i + 18];
      longitude[i] = sentance[i + 30];
    }
  Serial.print("Latitude: ");
  Serial.print(latitude); 
  Serial.print(" Longitude: ");
  Serial.print(longitude);
  Serial.println();
  }
}
