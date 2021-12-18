#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

struct Rules {
	std::string characters;
	char insertion;
};


std::vector<Rules> readFile(std::string filename){
	std::vector<Rules> rules;
	std::ifstream txtfile(filename, std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			std::stringstream ss(tmp);
			std::string tmp2;
			std::vector<std::string> parts;
			while (ss >> tmp2){
				parts.push_back(tmp2);
			}
			Rules r;
			r.characters = parts[0];
			r.insertion = parts[2][0];
			rules.push_back(r);
		}
		txtfile.close();
	}
	return rules;
}

int solve_one(std::vector<Rules>& rules){
	std::string pTemp = "KHSSCSKKCPFKPPBBOKVF";

	std::string tmp = pTemp;
	for(int i = 0; i < 10; i++){
		for (int p = pTemp.length()-1; p >= 0; p--){
			for (int r = 0; r < rules.size(); r++){
				if (pTemp[p] == rules[r].characters[0] && pTemp[p+1] == rules[r].characters[1]){
					// Match - append to insertion array
					tmp.insert(p+1, std::string(1, rules[r].insertion));
				}
			}
		}
		pTemp = tmp;
	}

	// Evaluate - occurances
	int maxOcc = std::count(pTemp.begin(), pTemp.end(), 'N');
	int minOcc = std::count(pTemp.begin(), pTemp.end(), 'N');
	std::vector<char> pTempChars(pTemp.begin(), pTemp.end());
	std::vector<char> checked;
	for(int i = 0; i < pTempChars.size(); i++){
		if (find(checked.begin(), checked.end(), pTempChars[i]) == checked.end()){
			int occ = std::count(pTemp.begin(), pTemp.end(), pTempChars[i]);
			if (occ > maxOcc){
				maxOcc = occ;
			}
			if (occ < minOcc){
				minOcc = occ;
			}
			checked.push_back(pTempChars[i]);
		}
	}

	return maxOcc - minOcc;
}


int main(){
	std::vector<Rules> rules = readFile("input.txt");
	int p1 = solve_one(rules);
	std::cout << p1 << std::endl;
	return 0;
}
