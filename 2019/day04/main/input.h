#ifndef INPUT_H_
#define INPUT_H_ 

#include <Arduino.h>

class Input {

	public:
		Input();
		//inline int test(int x, int y) return x + y;
		template<size_t n>
		bool check_match(char (&match)[n], char c);
		//bool check_match(char *match, char c);
		long solve_one();
		int solve_two();
};


#endif // INPUT_H_
