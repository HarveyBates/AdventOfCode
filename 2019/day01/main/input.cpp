#include "input.h"


Input::Input(){}


const char* Input::get_raw(){
	return raw;
}


int Input::num_of_values(){
	int res = 0;
	for(int i = 0; i < strlen(raw); i++){
		if(raw[i] == ' '){
			res++;
		}
	}
	return res;
}


void Input::parse(){
	int idx = 0;
	int start = 0;
	bool initial = true;
	for(int i = 0; i < strlen(raw); i++){
		if(raw[i] == ' '){
			String tmp;
			int x = start;
			// Gets rid of preceeding space in input
			if(!initial){
				x++;
			}
			for(x; x < i; x++){
				tmp += raw[x];
			}
			start = x;
			if(initial){
				initial = false;
			}

			// Convert tmp to long and add to inputs
			inputs[idx] = tmp.toInt(); // Returns long
			idx++;
		}
		else if(i == strlen(raw) - 1){ // Handles last value
			String tmp;
			int x = start;
			for(x; x <= i; x++){
				tmp += raw[x];
			}
			start = x;
			// Convert tmp to long and add to inputs
			inputs[idx] = tmp.toInt(); // Returns long
			break;
		}
	}
}


void Input::inspect(){
	for(int i = 0; i < input_length; i++){
		Serial.println(inputs[i]);
	}
}


long Input::solve_one(){
	long res = 0;
	for(int i = 0; i < input_length; i++){
		long mass = (long)(floor((float)inputs[i] / 3.0f) - 2);
		res = res + mass;
	}
	return res;
}


long Input::solve_two(){
	long res = 0;
	for(int i = 0; i < input_length; i++){
		long fuel = (long)(floor((float)inputs[i] / 3.0f) - 2);
		long fuel_mass = (long)(floor((float)fuel / 3.0f) - 2);
		long total_fuel = fuel;
		while(fuel_mass > 0){
			total_fuel += fuel_mass;
			fuel_mass = (long)(floor((float)fuel_mass / 3.0f) - 2);
		}
		res += total_fuel;
	}
	return res;
}




