#include "FRAM.h"

FRAM fram(256);

void setup() {
  Serial.begin(115200);
  while(!Serial){;}
  Serial.println("FRAM Test\n");

  fram.begin(4);
  
  const char* name = "Bizan Nishimura";
  char rname[32];
  double height = 5.84;
  uint32_t age = 45;

  // Write: Variables ---> FRAM
  fram.writeString(0, name);
  fram.put(30, height);
  fram.put(40, age);
  Serial.print("name: ");   Serial.println(name);
  Serial.print("height: "); Serial.println(height);
  Serial.print("age: ");    Serial.println(age);
  Serial.println("------------------------------------\n");

  // Clear variables
  name = "\0";
  height = 0;
  age = 0;

  // Read: Variables <--- FRAM
  fram.get(0, rname);
  fram.get(30, height);
  fram.get(40, age);
  Serial.print("name: ");   Serial.println(rname);
  Serial.print("height: "); Serial.println(height);
  Serial.print("age: ");    Serial.println(age);
  
  Serial.println("Done!");
}

void loop()
{
}
