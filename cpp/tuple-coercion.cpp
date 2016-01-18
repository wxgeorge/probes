#include <iostream>
#include <tuple>

typedef std::tuple<int, bool> MyTuple;

class MyClass {
public:
	MyClass(int i) : i(i) {};
private:
	int i;
};

int main() {
	MyTuple m;

	m = std::make_tuple(22, true);
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";

	m = std::make_tuple(34, false);
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";
	
	m = 1;
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";

	// The following does compile.
	m = false;
	//	Here the compiler is following the types bool -> int -> std::tuple<int, bool>
	std::cout << std::get<0>(m) << ", " << std::get<1>(m) << "\n";

	// Uncomment me for a compilation error!

	// std::tuple<int, MyClass> my_other_tuple = 1;

	// 	Here, the compiler fill in coerccion of int to std::tuple<int, MyClass>
	// 	without a default constructor for MyClass.
}
