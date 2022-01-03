#include "input.h"

Instruction Input::wire_one[kWireOneSize];
Instruction Input::wire_two[kWireTwoSize];

int Input::min_sum = 0;
bool Input::initial = true;


Input::Input(){}


int Input::num_of_values(const char* raw_string){
	int res = 0;
	for(int i = 0; i < strlen(raw_string); i++){
		if(raw_string[i] == ','){
			res++;
		}
	}
	return res + 1;
}


void Input::split(const char* raw_string, int wire){

	Instruction instruction;

	char *pch;
	pch = strtok(raw_string, ",");

	int pos = 0;
	while(pch != NULL){

		instruction.direction = pch[0];
		String tmp;
		for(int i = 1; i < strlen(pch); i++){
			tmp += pch[i];
		}
		instruction.distance = tmp.toInt();

		switch(wire){
			case 1:
				wire_one[pos] = instruction;
				break;
			case 2:
				wire_two[pos] = instruction;
				break;
		}

		pch = strtok(NULL, ",");
		pos++;
	}
}


void Input::inspect(int wire){
	if(wire == 1){
		for(int i = 0; i < kWireOneSize; i++){
			Serial.print(wire_one[i].direction);
			Serial.print(" -> ");
			Serial.println(wire_one[i].distance);
		}
	}
	else if(wire == 2){
		for(int i = 0; i < kWireTwoSize; i++){
			Serial.print(wire_two[i].direction);
			Serial.print(" -> ");
			Serial.println(wire_two[i].distance);
		}
	}
}


int Input::check_overlap(int x, int y, int xx, int yy){
	if(x == xx && y == yy){
		int sum = abs(x) + abs(y);
		if(initial && sum != 0){
			min_sum = sum;
			initial = false;
		}
		if(sum < min_sum){
			min_sum = sum;
			Serial.print("Min Sum: ");
			Serial.println(min_sum);
		}
	}
	return NULL;
}


void Input::second_wire(int xx, int yy){
	int current_x = 0;
	int current_y = 0;
	for(int i = 0; i < kWireTwoSize; i++){
		int dist = 0;
		switch (wire_two[i].direction){
			case 'U':
				dist = current_y + wire_two[i].distance;
				for(int y = current_y; y < dist; y++){
					if(y > yy || xx != current_x){
						current_y = dist;
						break;
					}
					check_overlap(xx, yy, current_x, y);
				}
				current_y = dist;
				break;
			case 'D':
				dist = current_y - wire_two[i].distance;
				for(int y = current_y; y > dist; y--){
					if(y < yy || xx != current_x){
						current_y = dist;
						break;
					}
					check_overlap(xx, yy, current_x, y);
				}
				current_y = dist;
				break;
			case 'R':
				dist = current_x + wire_two[i].distance;
				for(int x = current_x; x < dist; x++){
					if(x > xx || yy != current_y){
						current_x = dist;
						break;
					}
					check_overlap(xx, yy, x, current_y);
				}
				current_x = dist;
				break;
			case 'L':
				dist = current_x - wire_two[i].distance;
				for(int x = current_x; x > dist; x--){
					if(x < xx || yy != current_y){
						current_x = dist;
						break;
					}
					check_overlap(xx, yy, x, current_y);
				}
				current_x = dist;
				break;
		}
	}
}


int Input::solve_one(){
	
	int first_path_idx = 0;
	int current_x = 0;
	int current_y = 0;
	for(int i = 0; i < kWireOneSize; i++){
		Serial.println(i);
		int dist = 0;
		switch (wire_one[i].direction){
			case 'U':
				dist = current_y + wire_one[i].distance;
				for(int y = current_y; y < dist; y++){
					second_wire(current_x, y);
				}
				current_y = dist;
				break;
			case 'D':
				dist = current_y - wire_one[i].distance;
				for(int y = current_y; y > dist; y--){
					second_wire(current_x, y);
				}
				current_y = dist;
				break;
			case 'R':
				dist = wire_one[i].distance + current_x;
				for(int x = current_x; x < dist; x++){
					second_wire(x, current_y);
				}
				current_x = dist;
				break;
			case 'L':
				dist = current_x - wire_one[i].distance;
				for(int x = current_x; x > dist; x--){
					second_wire(x, current_y);
				}
				current_x = dist;
				break;
		}
	}

	return min_sum;
}


int Input::solve_two(){

}

