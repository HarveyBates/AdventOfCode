#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> get_passports(std::string fileName){
	std::vector<std::string> passports;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::cout << "Opened: " << fileName << std::endl;
		std::string passport;
		while(getline(txtFile, passport)){
			std::string tmp = passport + " ";
			while(getline(txtFile, passport) && !passport.empty()){
				tmp += passport + " ";
			}
			passports.push_back(tmp);
		}
	}
	else{
		std::cout << "Unable to open: " << fileName << std::endl;
	}
	txtFile.close();
	return passports;
}

int validate_passports(std::vector<std::string> passports){
	std::string fields[8] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
	std::string eye_colors[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	char hc_chars[16] = {'a', 'b', 'c', 'd', 'e', 'f', '0', '1', '2', '3', 
'4', '5', '6', '7', '8', '9'};
	char pid_chars[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int valid_passports = 0;
	for(int i=0; i < passports.size(); i++){
		int field_inc = 0;
		for(int x=0; x < 8; x++){
			if(passports[i].find(fields[x]) != std::string::npos){
				if(fields[x] == "byr"){
					std::string date = passports[i].substr(passports[i].find("byr:"), 8);
					date = date.substr(4, 8);
					if(stoi(date) >= 1920 && stoi(date) <=2002){
						field_inc++;
					}
				}

				else if(fields[x] == "iyr"){
					std::string isu_date = passports[i].substr(passports[i].find("iyr:"), 8);
					isu_date = isu_date.substr(4, 8);
					if(stoi(isu_date) >= 2010 && stoi(isu_date) <= 2020){
						field_inc++;
					}
				}

				else if(fields[x] == "eyr"){
					std::string exp_date = passports[i].substr(passports[i].find("eyr:"), 8);
					exp_date = exp_date.substr(4, 8);
					if(stoi(exp_date) >= 2020 && stoi(exp_date) <= 2030){
						field_inc++;
					}
				}

				else if(fields[x] == "hgt"){
					std::string height = passports[i].substr(passports[i].find("hgt:"), passports[i].length());
					height = height.substr(0, height.find(" "));
					height = height.substr(4, height.length());
					std::string units = height.substr(height.length() - 2, height.length());
					height = height.substr(0, height.length() - 2);
					if(units == "cm"){
						if(stoi(height) >= 150 && stoi(height) <= 193){
							field_inc++;
						}
					}
					else if(units == "in"){
						if(stoi(height) >= 59 && stoi(height) <= 76){
							field_inc++;
						}
					}
				}
				else if(fields[x] == "hcl"){
					std::string hair_colour = passports[i].substr(passports[i].find("hcl:"), 12);
					hair_colour = hair_colour.substr(4, hair_colour.length());
					char hair_lim = hair_colour[hair_colour.length()-1];
					char hair_hash = hair_colour[0];
					if(hair_lim == ' ' && hair_hash == '#'){
						int hair_inc = 0;
						for(int a=0; a<hair_colour.length(); a++){
							for(int t=0; t<sizeof(hc_chars) / sizeof(char); t++){
								if(hair_colour[a] == hc_chars[t]){
									hair_inc++;
								}
							}
						}
						if(hair_inc == 6){
							field_inc++;
						}
					}
				}
				else if(fields[x] == "ecl"){
					bool found = false;
					std::string eye_colour = passports[i].substr(passports[i].find("ecl:"), 8);
					eye_colour = eye_colour.substr(4, 4);
					for(int e = 0; e < sizeof(eye_colors) / sizeof(std::string); e++){
						if(eye_colors[e] == eye_colour.substr(0, 3) && eye_colour[eye_colour.length()-1] == ' '){
							field_inc++;	
						}
					}
				}
				else if(fields[x] == "pid"){
					std::string pass_id = passports[i].substr(passports[i].find("pid:"), 14);
					pass_id = pass_id.substr(4, 10);
					// std::cout << pass_id <<  std::endl;
					int id_inc = 0;
					for(int p=0; p<pass_id.length(); p++){
						for(int o = 0; o < sizeof(pid_chars) / sizeof(char); o++){
							if(pass_id[p] == pid_chars[o]){
								id_inc++;
							}
						}
					}
					// std::cout <<  " H" <<  id_inc << std::endl;
					if(id_inc == 9){
						field_inc++;
					}

				}
				else if(fields[x] == "cid"){
					field_inc++;
				}
			}
		}

		if(field_inc == 8){
			valid_passports++;
			std::cout << "Valid " << std::endl;
		}
		else if(passports[i].find("cid") == std::string::npos && field_inc == 7){
			valid_passports++;
			std::cout << "Valid" << std::endl;
		}
		else{
			std::cout << "Invalid" << std::endl;
		}
	}
	return valid_passports;
}

int main(){
	std::vector<std::string> passports = get_passports("input_day4.txt");
	int valid_passports = validate_passports(passports);
	std::cout << valid_passports << std::endl;
	return 0;
}