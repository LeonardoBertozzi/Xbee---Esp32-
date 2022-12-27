#include <Arduino.h>
#include <Printers.h>
#include <HardwareSerial.h>
#include <stdio.h>
#include <string.h>


#define RXD2 16
#define TXD2 17


String BuildPackage(String payload, int len)
{
  char index[50] = "0x";
  char delimiter[] = ",";
  char char_array[50];
  char teste[50];
  
  payload.toCharArray(char_array,len);
  char* success = strdup(char_array);
  free(success);

  for(int i = 0; i < strlen(success); i++){
    //Serial.printf("%c", success[i]);
    //Serial.printf("/");
    Serial.println(i);
    i++;
    Serial.println("/-/");
    Serial.println(i);
  }
  return char_array;
}

String StringToHex(char* input)
{
  
  int loop;
  int i;
  loop = 0;
  i = 0;
  int len = strlen(input);
  char output[(len*2)+1];

  
  //strncat(index,hex_str,2);
  //strcpy(str2,index);
  //strncat(str2,delimiter,2);
  //Serial.println(index);
  //Serial.println(str2);

  while(input[loop] != '\0')
  {
    sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
  }
String package = output;
BuildPackage(package,(len*4)+1);
return package;
}



byte packet [] = {0x7E, 0x00, 0x1B, 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x41, 0xD9, 0x8B, 0x5F, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x20, 0x21, 0xDB};

void setup() {
  
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Setup Ok");
}

void loop() {
  Serial2.write(packet, sizeof(packet));
  char ascii_str [] = "Hello World!";;
  (StringToHex(ascii_str));
  delay(5000);
}