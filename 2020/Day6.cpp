#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <sstream>

std::vector<std::string> get_forms(std::string fileName){
	std::vector<std::string> forms;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::cout << "Opened: " << fileName << std::endl;
		std::string form;

		while(getline(txtFile, form)){
			std::string tmp = form;
			int lines = 1;
			while(getline(txtFile, form) && !form.empty()){
				tmp += form;
				lines++;
			}
			forms.push_back(std::to_string(lines) + tmp);
		}
	}
	else{
		std::cout << "Unable to open file: " << fileName << std::endl;
	}
	txtFile.close();
	return forms;
}

int parse_forms_p1(std::vector<std::string> forms){
	int sumYes = 0;
	for(unsigned int i=0; i < forms.size(); i++){
		std::string form = forms[i]; 
		std::sort(form.begin(), form.end());
		auto res = std::unique(form.begin(), form.end());
		form = std::string(form.begin(), res);
		std::cout << forms[i] << " " << form << " "
			<< form.length()<< std::endl;
		sumYes += form.length();
	}
	return sumYes;
}

int parse_forms_p2(std::vector<std::string> forms){
	int sumYes = 0;
	for(unsigned int i=0; i < forms.size(); i++){
		int increment = 1;
		std::string form = forms[i]; 
		char identifer = forms[i][0];
		int id_int = identifer - '0';
		std::sort(form.begin(), form.end());
		if(form[0] == '1'){
			for(unsigned int x=1; x<form.length(); x++){
				sumYes++;
			}
		}
		else{
			for(unsigned int x=1; x < form.length(); x++){
				increment = 1;
				for(unsigned int y = x+1; y < form.length(); y++){
					if(form[x] == form[y]){
						increment++;
					}
				}
				if(increment == id_int){
					sumYes++;
				}
			}
		}
	}
	return sumYes;
}

int main(){
	std::vector<std::string> forms = get_forms("input_day6.txt");
	int sumYes = parse_forms_p2(forms);
	std::cout << sumYes << std::endl;
	return 0;
}