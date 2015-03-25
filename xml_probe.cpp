#include "gtest/gtest.h"

class MyTestFixture : public ::testing::Test {
public:
	static void SetUpTestCase() {
		RecordProperty("context", "SetUpTestCase");
	}

	void SetUp() {
		RecordProperty("context", "SetUp");
	}
};

TEST_F(MyTestFixture, some_test) {
	RecordProperty("context", "MyTestFixture.some_test");
	ASSERT_TRUE(false) << "A forced failure!";
}