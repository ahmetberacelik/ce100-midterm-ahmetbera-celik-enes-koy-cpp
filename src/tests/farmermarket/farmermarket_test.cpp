#include "gtest/gtest.h"
#include "../../farmermarket/header/farmermarket.h"
class FarmermarketTest : public ::testing::Test {
protected:
	const char* testFilename = "TestUsers.bin";
	FILE* testIn;
	FILE* testOut;
	char testOutputBuffer[1024];
	void SetUp() override {
		testIn = tmpfile();
		testOut = tmpfile();
	}
	void TearDown() override {
		fclose(testIn);
		fclose(testOut);
		remove(testFilename);
	}
	void ReadTestOutput() {
		rewind(testOut);
		fread(testOutputBuffer, sizeof(testOutputBuffer), 1, testOut);
	}
};

TEST_F(FarmermarketTest, SaveandAuthenticateUserTest) {
	User testUser = { "TestUser", "123456" };
	int result = saveUser(&testUser, testFilename);
	int result2 = authenticateUser("TestUser", "123456", testFilename);
	EXPECT_EQ(result2, 1);
	EXPECT_EQ(result, 1);
}

TEST_F(FarmermarketTest, InvalidAuthenticateUserTest) {
	int result2 = authenticateUser("TestUser", "123456", testFilename);
	EXPECT_EQ(result2, -1);
}

TEST_F(FarmermarketTest, UserAuthenticationTest) {
	fputs("1\nEnes Koy\n123456\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutout[1024] = "Welcome Enes Koy\n";
	EXPECT_TRUE(authResult);
	EXPECT_TRUE(strstr(testOutputBuffer, expectedOutout) != NULL);
}
/**
 * @brief The main function of the test program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the program.
 */
int main(int argc, char** argv) {
#ifdef ENABLE_FARMERMARKET_TEST
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}