#include<SoftwareSerial.h>
#define TIMEOUT 5000 // mS
const int TX = 4;
const int RX = 5;
int gesture = -1;
SoftwareSerial mySerial(RX,TX);
boolean tbr = false;
void setup() {
  // put your setup code here, to run once:
  String Wifi = "\"Fios-F77VF\"";
  String Pw = "\"hum377skip0344some\"";
  String server = "192.168.0.107";
 // String type = ;
  
  Serial.begin(115200);
  mySerial.begin(115200);
  //SendCommand("AT+RST","Ready");
  //delay(5000);
  //
  delay(5000);
  tbr=SendCommand("AT+CWQAP","OK");
  if(tbr){
  tbr = SendCommand("AT+CWMODE=3","OK");
  }
  if(tbr){
  tbr = SendCommand("AT+CWJAP="+Wifi+","+Pw,"OK");
  }
  delay(5000);
  /*if(tbr){
  tbr = SendCommand("AT+CWQAP","OK");
  }*/
  if(tbr){
  tbr = SendCommand("AT+CIPMUX=0","OK");
  }
  delay(5000);
  if(tbr){
  SendCommand("AT+CISFR","OK");
  }
  //delay(5000);
  
  delay(5000);
  
  
  
  //Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  detect();
  //SendCommand("AT+CIPSTART=\"TCP\",\"192.168.1.208\",8000","OK");
  mySerial.println("AT+CIPSTART=\"TCP\",\"192.168.1.208\",8000");
  delay(200);
  //SendCommand("AT+CIPSEND=1","OK");
  mySerial.println("AT+CIPSEND=1");
  delay(200);
  mySerial.println(gesture);
  delay(250);
  //SendCommand("AT+CIPCLOSE","OK");
  mySerial.println("AT+CIPCLOSE");
  delay(250);
}

void detect(){
  int middlefinger;
  int thumb; 
  int a0 = analogRead(2);
  int a2 = analogRead(0);
  middlefinger = map(a0, 370, 500, 0, 100);
  thumb = map(a2, 370, 600, 0, 100);
  int th = 20;
  if (middlefinger > th && thumb > th) {
    //Serial.println("Fist pump");
    gesture = 0;
  } 
  if (middlefinger < th && thumb > th) {
    //Serial.println("Four Fingers");
    gesture = 1;
  }
  if (middlefinger < th && thumb < th) {
    //Serial.println("High Five");
    gesture = 2;
  }
  if (middlefinger > th && thumb < th) {
    //Serial.println("Thumbs up");
    gesture = 3;
  }
}

boolean SendCommand(String cmd, String ack){
  mySerial.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}
 
boolean echoFind(String keyword){
 byte current_char = 0;
 byte keyword_length = keyword.length();
 long deadline = millis() + TIMEOUT;
 while(millis() < deadline){
  if (mySerial.available()){
    char ch = mySerial.read();
    Serial.write(ch);
    if (ch == keyword[current_char])
      if (++current_char == keyword_length){
       Serial.println();
       return true;
    }
   }
  }
 return false; // Timed out
}
