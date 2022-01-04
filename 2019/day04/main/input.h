#ifndef INPUT_H_
#define INPUT_H_ 

#include <Arduino.h>

class Input {

	public:
		Input();
		bool check_match(char *match, char c);
		long solve_one();
		int solve_two();
};


#endif // INPUT_H_
