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
		memset(testOutputBuffer, 0, sizeof(testOutputBuffer));
		size_t bytesRead = fread(testOutputBuffer, 1, sizeof(testOutputBuffer) - 1, testOut);
		testOutputBuffer[bytesRead] = '\0';
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

TEST_F(FarmermarketTest, UserAuthenticationLoginTest) {
	fputs("1\nEnes Koy\n123456\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Please enter your username:"
		" Please enter your password: Welcome Enes Koy\n";
	EXPECT_TRUE(authResult);
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}

TEST_F(FarmermarketTest, UserAuthenticationLoginInvalidTest) {
	fputs("1\nInvalid User\n123456\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Please enter your username: Please enter your password: You entered wrong username or password. Please try again.\n"
		"1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Please enter your username: Please enter your password: You entered wrong username or password. Please try again.\n"
		"1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Please enter your username: Please enter your password: You entered wrong username or password. Please try again.\n"
		"You have run out of login attempts. See you...\n";
	EXPECT_FALSE(authResult);
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}

TEST_F(FarmermarketTest, UserAuthenticationRegisterTest) {
	fputs("2\nNew User\n123456\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Please enter your username: Please enter your password: User registered successfully.\nWelcome New User\n";
	EXPECT_TRUE(authResult);
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}

TEST_F(FarmermarketTest, LoginGuestModeTest) {
	fputs("3\n", testIn);
	rewind(testIn);
	bool authResult = userAuthentication(testIn, testOut);
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ExitUserAuthenticationTest) {
	fputs("4\n", testIn);
	rewind(testIn);
	bool authResult = userAuthentication(testIn, testOut);
	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, UserAuthenticationInvalidInputTest) {
	fputs("invalid\n4\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Invalid option, please try again.\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Exiting program...\n";
	EXPECT_FALSE(authResult);
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
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