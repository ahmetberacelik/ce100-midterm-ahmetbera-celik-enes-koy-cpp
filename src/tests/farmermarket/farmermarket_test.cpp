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
	fputs("1\nEnes Koy\n123456\n100\n\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();

	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, UserAuthenticationLoginInvalidTest) {
	fputs("1\nInvalid User\n123456\n100\n\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();

	EXPECT_FALSE(authResult);
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

TEST_F(FarmermarketTest, HandlePointerSwap) {
	char* a = strdup("hello");
	char* b = strdup("world");
	EXPECT_TRUE(swap(&a, &b));
	EXPECT_STREQ(b, "hello");
	EXPECT_STREQ(a, "world");
	free(a);
	free(b);
}
TEST_F(FarmermarketTest, HandleSorting) {
	char* arr[] = { "banana", "apple", "orange", "mango" };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, n - 1);
	EXPECT_STREQ(arr[0], "apple");
	EXPECT_STREQ(arr[1], "banana");
	EXPECT_STREQ(arr[2], "mango");
	EXPECT_STREQ(arr[3], "orange");
}
TEST_F(FarmermarketTest, FindElement) {
	char* arr[] = { "apple", "banana", "mango", "orange" };
	int n = sizeof(arr) / sizeof(arr[0]);
	EXPECT_EQ(binarySearch(arr, 0, n - 1, "mango"), 2);
	EXPECT_EQ(binarySearch(arr, 0, n - 1, "apple"), 0);
	EXPECT_EQ(binarySearch(arr, 0, n - 1, "notinthelist"), -1);
}
TEST_F(FarmermarketTest, SearchInArray) {
	char* arr[] = { "apple", "banana", "mango", "orange" };
	int n = sizeof(arr) / sizeof(arr[0]);
	EXPECT_TRUE(searchAndPrintResult(arr, n, "banana"));
	EXPECT_FALSE(searchAndPrintResult(arr, n, "cherry"));
}
TEST_F(FarmermarketTest, VendorSearchTest) {
	fputs("1\nAhmet\n3\n", testIn);
	rewind(testIn);

	listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Please enter vendor name: Vendor found: Ahmet\n1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Exiting Listing Of Infos...\n";
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}
TEST_F(FarmermarketTest, ProductSearchTest) {
	fputs("2\nBanana\n3\n", testIn);
	rewind(testIn);

	listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Please enter product name: Product Banana found at vendor Ahmet\n1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Exiting Listing Of Infos...\n";
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}
TEST_F(FarmermarketTest, InvalidOptionTest) {
	fputs("invalid\n3\n", testIn);
	rewind(testIn);

	listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Invalid input, please enter a number.\n1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Exiting Listing Of Infos...\n";
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}
TEST_F(FarmermarketTest, VendorNotFoundTest) {
	fputs("1\nNonExistingVendor\n3\n", testIn);
	rewind(testIn);

	listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Please enter vendor name: Vendor not found.\n1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Exiting Listing Of Infos...\n";
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}
TEST_F(FarmermarketTest, ProductNotFoundTest) {
	fputs("2\nNonExistingProduct\n3\n", testIn);
	rewind(testIn);

	listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Please enter product name: Product not found.\n1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Exiting Listing Of Infos...\n";
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}
TEST_F(FarmermarketTest, InvalidMenuOptionTest) {
	fputs("5\n3\n", testIn);
	rewind(testIn);

	listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	char expectedOutput[] = "1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Invalid option, please try again.\n1. Browse Vendors\n2. Search Product\n3. Exit\nPlease select an option: Exiting Listing Of Infos...\n";
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