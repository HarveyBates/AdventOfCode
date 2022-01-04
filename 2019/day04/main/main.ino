#include "input.h"

Input input;

void setup(){
	Serial.begin(9600);
	delay(200);

	Serial.println(input.solve_one());
	//Serial.println(input.solve_two());
}

void loop(){}
