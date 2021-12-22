#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <map>


struct Tunnel {
	std::string cave1;
	std::string cave2;
};

std::vector<Tunnel> readFile(std::string filename){
	std::vector<Tunnel> tunnels;
	std::ifstream txtfile(filename, std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			std::replace(tmp.begin(), tmp.end(), '-', ' ');
			std::stringstream ss(tmp);
			std::string tmp2;
			std::vector<std::string> caves;
			while (ss >> tmp2){
				caves.push_back(tmp2);
			}
			Tunnel t;
			t.cave1 = caves[0];
			t.cave2 = caves[1];
			tunnels.push_back(t);
		}
		txtfile.close();
	}
	return tunnels;
}

struct Routes {
	bool visited;
	std::vector<std::string> neighbours;
};


std::vector<std::vector<std::string>> paths;
std::map<std::string, Routes> routes;
std::vector<std::string> cave;

void visit(Routes route, std::string nodeName){


	cave.push_back(nodeName);
	// Check if lowercase
	for(const auto& c : nodeName){
		if(std::islower(c)){
			routes[nodeName].visited = true;
			break;
		}
	}
	
	for(const auto& node : route.neighbours){
		if(node == "end"){
			cave.push_back(node);
			break;
		}
		if(!routes[node].visited){
			visit(routes[node], node);
			cave.push_back(node);
		}
	}

	for(const auto& p : cave){
		printf("%s ", p.c_str());
	}
	printf("\n\n");

	paths.push_back(cave);
	cave.clear();

}


int solve_one(std::vector<Tunnel> &tunnels){

	for(int i = 0; i < tunnels.size(); i++){
		std::string caveOne = tunnels[i].cave1;
		std::string caveTwo = tunnels[i].cave2;
		if(routes.find(caveOne) == routes.end()){
			std::vector<std::string> neighbours;
			for(int x = 0; x < tunnels.size(); x++){
				if(caveOne == tunnels[x].cave1){
					neighbours.push_back(tunnels[x].cave2);
				}
				else if (caveOne == tunnels[x].cave2){
					neighbours.push_back(tunnels[x].cave1);
				}
			}
			routes[caveOne] = {false, neighbours};
		}
		if(routes.find(caveTwo) == routes.end()){
			std::vector<std::string> neighbours;
			for(int x = 0; x < tunnels.size(); x++){
				if(caveTwo == tunnels[x].cave1){
					neighbours.push_back(tunnels[x].cave2);
				}
				else if (caveTwo == tunnels[x].cave2){
					neighbours.push_back(tunnels[x].cave1);
				}
			}
			routes[caveTwo] = {false, neighbours};
		}
	}

	visit(routes["start"], "start");

	return 0;
}



int main(){
	std::vector<Tunnel> tunnels = readFile("input.txt");
	int answerOne = solve_one(tunnels);
	//printf("%d\n", answerOne);
	return 0;
}
