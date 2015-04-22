#include <stdio.h>

int stack_inspector(unsigned int n_elements) {
	unsigned int bonanza = n_elements*3 + 7;
	int stack[bonanza];

	int accumulator = 0;
	for(int i=0; i<n_elements*3; i++) {
		accumulator += stack[i];
	}

	return accumulator;
}

int main() {
	printf("%d\n", stack_inspector(25));
}