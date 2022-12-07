#include "input.h"

Input input;

const char *input_one = "R8,U5,L5,D3";
const char *input_two = "U7,R6,D4,L4";

void setup(){
	Serial.begin(9600);
	delay(200);

	Input::split(input_one, 1);
	Input::split(input_two, 2);
//	input.inspect(1);
//	Serial.println(" ");
//	input.inspect(2);

	//Serial.println(input.num_of_values(input_two));

	Serial.println(input.solve_one());
	//Serial.println(input.solve_two());
}

void loop(){}
