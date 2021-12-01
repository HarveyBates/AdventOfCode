#include <iostream>
#include <string>
#include <vector>
#include <fstream>


void get_input(const char* filename){
	
	std::ifstream txtFile(filename, std::ios::in);
	if(txtFile.is_open()){
		std::string tmp;
		while(getline(txtFile, tmp)){
			std::cout << tmp << std::endl;
		}
	}

	// return 
}

int main(){
	get_input("../filename.txt");
	return 0;
}
