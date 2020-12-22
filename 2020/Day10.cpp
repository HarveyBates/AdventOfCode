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

int main(){
	std::vector<int> input = get_input("input_day10.txt");
	printf("%d\n", input[0]);
	return 0;
}