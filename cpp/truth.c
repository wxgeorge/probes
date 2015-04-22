#if 1
#define TRUTH "one"
#endif

#if 0
#define TRUTH "zero"
#endif

#include <stdio.h>
int main() {
	printf("%s is true as per cpp\n", TRUTH);
}
