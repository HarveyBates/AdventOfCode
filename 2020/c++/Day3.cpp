#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> get_values(std::string fileName){
	std::vector<std::string> route;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::cout << "Opened file: " << fileName << std::endl;
		std::string row;
		while(getline(txtFile, row)){
			route.push_back(row);
		}
	}
	else{
		std::cout << "Unable to open file: " << fileName << std::endl;
	}
	txtFile.close();
	return route;
}

long examine_route(std::vector<std::string> route){
	int steps = 0;
	int trees = 0;
	int one_treverse = 0, two_treverse = 0, three_treverse = 0, 
		four_treverse = 0, five_treverse = 0;
	
	for(int i=0; i < route.size(); i++){
		if(route[i][steps] == '#'){
			one_treverse++;
		}
		steps++;
		if(steps >= 31){
			steps = steps - 31;
		}
	}

	steps = 0;
	for(int i=0; i < route.size(); i++){
		if(route[i][steps] == '#'){
			two_treverse++;
		}
		steps+=3;
		if(steps >= 31){
			steps = steps - 31;
		}
	}

	steps = 0;
	for(int i=0; i < route.size(); i++){
		if(route[i][steps] == '#'){
			three_treverse++;
		}
		steps+=5;
		if(steps >= 31){
			steps = steps - 31;
		}
	}

	steps = 0;
	for(int i=0; i < route.size(); i++){
		if(route[i][steps] == '#'){
			four_treverse++;
		}
		steps+=7;
		if(steps >= 31){
			steps = steps - 31;
		}
	}

	steps = 0;
	for(int i=0; i < route.size(); i+=2){
		if(route[i][steps] == '#'){
			five_treverse++;
		}
		steps+=1;
		if(steps >= 31){
			steps = steps - 31;
		}
	}

	printf("%i %i %i %i %i \n", one_treverse, two_treverse, three_treverse, 
		four_treverse, five_treverse);

	return one_treverse * two_treverse * three_treverse * four_treverse * five_treverse;
}



int main(){
	std::vector<std::string> route = get_values("input_day3.txt");
	int trees = examine_route(route);
	std::cout << trees << std::endl;
	return 0;
}