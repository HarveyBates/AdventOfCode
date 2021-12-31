#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>


std::map<std::string, char> readFile(std::string filename){
	std::map<std::string, char> rules;
	std::ifstream txtfile(filename, std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			std::stringstream ss(tmp);
			std::string tmp2;
			std::vector<std::string> parts;
			while (ss >> tmp2){
				parts.push_back(tmp2);
			}
			rules[parts[0]] = parts[2][0];
		}
		txtfile.close();
	}
	return rules;
}


long solve_two(std::map<std::string, char> &rules){
	std::string pTemp = "KHSSCSKKCPFKPPBBOKVF";

	std::map<std::string, long> occ; // Occurances

	// Initalise rules
	for(const auto &[key, value] : rules){
		occ[key] = 0;
	}

	// Find occurances from initial string
	for(int i = 0; i < pTemp.length()-1; i++){
		std::string cmb = std::string() + pTemp[i] + pTemp[i+1];
		occ[cmb] += 1;
	}

	std::map<std::string, long> tmpOcc;
	for(int l = 0; l < 10; l++){
		for(const auto &[key, value] : occ){
			if(value > 0){
				std::string newLeft = std::string() + key[0] + rules[key];
				std::string newRight = std::string() + rules[key] + key[1];
				tmpOcc[newLeft] += value;
				tmpOcc[newRight] += value;
				if(tmpOcc.find(key) != tmpOcc.end()){
					if(newLeft != key){
						tmpOcc[key] -= value;
					}
					else if(newRight != key){
						tmpOcc[key] -= value;
					}
				}
				else{
					tmpOcc[key] = 0;
				}
			}
			if(tmpOcc.find(key) == tmpOcc.end()){
				tmpOcc[key] = 0;
			}
		}

		for(const auto &[key, value] : occ){
			occ[key] = tmpOcc[key];
		}

	}

	std::vector<char> uChar;
	for(const auto &[key, value] : occ){
		if(std::find(uChar.begin(), uChar.end(), key[0]) == uChar.end()){
			uChar.push_back(key[0]);
		}
		if(std::find(uChar.begin(), uChar.end(), key[1]) == uChar.end()){
			uChar.push_back(key[1]);
		}
	}

	long sumMax = 0;
	long sumMin = 0;
	bool sumSet = false;
	for(const auto& c : uChar){
		long sum = 0;
		for(const auto &[key, value] : occ){
			if(key[0] == c || (key[0] == c && key[1] == c)){
				sum += value;
			}
		}
		if(!sumSet){
			sumMax = sum + 1;
			sumMin = sum;
			sumSet = true;
		}
		else{
			if(sum > sumMax){
				sumMax = sum;
			}
			if(sum < sumMin){
				sumMin = sum;
			}
		}
	}
	printf("Min: %ld Max: %ld\n", sumMin, sumMax);

	return sumMax - sumMin;
}


int main(){
	std::map<std::string, char> rules = readFile("input.txt");
	long p2 = solve_two(rules);
	printf("%ld\n", p2);
	return 0;
}
