#include "FRAM.h"

FRAM fram(256);

void setup() {
  Serial.begin(115200);
  while(!Serial){;}
  Serial.println("FRAM Test\n");

  fram.begin(4);

  // write
  int address = 0;

  fram.writeByte(address, 128);                   // 2^7
  address += sizeof(byte);

  fram.writeChar(address, -128);                  // -2^7
  address += sizeof(char);

  fram.writeChar(address, 'A');                   // 'A'
  address += sizeof(char);

  fram.writeShort(address, -32768);               // -2^15
  address += sizeof(short);

  fram.writeUShort(address, 65535);               // 2^16 - 1
  address += sizeof(unsigned short);

  fram.writeLong(address, -2147483648);           // -2^31
  address += sizeof(long);

  fram.writeULong(address, 4294967295);           // 2^32 - 1
  address += sizeof(unsigned long);

  fram.writeFloat(address, 123.123);
  address += sizeof(float);

  fram.writeDouble(address, 1234567.12345678);
  address += sizeof(double);

  fram.writeBool(address, true);
  address += sizeof(bool);

  String sentence = "I love ESP32.";
  fram.writeString(address, sentence);
  address += sentence.length() + 1;

  char gratitude[21] = "Thank You Espressif!";
  fram.writeString(address, gratitude);
  address += 21;
  
  // read
  address = 0;
  
  Serial.println(fram.readByte(address));
  address += sizeof(byte);

  Serial.println(fram.readChar(address));
  address += sizeof(char);
  
  Serial.println((char)fram.readChar(address));
  address += sizeof(char);

  Serial.println(fram.readShort(address));
  address += sizeof(short);

  Serial.println(fram.readUShort(address));
  address += sizeof(unsigned short);

  Serial.println(fram.readLong(address));
  address += sizeof(long);

  Serial.println(fram.readULong(address));
  address += sizeof(unsigned long);

  Serial.println(fram.readFloat(address), 3);
  address += sizeof(float);

  Serial.println(fram.readDouble(address), 8);
  address += sizeof(double);

  Serial.println(fram.readBool(address) ? "true" : "false");
  address += sizeof(bool);
  
  String sentence_r = fram.readString(address, sentence.length());
  Serial.println(sentence_r);
  address += sentence.length() + 1;

  Serial.println(fram.readString(address, 20));
  address += 21;
}

void loop() {
  // put your main code here, to run repeatedly:

}
