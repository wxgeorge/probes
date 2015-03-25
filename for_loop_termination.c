#include <stdio.h>
int main() {
	int foo;

	printf("Entering loop one!\n");
	for(foo=0; foo<32; foo++) {
		printf("foo = %d\n", foo);
		if(foo == 57) {
			break;
		}
	}
	printf("At the end of loop 1, foo is %d\n", foo);

	printf("\n\n");
	printf("Let's try that again\n");
	printf("\n\n");

	printf("Entering loop two!\n");
	for(foo=0; foo<600; foo++) {
		printf("foo = %d\n", foo);
		if(foo == 57) {
			break;
		}
	}
	printf("At the end of loop 2, foo is %d\n", foo);
}
