#include "input.h"

Input input;

void setup(){
  Serial.begin(9600);
  while(!Serial);

  input.parse();

  Serial.println(input.solve_one());
  Serial.println(input.solve_two());
}

void loop(){}
