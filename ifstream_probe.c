#include <fstream>
#include <iostream>

int main() {
	std::string file_name = "foo";
	std::ifstream my_file(file_name.data(), std::ios::in);
	char some_buffer[400];
	my_file.read(some_buffer, 200);
	std::cout << some_buffer;
}