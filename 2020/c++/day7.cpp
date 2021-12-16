#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::string> get_input(std::string fileName){
	std::vector<std::string> bags;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		printf("Opened: %s\n", fileName.c_str());
		std::string line;
		while(getline(txtFile, line)){
			bags.push_back(line);
		}
	}
	else{
		printf("Could not open: %s\n", fileName.c_str());
	}
	txtFile.close();
	return bags;
}

int gold_bag_compatiable(std::vector<std::string> bags){
	int compat = 0;
	std::vector<std::string> compat_bags;
	for(int i=0; i < bags.size(); i++){
		std::string bag = bags[i];
		if(bag.find("shiny gold bag") != std::string::npos){
			if(bag.find("shiny gold bags contain") == std::string::npos){
				std::string delim = "bags";
				std::string bag_id = bag.substr(0, bag.find(delim));
				// printf("%s\n", bag_id.c_str());
				// printf("%s\n", bag.c_str());
				compat_bags.push_back(bag_id);
			}
		}
	}
	for(int i=0; i < bags.size(); i++){
		std::string bag = bags[i];
		bool found = false;
		for(int x=0; x<compat_bags.size(); x++){
			if(!found && bag.find(compat_bags[x]) != std::string::npos){
				compat++;
				printf("%s\n", bag.c_str());
				found = true;
			}
		}
	}
	return compat;
}


int main(){
	std::vector<std::string> bags = get_input("input_day7.txt");
	int compat = gold_bag_compatiable(bags);
	printf("%d\n", compat);
	return 0;
}