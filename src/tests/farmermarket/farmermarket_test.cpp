#include "gtest/gtest.h"
#include "../../farmermarket/header/farmermarket.h"
class FarmermarketTest : public ::testing::Test {
protected:
	const char* testFilename = "TestUsers.bin";
    const char* inputSimname = "inputSim.txt";
    const char* outputSimname = "outputSim.txt";
	void SetUp() override {
	}
	void TearDown() override {
		remove(testFilename);
        remove(inputSimname);
        remove(outputSimname);
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
    FILE* inputSim = fopen(inputSimname, "w");
    fprintf(inputSim, "1\nAhmet Bera Celik\nqwerty\n");
    fclose(inputSim);

    freopen(inputSimname, "r", stdin);
    freopen(outputSimname, "w", stdout);

    userAuthentication();

    fclose(stdin);
    fclose(stdout);
    freopen("COM", "a", stdout);
    freopen("COM", "r", stdin);

    char expectedOutput[] = "1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease select an option: Please enter your username: Please enter your password: Welcome Ahmet Bera Celik\n";
    char actualOutput[1024];

    FILE* outputSim = fopen(outputSimname, "r");
    fread(actualOutput, sizeof(char), 1023, outputSim);
    fclose(outputSim);
    bool result = (strcmp(expectedOutput, actualOutput) == 1);
    EXPECT_TRUE(result);
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