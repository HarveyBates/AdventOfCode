#ifndef INPUT_H_
#define INPUT_H_ 

#include <Arduino.h>

struct Instruction {
	char direction;
	int distance;
};

class Input {

	static const int kWireOneSize = 301;
	static const int kWireTwoSize = 301;

	static Instruction wire_one[kWireOneSize];
	static Instruction wire_two[kWireTwoSize];

	static int min_sum;
	static bool initial;

	public:
		Input();
		int num_of_values(const char* raw_string);
		static void split(const char* raw_string, char delim, int wire);

		int check_overlap(int x, int y, int xx, int yy);
		void second_wire(int xx, int yy);
		void inspect(int wire);

		int solve_one();
		int solve_two();
};


#endif // INPUT_H_

