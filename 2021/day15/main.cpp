#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>


std::vector<int> readFile(std::string filename){
	std::vector<int> output;
	std::ifstream txtfile(filename, std::ios::in);
	if(txtfile.is_open()){
		std::string tmp;
		while(getline(txtfile, tmp)){
			for(int i = 0; i < tmp.length(); i++){
				output.push_back(int(tmp[i]) - 48);
			}
		}
		txtfile.close();
	}
	return output;
}


int solve(std::vector<int>& input, int N){
	// Couldn't solve, modified version for reddit 

	const int width = std::sqrt(input.size());
	const int height = input.size() / width;

	std::priority_queue<std::pair<int, int>> q; // Queue
	q.push({0,0}); // Starting point

	std::vector<int> minDist(input.size() * N * N, INT32_MAX);
	minDist[0] = 0;

	const int dx[4] = {0, 0, -1, 1};
	const int dy[4] = {-1, 1, 0, 0};

	while (!q.empty()){
		// Get the first item in the queue
		auto [val, idx] = q.top();
		// Remove it from the queue
		q.pop();
		int dist = -val;
		for(int i = 0; i < sizeof(dx)/sizeof(int); i++){

			// Check if nx and ny are within limits
			int nx = idx % (width * N) + dx[i];
			int ny = idx / (width * N) + dy[i];
			if(ny < 0 || ny >= (height * N) || nx < 0 || nx >= (width * N)) continue;

			int risk = input[(ny % height) * width + (nx % width)] + (nx / width) + (ny / height);

			if (risk > 9){
				risk -= 9;
			}

			int nDst = dist + risk;
			int nb = nx + ny * (width * N);
			if (nDst < minDist[nb]){
				minDist[nb] = nDst;
				q.push({-nDst, nb});
			}
		}
	}

	return minDist.back();
}


int main(){
	std::vector<int> input = readFile("input.txt");
	int p1 = solve(input, 1);
	std::cout << p1 << std::endl;
	int p2 = solve(input, 5);
	std::cout << p2 << std::endl;
	return 0;
}
