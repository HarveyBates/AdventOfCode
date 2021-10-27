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
	bool initial_loop = false;
	int initial_acc = -1;
	// int incre = 0;
	for(int i=0; i < instructions.size(); i++){
		if(i == initial_acc){
			break;
		}
		std::string instruct = instructions[i].substr(0, 3);
		std::string value = instructions[i].substr(5, 7);
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
			if(!initial_loop){
				initial_loop = true;
				initial_acc = i;
			}
			if(op == '+'){
				acc += stoi(value);
			}
			else if(op == '-'){
				acc -= stoi(value);
			}
		}
		// if(incre >= 10){
		// 	break;
		// }
		// incre++;
		printf("%s %c %d Acc=%d %d\n", instruct.c_str(), op, stoi(value), acc, i);
	}
	return acc;
}


int main(){
	std::vector<std::string> instructions = get_input("input_day8.txt");
	int acc = accumulator(instructions);
	printf("%d\n", acc);
}