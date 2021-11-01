#include <iostream>
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// First method using iterator
template<class UnaryFunction>
void recursive_json_iterate(const json& j, UnaryFunction f){
	for(auto item = j.begin(); item != j.end(); ++item){
		if (item->is_structured()){
			recursive_json_iterate(*item, f);
		} else {
			f(item);
		}
	}
}


// Second Method (just return key values)
void json_iterate(const json& j) {
	for (const auto& item : j.items()){
		std::cout << item.key() << ": " << item.value() << std::endl;
	}
}
		

int main() {
	cpr::Response r = cpr::Get(cpr::Url{"https://open.er-api.com/v6/latest/USD"});

	if (r.status_code == 200) {
		json j = json::parse(r.text); 

		// First method
		recursive_json_iterate(j, [](json::const_iterator item) {
			std::cout << item.key() << ": " << item.value() << std::endl;
		});

		// Second method
		json_iterate(j);

	} else {
		std::cout << "Bad Request:" << r.status_code << std::endl;
	}

	return 0;
}
