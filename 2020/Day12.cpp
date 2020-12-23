
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::vector<std::pair<char, int>> get_input(const char* fileName){
	std::vector<std::pair<char, int>> input;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::string tmp;
		while(getline(txtFile, tmp)){
			input.push_back(std::make_pair(tmp[0], stoi(tmp.substr(1, tmp.length()))));
		}
	}
	else{
		printf("Unable to open: %s\n", fileName);
	}
	return input;
}

int manhattan_distance(std::vector<std::pair<char, int>> input){
	int md = 0, nsPos = 0, ewPos = 0;
	char initDir = 'E';
	for(int i = 0; i < input.size(); i++){
		char direction = input[i].first;
		int distance = input[i].second;

		printf("%c %d\n", input[i].first, input[i].second);
	}
	return md;
}



int main(){
	std::vector<std::pair<char, int>> input = get_input("input_day12.txt");
	int md = manhattan_distance(input);
	printf("%d\n", md);
	return 0;
}



