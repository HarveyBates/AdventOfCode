#include <iostream>
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


// First method - async function single call
void call_async_get() {
	cpr::AsyncResponse res = cpr::GetAsync(cpr::Url{"http://www.httpbin.org/get"});
	cpr::Response r = res.get();
	if (r.status_code == 200) {
		json j = json::parse(r.text);
		std::cout << j.dump(4) << std::endl;
	} else {
		std::cout << "Bad Request:" << r.status_code << std::endl;
	}
}


// Second method - async function multiple calls
std::vector<std::future<cpr::Response>> call_async_get_many() {

	std::vector<std::future<cpr::Response>> container{};

	cpr::Url url = cpr::Url{"http://www.httpbin.org/get"};

	for (int i = 0; i < 10; ++i){
		container.emplace_back(cpr::GetAsync(url, cpr::Parameters{{"i", std::to_string(i)}}));
	}

	return container;
}


int main() {
	std::vector<std::future<cpr::Response>> container = call_async_get_many();

	for(std::future<cpr::Response>& res: container) {
		cpr::Response r = res.get();
		if (r.status_code == 200) {
			json j = json::parse(r.text);
			std::cout << j.dump(4) << std::endl;
		} else {
			std::cout << "Bad Request:" << r.status_code << std::endl;
		}
	}

	return 0;
}
