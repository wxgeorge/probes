#include <iostream>
#include <tuple>

typedef std::tuple<int, bool> MyTuple;

int main() {
	MyTuple m;

	m = std::make_tuple(22, true);
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";

	m = std::make_tuple(34, false);
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";
	
	m = 1;
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";
}
