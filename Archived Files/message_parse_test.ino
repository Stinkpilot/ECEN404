void setup() {
  Serial.begin(115200);

}

void loop() {
  String decimal_string="0000000122223333444455556666777700019999111122223333444455556666777788889999";
  byte sending_message[100]={0x21};
 
  for (int i = 0; i<=decimal_string.length(); i++) {
    if (decimal_string[i]=='1') {
      sending_message[i+1]={0x31};
    }
    else if (decimal_string[i]=='2') {
      sending_message[i+1]={0x32};
    }
    else if (decimal_string[i]=='3') {
      sending_message[i+1]={0x33};
    }  
    else if (decimal_string[i]=='4') {
      sending_message[i+1]={0x34};
    }
    else if (decimal_string[i]=='5') {
      sending_message[i+1]={0x35};
    } 
    else if (decimal_string[i]=='6') {
      sending_message[i+1]={0x36};
    } 
    else if (decimal_string[i]=='7') {
      sending_message[i+1]={0x37};
    } 
    else if (decimal_string[i]=='8') {
      sending_message[i+1]={0x38};
    }
    else if (decimal_string[i]=='9') {
      sending_message[i+1]={0x39};
    }   
    else if (decimal_string[i]=='.') {
      sending_message[i+1]={0x2E};
    }   
    else {
      sending_message[i+1]={0x00};
    }
  }

  Serial.write(sending_message, sizeof(sending_message));
  delay(5000);
}
