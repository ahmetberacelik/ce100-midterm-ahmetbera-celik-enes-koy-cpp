
#include "gtest/gtest.h"
#include "../../farmermarket/header/farmermarket.h"

class FarmermarketTest : public ::testing::Test {
protected:
	std::ostringstream out;
	std::istringstream in;
	void SetUp() override {
		out.str("");
		out.clear();
	} 
	void simulateUserInput(const std::string& input) {
		in.str(input);
		in.clear();
	}
};
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