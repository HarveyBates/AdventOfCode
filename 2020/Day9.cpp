#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<long> get_input(std::string fileName){
	std::vector<long> input;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		printf("Opened: %s\n", fileName.c_str());
		std::string tmp;
		while(getline(txtFile, tmp)){
			input.push_back(stol(tmp));
		}
	}
	txtFile.close();
	return input;
}

long preamble(std::vector<long> input, int length){
	long prev_vals[length];

	for(long i=0; i < length; i++){
		prev_vals[i] = input[i];
		// printf("%d\n", prev_vals[i]);
	}
	int prevValID = 0;
	for(long i=length; i < input.size(); i++){
		bool match = false;
		for(int x=0; x < length; x++){
			for(int y=x+1; y < length; y++){
				if(prev_vals[x] + prev_vals[y]  ==  input[i]){
					// printf("%ld + %ld = %ld\n", prev_vals[x], prev_vals[y], input[i]);
					match = true;
				}
			}
		}

		if(!match){
			return input[i];
		}

		else{
			if(prevValID < length-1){
				prev_vals[prevValID] = input[i];
				prevValID++;
			}
			else{
				prev_vals[prevValID] = input[i];
				prevValID = 0;
			}
		}
	}
	return 0;
}

long contiguous_set(std::vector<long> input, long invalidNum){
	for(long i=0; i < input.size(); i++){
		long sum = 0;
		int x = i +1;
		long min = input[x];
		long max = 0;
		while(sum < invalidNum){
			sum += input[x];
			if(input[x] > max){
				max = input[x];
			}
			if(input[x] < min){
				min = input[x];
			}
			// printf("%ld + %ld = %ld\n", input[x-1], input[x], sum);
			x++;
		}
		if(sum == invalidNum){
			// printf("%ld + %ld\n", min, max);
			return min + max;
		}
	}
	return 0;
}


int main(){
	std::vector<long> input = get_input("input_day9.txt");
	// printf("%d\n", input[0]);
	// long p1 = preamble(input, 5);
	long val = contiguous_set(input, 15690279);
	printf("%ld\n", val);
	return 0;
}