
#include "gtest/gtest.h"
#include "../../farmermarket/header/farmermarket.h"
class FarmermarketTest : public ::testing::Test {
protected:
	std::ostringstream out;
	std::istringstream in;
	const char* testFilename = "TestUsers.bin";
	void SetUp() override {
		out.str("");
		out.clear();
	}
	void TearDown() override {
		remove(testFilename);
	}
	void simulateUserInput(const std::string& input) {
		in.str(input);
		in.clear();
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

TEST_F(FarmermarketTest, UserAuthenticationValidTest) {
	simulateUserInput("1\nAhmet Bera Celik\nqwerty\n");
	EXPECT_TRUE(userAuthentication(in, out));
	std::string expectedOutput = "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Please enter your username: ";
	expectedOutput += "Please enter your password: ";
	expectedOutput += "Welcome Ahmet Bera Celik\n";
	EXPECT_EQ(expectedOutput, out.str());

}

TEST_F(FarmermarketTest, UserAuthenticationInvalidTest) {
	simulateUserInput("1\nInvalid User\nqwerty\n1\nInvalid User\nqwerty\n1\nInvalid User\nqwerty\n");
	EXPECT_FALSE(userAuthentication(in, out));
	std::string expectedOutput = "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Please enter your username: ";
	expectedOutput += "Please enter your password: ";
	expectedOutput += "You entered wrong username or password. Please try again.\n";
	expectedOutput += "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Please enter your username: ";
	expectedOutput += "Please enter your password: ";
	expectedOutput += "You entered wrong username or password. Please try again.\n";
	expectedOutput += "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Please enter your username: ";
	expectedOutput += "Please enter your password: ";
	expectedOutput += "You entered wrong username or password. Please try again.\n";
	expectedOutput += "You have run out of login attempts. See you...\n";
	EXPECT_EQ(expectedOutput, out.str());

}

TEST_F(FarmermarketTest, RegisterUserTest) {
	simulateUserInput("2\nAbuzer\n616161\n");
	EXPECT_TRUE(userAuthentication(in, out));
	std::string expectedOutput = "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Please enter your username: ";
	expectedOutput += "Please enter your password: ";
	expectedOutput += "User registered successfully.\n";
	expectedOutput += "Welcome Abuzer\n";
	EXPECT_EQ(expectedOutput, out.str());

}

TEST_F(FarmermarketTest, GuessModeTest) {
	simulateUserInput("3\n");
	EXPECT_TRUE(userAuthentication(in, out));
}

TEST_F(FarmermarketTest, userAuthenticationMenuSelection) {
	simulateUserInput("1213213\nasdasd\n4\n");
	EXPECT_FALSE(userAuthentication(in, out));
	std::string expectedOutput = "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Invalid option, please try again.\n";
	expectedOutput += "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Invalid input, please enter a number.\n";
	expectedOutput += "1. Login\n";
	expectedOutput += "2. Register\n";
	expectedOutput += "3. Guest Mode\n";
	expectedOutput += "4. Exit Program\n";
	expectedOutput += "Please select an option: ";
	expectedOutput += "Exiting program...\n";
	EXPECT_EQ(expectedOutput, out.str());
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