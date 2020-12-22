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
	// If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
	// If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
	// Otherwise, the seat's state does not change.

	std::vector<std::string> output;

	for(int i=0; i < input.size(); i++){
		for(int x=0; x<input[i].length(); x++){
			std::vector<char> adj = {input[i+1][x], input[i][x+1],
				input[i+1][x-1], input[i+1][x+1]};

			if(input[i][x] == 'L'){
				bool noneAdj = true;
				for(int y=0; y < adj.size(); y++){
					if(adj[y] == '#'){
						noneAdj = false;
					}
				}
				if(noneAdj){
					input[i][x] = '#';
				}
			}
		}
	}

	output = input;
	bool seatChange = false;
	for(int i=0; i < input.size(); i++){
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
					output[i][x] = 'L';
					seatChange = true;
				}
			}
		}
	}

	for(int i =0; i < output.size(); i++){
		printf("%s\n", output[i].c_str());
	}
	return 0;
}


int main(){
	std::vector<std::string> input = get_input("input_day11.txt");
	calc_seats(input);
	return 0;
}
