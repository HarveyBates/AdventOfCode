#include "input.h"

long Input::inputs[kInputSize];


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


void Input::split(const char* raw_string, char delim){
	/* Turns a single line input into an array of long,
	 * based on a delimiter.
	 */

	int idx = 0;
	int first = 0;
	bool initial = true;
	for(int last = 0; last < strlen(raw_string); last++){
		if(raw_string[last] == delim){
			String tmp;
			if(!initial){
				first++;
			}
			for(first; first < last; first++){
				tmp += raw_string[first];
			}
			if(initial){
				initial = false;
			}
			inputs[idx] = tmp.toInt();
			idx++;
		}
		else if(last == strlen(raw_string) - 1){
			String tmp;
			for(first; first <= last; first++){
				if(raw_string[first] != delim){
					tmp += raw_string[first];
				}
			}
			inputs[idx] = tmp.toInt();
			break;
		}

	}

}


void Input::inspect(){
	for(int i = 0; i < kInputSize; i++){
		Serial.println(inputs[i]);
	}
}


long Input::solve_one(int noun, int verb){
	// Create a copy of inputs
	long tmpInputs[kInputSize];
	for(int i = 0; i < kInputSize; i++){
		tmpInputs[i] = inputs[i];
	}

	// Initial replacements
	tmpInputs[1] = noun;
	tmpInputs[2] = verb;
	for(int i = 0; i < kInputSize; i+=4){
		long tmp = 0;
		long new_noun = tmpInputs[tmpInputs[i+1]];
		long new_verb = tmpInputs[tmpInputs[i+2]];
		long *new_output = &tmpInputs[tmpInputs[i+3]];
		switch (tmpInputs[i]){
			case 1:
				// Add
				tmp = new_noun + new_verb;
			 	*new_output = tmp;
				break;
			case 2:
				// Multiply
				tmp = new_noun * new_verb;
			 	*new_output = tmp;
				break;
			case 99:
				return tmpInputs[0]; 
		}
	}
	return tmpInputs[0];
}


long Input::solve_two(const char* raw_string){
	int noun = 0;
	for(noun; noun < 100; noun++){
		int verb = 0;
		for(verb; verb < 100; verb++){
			long res = solve_one(noun, verb);
			if(res == 19690720){
				return 100 * noun + verb;
			}
		}
	}
	return 404; // Not found lol 
}

