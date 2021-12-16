#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


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


int main(){
	std::vector<Tunnel> tunnels = readFile("input.txt");
	std::vector<bool> visited(tunnels.size());
	for (int i = 0; i < tunnels.size(); i++){
		if (visited[i] == false){
			std::cout << tunnels[i].cave1 << tunnels[i].cave2 << std::endl;
		}
	}
	return 0;
}
