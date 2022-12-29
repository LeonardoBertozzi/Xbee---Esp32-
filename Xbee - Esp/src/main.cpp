#include <Arduino.h>
#include <Printers.h>
#include <HardwareSerial.h>
#include <stdio.h>
#include <string.h>


#define RXD2 16
#define TXD2 17


String BuildPackage(String payload, int len)
{
  String Payload1;
  String Payload2;
  char teste[len];
  int lenght = (payload.length()+1)/2;
  int j = 0;

  Serial.println();
  for(int i = 0; i < lenght; i++){
    Payload1 = payload.substring(j,j+=2);
    if( i == (lenght -1))
    {
      Payload1 = "0x" + Payload1 ;
    }
    else
    {
      Payload1 = "0x" + Payload1 + ",";
    }
    
    //Serial.print(Payload1);
    Payload2 = Payload2 + Payload1;
  }
  //Serial.println(Payload2);
  Payload2.toCharArray(teste,len);
  Serial.println(teste);
  byte input2 = (byte)atoi(teste);  
  Serial.println(input2);

  return Payload1;
}

String StringToHex(char* input)
{
  
  int loop;
  int i;
  loop = 0;
  i = 0;
  int len = strlen(input);
  char output[(len*2)+1];

  while(input[loop] != '\0')
  {
    sprintf((char*)(output+i),"%02x", input[loop]);
        loop+=1;
        i+=2;
  }
//Serial.println(output);
String package = output;
//Serial.println(package);
BuildPackage(package,(len*5));
return package;
}



byte packet [] = {0x7E, 0x00, 0x1B, 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x41, 0xD9, 0x8B, 0x5F, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x20, 0x21, 0xDB};
String pack = {"0x7E, 0x00, 0x1B, 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x41, 0xD9, 0x8B, 0x5F, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x20, 0x21, 0xDB"};

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Setup Ok");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(packet);
  
  Serial2.write(packet, sizeof(packet));
  char ascii_str [] = "Hello World!";
  (StringToHex(ascii_str));
  delay(5000);
}