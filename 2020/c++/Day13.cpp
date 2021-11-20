#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>

struct Inputs 
{
	int depart;
	std::vector< int > busses;
	std::vector< int > waitTime;
};


Inputs get_input(const char* filename){
	int depart = 0;
	std::vector< int > busses;
	std::vector< int > waitTime;
	std::ifstream txtFile(filename, std::ios::in);
	if (txtFile.is_open()){
		std::string tmp;
		int idx = 0;
		while(getline(txtFile, tmp)){
			if (idx == 0){
				// Get the minimum departure time
				depart = stoi(tmp);
				std::cout << depart << std::endl;
			} else {
				// Get the intervals between the busses
				int cnt = 0;
				bool nextX = false;
				for(int i = 0; i < tmp.length(); i++){
					if(tmp[i] == 'x'){
						cnt++;
						nextX = true;
					}
					else if (isdigit(tmp[i])){
						if(nextX){
							waitTime.push_back(cnt);
							std::cout << cnt << " ";
							nextX = false;
						}
						cnt = 0;
					}
				} 
				std::cout << std::endl;

				// Get the time of the busses
				std::regex exp("[0-9]{1,}");
				std::smatch res;
				while(regex_search(tmp, res, exp)){
					busses.push_back(stoi(res[0]));
					std::cout << res[0] << " ";
					tmp = res.suffix();
				} 
				std::cout << std::endl;

			}
			idx++;
		}
	}
	else {
		printf("Unable to open: %s\n", filename);
	}
	
	Inputs input;
	input.depart = depart;
	input.busses = busses;
	input.waitTime = waitTime;

	return input;
}


void solve_one(Inputs input){

	int busId;
	int lowestTime;
	bool initalise = false;
	for(int i = 0; i < input.busses.size(); i++){
		int ts = 0;
		while(ts < input.depart){
			ts = ts + input.busses[i];
		}
		if (ts < lowestTime || !initalise){
			lowestTime = ts;
			busId = input.busses[i];
			initalise = true;
		}
	}
	int diff = lowestTime - input.depart;
	int ans = diff * busId;
	std::cout << ans << std::endl;
}


int main(void){
	Inputs input = get_input("../input_day13.txt");
	solve_one(input);
	return 0;
}
