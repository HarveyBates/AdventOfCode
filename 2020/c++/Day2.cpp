#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

int min_occ = 0;
int max_occ = 0;
char letter; 
std::string password;

std::vector<std::string> get_passwords(std::string fileName){
	std::vector<std::string> passwords;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::cout << "Opened file..." << std::endl;
		std::string password;
		while(getline(txtFile, password)){
			passwords.push_back(password);
		}
	}
	else{
		std::cerr << "Error: Unable to open file" << std::endl;
	}
	txtFile.close();
	return passwords;
}

void split_line(std::string line){
	std::string tmp;
	std::stringstream ss(line);
	int count = 0;
	while(getline(ss, tmp, ' ')){
		if(count == 0){
			std::stringstream ss0(tmp);
			int occ_count = 0;
			while(getline(ss0, tmp, '-')){
				if(occ_count == 0){
					min_occ = stoi(tmp);
				}
				else if(occ_count == 1){
					max_occ = stoi(tmp);
				}
				occ_count++;
			}
		}
		else if(count == 1){
			letter = tmp[0];
		}
		else if(count == 2){
			password = tmp;
		}
		count++;
	}
}

bool assess_password(int m_occ, int mx_occ, char lett, std::string pass){
	if(pass[m_occ-1] == lett && pass[mx_occ-1] != lett){
		return true;
	}
	else if(pass[m_occ-1] != lett && pass[--mx_occ] == lett){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	std::vector<std::string> passwords = get_passwords("input_day2.txt");
	int num_valid = 0;
	for(int i = 0; i < passwords.size(); i++){
		split_line(passwords[i]);
		bool assess = assess_password(min_occ, max_occ, letter, password);
		if(assess){
			std::cout << "Valid ";
			std::cout << min_occ << " " << max_occ << " " << letter << " " << password << std::endl;
			num_valid++;
		}
		else{
			std::cout << "Invalid ";
			std::cout << min_occ << " " << max_occ << " " << letter << " " << password << std::endl;
		}
	}
	std::cout << num_valid << std::endl;
	return 0;
}
