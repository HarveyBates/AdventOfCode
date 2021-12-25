#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

std::map<std::string, std::vector<std::string>> routes;

std::map<std::string, std::vector<std::string>> readFile(std::string filename){
	std::map<std::string, std::vector<std::string>> routes;
	std::ifstream txtfile(filename, std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			std::replace(tmp.begin(), tmp.end(), '-', ' ');
			std::stringstream ss(tmp);
			std::string cave;
			std::vector<std::string> caves;
			while (ss >> cave){
				caves.push_back(cave);
			}
			if(routes.find(caves[0]) == routes.end()){
				routes[caves[0]].push_back(caves[1]);
			}
			else{
				routes[caves[0]].push_back(caves[1]);
			}
			if(routes.find(caves[1]) == routes.end()){
				routes[caves[1]].push_back(caves[0]);
			}
			else{
				routes[caves[1]].push_back(caves[0]);
			}
		}
		txtfile.close();
	}

	//	Debug input
//	for(const auto& [key, value] : routes){
//		printf("%s: ", key.c_str());
//		for(const auto &n : value){
//			printf("%s ", n.c_str());
//		}
//		printf("\n");
//	}

	return routes;
}

std::vector<std::vector<std::string>> paths;

void visit(std::string cave, 
		std::vector<std::string> neighbours, 
		std::vector<std::string> currentPath, 
		bool &caveTwice){

	currentPath.push_back(cave);

	if(cave == "end"){
		paths.push_back(currentPath);
		return;
	}
	
	for(const auto& node : neighbours){

		if(node == "start"){
			continue;
		}

		bool lower = false;
		// Check if lowercase
		for(const auto& c : node){
			if(std::islower(c)){
				lower = true;
				break;
			}
		}

		if(!lower || std::find(currentPath.begin(), currentPath.end(), node) == currentPath.end()){
			visit(node, routes[node], currentPath, caveTwice);
			std::remove(currentPath.end() - 1, currentPath.end(), node);
		}
	}
}


int solve_one(std::map<std::string, std::vector<std::string>> &routes){

	std::vector<std::string> currentPath;
	bool caveTwice = false;

	visit("start", routes["start"], currentPath, caveTwice);

	for(const auto& p: paths){
		for(const auto& r : p){
			if(r.length() != 0){
				printf("%s ", r.c_str());
			}
		}
		printf("\n");
	}

	return paths.size();
}



int main(){
	routes = readFile("input.txt");
	int answerOne = solve_one(routes);
	printf("%d\n", answerOne);
	return 0;
}
