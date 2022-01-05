#include "input.h"


Input::Input(){}


long Input::solve_one(){

		const int kNumDigits = 6;
		long start = 271973;
		long end = 785961;

		long valid_passwords = 0;
		for(start; start < end; start++){
				char pwd [6*4];
				ltoa(start, pwd, 10);
				bool valid = false;
				for(int i = 0; i < kNumDigits - 1; i++){
						int prev = pwd[i] - '0';
						int next = pwd[i + 1] - '0';
						if(prev > next){
								valid = false;
								break;
						}
						if(prev == next){
								valid = true;
						}
				}
				if(valid){
						valid_passwords++;
				}
		}

		return valid_passwords;
}


template <size_t n>
bool Input::check_match(char (&match)[n], char c){
		for(int i = 0; i < n; i++){
				if(match[i] == c){
						return true;
				}
		}
		return false;
}


int Input::solve_two(){

		const int kNumDigits = 6;
		long start = 271973;
		long end = 785961;

		long valid_passwords = 0;
		for(start; start < end; start++){
				char pwd [6*4];
				ltoa(start, pwd, 10);
				bool valid = false;

				char match[6];
				int pos = 0;
				for(int i = 0; i < kNumDigits - 1; i++){
						int prev = pwd[i] - '0';
						int next = pwd[i + 1] - '0';
						if(prev > next){
								valid = false;
								break;
						}
						if(prev == next && !check_match(match, next)){
								match[pos++] = next;
								valid = true;
						}
				}
				if(valid){
						valid_passwords++;
				}
		}

		return valid_passwords;

}

