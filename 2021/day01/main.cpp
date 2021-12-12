// g++ -o main main.cpp && ./main
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::vector<int> readFile(std::string filename){
	std::vector<int> values;
	std::ifstream txtfile(filename, std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			values.push_back(std::stoi(tmp));
		}
		txtfile.close();
	}
	return values;
}


int solve_one(std::vector<int> values){	
	int result = 0;
	for (int i = 0; i < values.size() - 1; i++){
		if (values[i] < values[i+1]){
			result++;
		}
	}
	return result;
}


int solve_two(std::vector<int> values){
	int result = 0;
	int prevSum = values[0] + values[1] + values[2];
	for (int i = 1; i < values.size() - 2; i++){
		int sum = values[i] + values[i+1] + values[i+2];
		if (sum > prevSum){
			result++;
		}
		prevSum = sum;
	}
	return result;
}


int main(){
	std::vector<int> values = readFile("input.txt");
	std::cout << solve_one(values) << std::endl;
	std::cout << solve_two(values) << std::endl;
	return 0;
}
