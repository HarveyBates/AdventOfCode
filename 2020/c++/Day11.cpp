#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::vector<std::string> get_input(const char * fileName){
	std::vector<std::string> input;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		printf("Opened: %s\n", fileName);
		std::string tmp;
		while(getline(txtFile, tmp)){
			input.push_back(tmp);
		}
	}
	else{
		printf("There was an error opening %s\n", fileName);
	}
	txtFile.close();
	return input;
}


int calc_seats(std::vector<std::string> input){
	// Solution Part 1 (Answer = 2275)
	std::vector<std::string> output; 
	bool changed = true;
	while(changed){
		// First rule
		for(int i=0; i < input.size(); i++){
			std::string newLine; 
			for(int x=0; x<input[i].length(); x++){
				std::vector<char> adj = {input[i+1][x], input[i][x+1],
					input[i+1][x-1], input[i+1][x+1], input[i-1][x], 
					input[i-1][x+1], input[i-1][x-1], input[i][x-1]};

				if(input[i][x] == 'L'){
					bool noneAdj = true;
					for(int y=0; y < adj.size(); y++){
						if(adj[y] == '#'){
							noneAdj = false;
						}
					}
					if(noneAdj){
						newLine += '#';
					}
					else{
						newLine += input[i][x];
					}
				}
				else{
					newLine += input[i][x];
				}
			}
			output.push_back(newLine);
		}
		
		input = output; 
		output.clear();
		// Second rule
		bool seatChange = false;
		for(int i=0; i < input.size(); i++){
			std::string newLine;
			for(int x=0; x<input[i].length(); x++){
				std::vector<char> adj = {input[i+1][x], input[i][x+1],
					input[i+1][x-1], input[i+1][x+1], input[i-1][x], 
					input[i-1][x+1], input[i-1][x-1], input[i][x-1]};

				if(input[i][x] == '#'){
					int numAdj = 0;
					for(int y=0; y < adj.size(); y++){
						if(adj[y] == '#'){
							numAdj++;
						}
					}
					if(numAdj >= 4){
						newLine += 'L';
						seatChange = true;
					}
					else{
						newLine += input[i][x];
					}
				}
				else{
					newLine += input[i][x];
				}
			}
			output.push_back(newLine);
		}

		if(!seatChange){
			changed = false;
		}

		input = output;
		output.clear();
	}
	int occ = 0;
	for(int i = 0; i < input.size(); i++){
		for(int x = 0; x < input[i].length(); x++){
			if(input[i][x] == '#'){
				occ++;
			}
		}
	}
	return occ;
}


int main(){
	std::vector<std::string> input = get_input("input_day11.txt");
	int occ = calc_seats(input);
	printf("%d\n", occ);
	return 0;
}
