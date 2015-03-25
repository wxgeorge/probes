#include <iostream>

int counter=0;

int loop_limit() {
	counter++;
	return counter;
}

int main() {
	// how long will I run?
	for (int i=0; i<loop_limit(); i++) {
		std::cout << "iteration " << i << "!\n";
	}
}