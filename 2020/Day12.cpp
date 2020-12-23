
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::vector<std::pair<char, int>> get_input(const char* fileName){
	std::vector<std::pair<char, int>> input;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::string tmp;
		while(getline(txtFile, tmp)){
			input.push_back(std::make_pair(tmp[0], stoi(tmp.substr(1, tmp.length()))));
		}
	}
	else{
		printf("Unable to open: %s\n", fileName);
	}
	return input;
}

int manhattan_distance(std::vector<std::pair<char, int>> input){
	int nsPos = 0, ewPos = 0;

	int heading  = 90;
	for(int i = 0; i < input.size(); i++){
		char direction = input[i].first;
		int distance = input[i].second;

		switch(direction){
			case 'F':
				if(heading == 0){
					nsPos += distance;
				}
				else if(heading == 90){
					ewPos += distance;
				}
				else if(heading == 180){
					nsPos -= distance;
				}
				else if(heading == 270){
					ewPos -= distance;
				}

			case 'N':
				heading = 0;
				nsPos += distance;
			case 'S':
				heading = 180;
				nsPos -= distance;
			case 'E':
				heading = 90;
				ewPos += distance;
			case 'W':
				heading = 270;
				ewPos -= distance;
			case 'L':
				heading -= distance;
			case 'R':
				heading += distance;
		}

		if(heading >= 360){
			heading -= 360;
		}
		else if(heading < 0){
			heading += 360;
		}

		printf("Input: %c%d Heading: %d EWPos: %d NSPos: %d\n", 
			direction, distance,  heading, ewPos, nsPos);
	}
	return nsPos + ewPos;
}



int main(){
	std::vector<std::pair<char, int>> input = get_input("input_day12.txt");
	int md = manhattan_distance(input);
	printf("%d\n", md);
	return 0;
}



