#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<int> get_input(std::string fileName){
	std::vector<int> input;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		printf("Opened: %s\n", fileName.c_str());
		std::string tmp;
		while(getline(txtFile, tmp)){
			input.push_back(stoi(tmp));
		}
	}
	txtFile.close();
	return input;
}

int solve_one(std::vector<int> input){
	// Part 1 (Answer 1755)
	std::sort(input.begin(), input.end());
	int oneJolt = 1, threeJolt = 1; 
	for(int i=0; i < input.size(); i++){
		if(input[i+1] - input[i] == 3){
			threeJolt++;
		}
		else if(input[i+1] - input[i] == 1){
			oneJolt++;
		}
	}
	printf("%d %d\n", oneJolt, threeJolt);
	return oneJolt * threeJolt;
}

int main(){
	std::vector<int> input = get_input("../input_day10.txt");
	int maxVal = solve_one(input);
	printf("%d\n", maxVal);

	solve_two(input);

	return 0;
}
