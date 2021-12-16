#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> get_input(std::string fileName){
	std::vector<std::string> instructions;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		printf("Opened: %s\n", fileName.c_str());
		std::string tmp;
		while(getline(txtFile, tmp)){
			instructions.push_back(tmp);
		}
	}
	txtFile.close();
	return instructions;
}

int accumulator(std::vector<std::string> instructions){
	int acc = 0;
	int initial_acc = stoi(instructions[1].substr(5,instructions[0].length()));
	int incre = 0;
	bool first = true;
	for(int i=0; i < instructions.size(); i++){

		std::string instruct = instructions[i].substr(0, 3);
		std::string value = instructions[i].substr(5, instructions[i].length());
		char op = instructions[i][4];
		
		if(instruct == "jmp"){
			if(op == '+'){
				i += stoi(value) - 1;
			}
			else if(op == '-'){
				i -= stoi(value) + 1;
			}
		}

		else if(instruct == "acc"){
			if(op == '+'){
				acc += stoi(value);
			}
			else if(op == '-'){
				acc -= stoi(value);
			}
		}

		if (i == initial_acc && !first){
			break;
		}
		first = false;

		printf("Index: %d %s %c %d Acc=%d %d\n", incre, instruct.c_str(), op, stoi(value), acc, i+1);
		incre++;

	}
	return acc;
}


int main(){
	std::vector<std::string> instructions = get_input("../input_day8.txt");
	int acc = accumulator(instructions);
	printf("%d\n", acc);
}
