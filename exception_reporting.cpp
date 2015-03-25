#include <iostream>
#include <exception>

class MyCustomException : public std::exception {
public:
	const char* what() const noexcept {
		return "A custom exception!";
	}
};

int main() {
	MyCustomException c;
	std::cout << "MyCustomException::what() = " << c.what() << "\n";
	throw c;
}