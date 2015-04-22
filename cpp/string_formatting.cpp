#include <iostream>
#include <string>

int main() {
	std::string my_string = "";

	my_string += "foo bar=";
	my_string += std::to_string(22);

	std::cout << my_string << "\n";
}