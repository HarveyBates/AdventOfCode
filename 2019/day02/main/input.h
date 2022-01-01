#ifndef INPUT_H_
#define INPUT_H_ 

#include <Arduino.h>

class Input {

	static const int kInputSize = 129; // Obtained from num_of_values()

	static long inputs[kInputSize];

	public:
		Input();
		int num_of_values(const char* raw_string);
		static void split(const char* raw_string, char delim);
		void inspect();
		long solve_one(int noun, int verb);
		long run_two(int noun, int verb);
		long solve_two(const char* raw_string);
};


#endif // INPUT_H_

