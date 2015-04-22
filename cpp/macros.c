#include <stdio.h>

#define DEFAULT_STRING "foo"

#ifndef MY_STRING
#define MY_STRING DEFAULT_STRING
#endif

#define FUN_PRINT_TIME() printf("It's fun print time! MY_STRING=%s\n", MY_STRING)

int main() {
	FUN_PRINT_TIME();

	#undef MY_STRING
	#define MY_STRING "Poop!"

	FUN_PRINT_TIME();

	#undef MY_STRING
	// won't compile!
	// FUN_PRINT_TIME();
	// (undeclared idenitifer MY_STRING!)
}