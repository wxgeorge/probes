#include "gtest/gtest.h"
#include <stdio.h>

#define ASSERT(x) ASSERT_TRUE(x)

TEST(Foo, foo) {
	FILE *fp = fopen("my_file", "w+");

	ASSERT(fp != NULL);

	std::cout << "Before write: "; std::cout << "ftell(fp)=" << ftell(fp) << "\n";
	ASSERT(fprintf(fp, "Hi there! I'm writing to a file!\n") != 0);
	std::cout << "After write: "; std::cout << "ftell(fp)=" << ftell(fp) << "\n";

	int message_size = ftell(fp);

	fseek(fp, 0, SEEK_SET);

	char my_buffer[2*message_size];
	std::cout << "Before read: "; std::cout << "ftell(fp)=" << ftell(fp) << "\n";
	int bytes_read = fread(my_buffer, 1, message_size, fp);
	std::cout << "After read: "; std::cout << "ftell(fp)=" << ftell(fp) << "\n";

	ASSERT_EQ(message_size, bytes_read);
	my_buffer[message_size] = 0;

	std::cout << "Here's what I read back from the file: " << "\n";
	std::cout << "<<<BEGIN>>>\n";
	std::cout << my_buffer; 
	std::cout << "<<<END>>>\n";

	fseek(fp, 10, SEEK_SET);
	fprintf(fp, "BOOGA!");

	fseek(fp, 0, SEEK_SET);
	fread(my_buffer, 1, message_size,fp);
	std::cout << "Here's what I read back from the file: " << "\n";
	std::cout << "<<<BEGIN>>>\n";
	std::cout << my_buffer; 
	std::cout << "<<<END>>>\n";

	ASSERT(fclose(fp) != EOF);
}