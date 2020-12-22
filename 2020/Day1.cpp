#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<int> get_values(){
	std::vector<int> values;
	std::ifstream txtfile("input_day1.txt", std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			values.push_back(std::stoi(tmp));
		}
		txtfile.close();
	}

	else{
		std::cerr << "Error: ";
		std::cout << "Could not open file" << std::endl;
	}
	txtfile.close();
	return values;
}

long solve(std::vector<int> values){
	long output = 0;
	for(int i = 0; i < values.size(); i++){
		for(int x = i+1; x < values.size(); x++){
			for(int y=x+1; y < values.size(); y++){
				if(values[i] + values[x] + values[y] == 2020){
					output = values[i] * values[x] * values[y];
					break;
				}
			}
		}
	}
	return output;
}

int main(){
	std::cout << "Calculating... " << std::endl;
	std::vector<int> values = get_values();
	std::cout << solve(values) << std::endl;
	return 0;
}