#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::vector<std::string> get_seats(std::string fileName){
	std::vector<std::string> seats;
	std::ifstream txtFile(fileName, std::ios::in);
	if(txtFile.is_open()){
		std::cout << "Opened: " << fileName << std::endl;
		std::string seat;
		while(getline(txtFile, seat)){
			seats.push_back(seat);
		}
	}
	else{
		std::cout << "Unable to open file: " << fileName << std::endl;
	}
	txtFile.close();
	return seats;
}

int get_seat_id(std::vector<std::string> seats){
	int highest_id = 0;
	std::vector<int> taken_seats;
	// std::cout << seats.size() << std::endl;
	for(int val = 0; val < seats.size(); val++){
		int L = 0, R = 127;
		int inc = 0;
		int mid = L + (R - L) / 2; 
		int row = 0;
		while(mid != 0 && inc <= 6){
			mid = (R - L)/ 2;
			if(seats[val][inc] == 'F'){
				R = R - mid - 1;
			}
			else if(seats[val][inc] == 'B'){
				L = L + mid + 1;
			}
			// std::cout << seats[0][inc] << " " << L << " " << R << " " << mid << std::endl;
			inc++;
		}
		if(seats[val][6] == 'F'){
			row = L;
		}
		else if(seats[val][6] == 'B'){
			row = R;
		}


		L = 0, R = 7;
		inc = 7;
		mid = L + (R - L) / 2; 
		int column = 0;
		while(mid != 0 && inc <= 10){
			mid = (R - L)/ 2;
			if(seats[val][inc] == 'L'){
				R = R - mid - 1;
			}
			else if(seats[val][inc] == 'R'){
				L = L + mid + 1;
			}
			// std::cout << seats[0][inc] << " " << L << " " << R << " " << mid << std::endl;
			inc++;
		}
		if(seats[val][6] == 'F'){
			column = L;
		}
		else if(seats[val][6] == 'B'){
			column = R;
		}
		int id = (row * 8) + column;
		// std::cout << high_id << std::endl;
		if(id > highest_id){
			highest_id = id;
		}
		taken_seats.push_back(id);
	}

	std::sort(taken_seats.begin(), taken_seats.end());
	
	for(int i=12; i < taken_seats.size(); i++){
		// if(taken_seats[i] + 1 != taken_seats[i+1]){
		// 	std::cout << taken_seats[i] << std::endl;
		// }
		std::cout << taken_seats[i] << std::endl;
	}

	return highest_id;
}




int main(){
	std::vector<std::string> seats = get_seats("input_day5.txt");
	get_seat_id(seats);
	return 0;
}