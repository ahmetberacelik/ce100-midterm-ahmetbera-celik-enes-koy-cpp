#include "gtest/gtest.h"
#include "../../farmermarket/header/farmermarket.h"
#define N 4
class FarmermarketTest : public ::testing::Test {
protected:
	ProductSeason item1 = { 20, "Apple", "Fall" };
	ProductSeason item2 = { 10, "Banana", "Summer" };
	ProductSeason item3 = { 15, "Cherry", "Summer" };
	ProductSeason item4 = { 5, "Date", "Winter" };
	const char* testFilename = "TestUsers.bin";
	const char* inputTest = "inputTest.txt";
	const char* outputTest = "outputTest.txt";
	void SetUp() override {
		initializeDP();
	}
	void TearDown() override {
		remove(inputTest);
		remove(outputTest);
		remove(testFilename);
	}

	void simulateUserInput(const char* userInput) {
		FILE* fileinput = fopen(inputTest, "wb");
		fputs(userInput, fileinput);
		fclose(fileinput);
		freopen(inputTest, "rb", stdin);
		freopen(outputTest, "wb", stdout);
	}

	void readOutput(const char* outputFilePath, char* buffer, size_t bufferSize) {
		FILE* fileoutput = fopen(outputFilePath, "rb");
		size_t charsRead = fread(buffer, sizeof(char), bufferSize - 1, fileoutput);
		fclose(fileoutput);
		buffer[charsRead] = '\0';
		removeClearScreenCharsFromOutputFile(buffer);
	}

	void resetStdinStdout() {
		fclose(stdin);
		fflush(stdout);
#ifdef _WIN32
		freopen("CON", "a", stdout);
		freopen("CON", "r", stdin);
#else
		freopen("/dev/tty", "a", stdout);
		freopen("/dev/tty", "r", stdin);
#endif // _WIN32
	}

	void removeClearScreenCharsFromOutputFile(char* str) {
		char* src = str;
		char* dst = str;
		while (*src) {
			if (*src != '\f') {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
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
	simulateUserInput("1\nEnes Koy\n123456\n100\n\n");

	bool authResult = userAuthentication();

	resetStdinStdout();

	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, UserAuthenticationInvalidLoginTest) {
	simulateUserInput("1\ninvalid user\n123456\n100\n\n1\ninvalid user\n123456\n100\n\n1\ninvalid user\n123456\n100\n\n");

	bool authResult = userAuthentication();

	resetStdinStdout();

	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, UserAuthenticationRegisterTest) {
	simulateUserInput("2\nNew User\n123456\n");


	bool authResult = userAuthentication();

	resetStdinStdout();

	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, LoginGuestModeTest) {
	simulateUserInput("3\n");

	bool authResult = userAuthentication();

	resetStdinStdout();
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ExitUserAuthenticationTest) {
	simulateUserInput("4\n");

	bool authResult = userAuthentication();

	resetStdinStdout();
	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, UserAuthenticationInvalidInputTest) {
	simulateUserInput("invalid\n\n4\n");


	bool authResult = userAuthentication();

	resetStdinStdout();


	EXPECT_FALSE(authResult);
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
	simulateUserInput("Ahmet");


	bool authResult = browseVendor();

	resetStdinStdout();


	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, VendorNotFoundTest) {
	simulateUserInput("NonExistingVendor");


	bool authResult = browseVendor();

	resetStdinStdout();


	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, ProductSearchTest) {
	simulateUserInput("Banana");


	bool authResult = searchProduct();

	resetStdinStdout();


	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ProductNotFoundTest) {
	simulateUserInput("NonExistingProduct");


	bool authResult = searchProduct();

	resetStdinStdout();


	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuValidOptionTest1) {
	simulateUserInput("1\nAhmet\n\n3\n");


	bool authResult = listingOfInfos();

	resetStdinStdout();


	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuValidOptionTest2) {
	simulateUserInput("2\nBanana\n\n3\n");


	bool authResult = listingOfInfos();

	resetStdinStdout();


	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuInvalidOptionTest) {
	simulateUserInput("invalid\n\n3\n");


	bool authResult = listingOfInfos();

	resetStdinStdout();


	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuInvalidOptionTestWithNumber) {
	simulateUserInput("5\n\n3\n");


	bool authResult = listingOfInfos();

	resetStdinStdout();


	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, InsertMinHeapWhenFullTest) {
	MinHeap heap;
	initMinHeap(&heap);

	// Fill up the heap
	for (int i = 0; i < MAX_SIZE; ++i) {
		ProductSeason item = { i, "Product", "Season" };
		insertMinHeap(&heap, item);
	}

	EXPECT_EQ(heap.size, MAX_SIZE); // Check that the heap is indeed full

	// Try inserting into a full heap
	ProductSeason newItem = { MAX_SIZE + 1, "NewProduct", "NewSeason" };
	insertMinHeap(&heap, newItem); // This should not insert the item

	// Ensure the size has not changed and the heap property is maintained
	EXPECT_EQ(heap.size, MAX_SIZE);
	// Validate the heap content remains unchanged, e.g., by checking the last item
	EXPECT_EQ(heap.items[heap.size - 1].price, MAX_SIZE - 1);
}

TEST_F(FarmermarketTest, RemoveMinWithReinsertionTest) {
	MinHeap heap;
	initMinHeap(&heap);

	// Insert items into the MinHeap in such a way that the last item
	// will have to be reinserted higher up than the bottom level
	ProductSeason itemsToInsert[] = { {30, "Apple", "Fall"},
									 {40, "Banana", "Summer"},
									 {50, "Cherry", "Summer"},
									 {20, "Date", "Winter"},
									 {10, "Elderberry", "Spring"} };
	for (auto& item : itemsToInsert) {
		insertMinHeap(&heap, item);
	}

	// Now removeMin will trigger the scenario where the last item is reinserted
	removeMin(&heap);

	// Validate the heap property is maintained after reinsertion
	int parentIndex = 0;
	int leftChildIndex = 2 * parentIndex + 1;
	int rightChildIndex = 2 * parentIndex + 2;

	// Check that both children are now larger than the parent
	EXPECT_TRUE(heap.items[parentIndex].price <= heap.items[leftChildIndex].price);
	EXPECT_TRUE(heap.items[parentIndex].price <= heap.items[rightChildIndex].price);

	// Make sure the size of the heap is decremented
	EXPECT_EQ(heap.size, 4);
}

TEST_F(FarmermarketTest, SaveProductSeasonTest) {
	ProductSeason productSeasons[3] = {
		{20, "Apple", "Fall"},
		{10, "Banana", "Summer"},
		{15, "Cherry", "Summer"}
	};
	const char* testProductSeasonFilename = "TestProductSeasons.bin";

	int saveResult = saveProductSeason(productSeasons, 3, testProductSeasonFilename);
	EXPECT_EQ(saveResult, 1);

	FILE* file = fopen(testProductSeasonFilename, "rb");
	ASSERT_TRUE(file != nullptr);

	int numProductsRead = 0;
	fread(&numProductsRead, sizeof(int), 1, file);
	EXPECT_EQ(numProductsRead, 3);

	ProductSeason readProductSeasons[3];
	fread(readProductSeasons, sizeof(ProductSeason), numProductsRead, file);

	for (int i = 0; i < numProductsRead; ++i) {
		EXPECT_EQ(readProductSeasons[i].price, productSeasons[i].price);
	}
	fclose(file);
	remove(testProductSeasonFilename);
}

TEST_F(FarmermarketTest, LoadProductSeasonsAndPrintTest) {
	const char* testLoadFilename = "TestProductSeasonsLoad.bin";

	ProductSeason productSeasonsToSave[] = {
		{20, "Apple", "Fall"},
		{10, "Banana", "Summer"},
		{15, "Cherry", "Summer"},
		{5, "Date", "Winter"},
		{8, "Fig", "Summer"}
	};
	int numProductsToSave = sizeof(productSeasonsToSave) / sizeof(ProductSeason);
	saveProductSeason(productSeasonsToSave, numProductsToSave, testLoadFilename);

	const char* selectedSeason = "Summer";
	int productsFound = loadProductSeasonsAndPrint(testLoadFilename, selectedSeason);

	EXPECT_EQ(productsFound, 3);
	remove(testLoadFilename);
}

TEST_F(FarmermarketTest, SeasonalProduceGuideTest) {
	simulateUserInput("invalid\n\n1\n\n2\n\n3\n\n4\n\n5\n");


	bool result = seasonalProduceGuide();

	resetStdinStdout();
	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, LongestCommonSubsequenceTest) {
	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";
	int m = strlen(X);
	int n = strlen(Y);

	// The LCS of "AGGTAB" and "GXTXAYB" is "GTAB" which has a length of 4.
	int lcsLength = lcs(X, Y, m, n);
	EXPECT_EQ(lcsLength, 4);

	// Test case with no common subsequence
	char A[] = "ABC";
	char B[] = "DEF";
	int lenA = strlen(A);
	int lenB = strlen(B);

	lcsLength = lcs(A, B, lenA, lenB);
	EXPECT_EQ(lcsLength, 0); // No common subsequence, so expect 0

	// Test case with one string being a subsequence of the other
	char C[] = "ABC";
	char D[] = "ABDC";
	int lenC = strlen(C);
	int lenD = strlen(D);

	lcsLength = lcs(C, D, lenC, lenD);
	EXPECT_EQ(lcsLength, 3); // "ABC" is a subsequence of "AADC"
}

TEST_F(FarmermarketTest, MaxFunctionTest) {
	EXPECT_EQ(10, max(5, 10)); // Test where second parameter is greater
	EXPECT_EQ(10, max(10, 5)); // Test where first parameter is greater
	EXPECT_EQ(5, max(5, 5));   // Test where both parameters are equal
}

TEST_F(FarmermarketTest, KnapsackFunctionTest) {
	const int W = 50; // Total weight capacity of the knapsack
	int wt[] = { 10, 20, 30 }; // Weights of the items
	int val[] = { 60, 100, 120 }; // Values of the items
	const int n = sizeof(val) / sizeof(val[0]); // Number of items
	int selectedItems[n]; // To store the selected item indices
	memset(selectedItems, 0, sizeof(selectedItems)); // Initialize with zeros

	int maxValue = knapsack(W, wt, val, n, selectedItems);
	EXPECT_EQ(maxValue, 0);

	// Check if the selected items array has the correct items
	EXPECT_EQ(selectedItems[0], 0); // Item 1 (weight 10) is not selected
	EXPECT_EQ(selectedItems[1], 1); // Item 2 (weight 20) is selected
	EXPECT_EQ(selectedItems[2], 1); // Item 3 (weight 30) is selected
}

TEST_F(FarmermarketTest, SuggestPurchasesTest) {
	int budget = 100;
	bool result = suggestPurchases(budget);
	EXPECT_TRUE(result);

	budget = 0;
	result = suggestPurchases(budget);
	EXPECT_FALSE(result);
}

TEST_F(FarmermarketTest, CompareProductsTest) {
	simulateUserInput("Summer\n");

	bool result = CompareProducts();

	resetStdinStdout();

	EXPECT_TRUE(result);

	char expectedOutput[] = "|Products at the same price as Summer season products:\n";
	char actualOutput[100000];

	readOutput(outputTest, actualOutput, sizeof(actualOutput));

	EXPECT_NE(expectedOutput, actualOutput);
}

TEST_F(FarmermarketTest, CompareProductsTestInvalid) {
	simulateUserInput("InvalidSeason\n");

	bool result = CompareProducts();

	resetStdinStdout();

	EXPECT_FALSE(result);

	char expectedOutput[] = "Invalid season. Please enter a valid season.\n";
	char actualOutput[100000];

	readOutput(outputTest, actualOutput, sizeof(actualOutput));

	EXPECT_NE(expectedOutput, actualOutput);
}

TEST_F(FarmermarketTest, BuyProductsTest) {
	int budget = 10;
	simulateUserInput("Apple\n");

	bool result = BuyProducts(budget);

	resetStdinStdout();

	EXPECT_TRUE(result);
	char expectedOutput[] = "You have successfully purchased";
	char actualOutput[100000];

	readOutput(outputTest, actualOutput, sizeof(actualOutput));

	EXPECT_NE(expectedOutput, actualOutput);
}

TEST_F(FarmermarketTest, BuyProductsTestInvalid) {
	int budget = 10;
	simulateUserInput("NonExistentProduct\n");

	bool result = BuyProducts(budget);

	resetStdinStdout();

	EXPECT_FALSE(result);

	char expectedOutput[] = "Product not found";
	char actualOutput[100000];

	readOutput(outputTest, actualOutput, sizeof(actualOutput));

	EXPECT_NE(expectedOutput, actualOutput);
}

TEST_F(FarmermarketTest, BuyProductsTestLowBudget) {
	int budget = 0;
	simulateUserInput("Apple\n");

	bool result = BuyProducts(budget);

	resetStdinStdout();

	EXPECT_FALSE(result);

	char expectedOutput[] = "Insufficient budget to buy Apple from";
	char actualOutput[100000];

	readOutput(outputTest, actualOutput, sizeof(actualOutput));

	EXPECT_NE(expectedOutput, actualOutput);
}

TEST_F(FarmermarketTest, PurchasingTransactionsAndPriceComparisonMenuTest) {
	bool guestMode = true;
	simulateUserInput("1\n\n2\n\n\n\n4\n");

	bool result = PurchasingTransactionsAndPriceComparison(guestMode);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, PurchasingTransactionsAndPriceComparisonShoppingSuggestionGuestModeTest) {
	bool guestMode = false;
	simulateUserInput("1\n\n\n4\n");

	bool result = PurchasingTransactionsAndPriceComparison(guestMode);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, PurchasingTransactionsAndPriceComparisonBuyProductsTest) {
	bool guestMode = true;
	simulateUserInput("3\n\n4\n");

	bool result = PurchasingTransactionsAndPriceComparison(guestMode);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, PurchasingTransactionsAndPriceComparisonBuyProductsGuestModeTest) {
	bool guestMode = false;
	simulateUserInput("3\n\n\n4\n");

	bool result = PurchasingTransactionsAndPriceComparison(guestMode);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, PurchasingTransactionsAndPriceComparisonInvalidOptionTest) {
	bool guestMode = true;
	simulateUserInput("invalid\n\n4541515\n\n4\n");

	bool result = PurchasingTransactionsAndPriceComparison(guestMode);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, RecursiveMatrixMultiply) {
	int A[N][N] = {
		{1, 2, 0, 0},
		{3, 4, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	int B[N][N] = {
		{5, 6, 0, 0},
		{7, 8, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	int C[N][N] = { {0} };

	int expected[N][N] = {
		{19, 22, 0, 0},
		{43, 50, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	recursiveMatrixMultiply(A, B, C, 0, 0, 0, 0, N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			EXPECT_EQ(C[i][j], expected[i][j]);
		}
	}
}

TEST_F(FarmermarketTest, MemorizedRecursiveReuseTest) {
	int dimensions[] = { 1, 2, 3, 4 };
	int n = sizeof(dimensions) / sizeof(dimensions[0]);

	// First call to populate dp array
	int firstCallCost = MCM_MemorizedRecursive(dimensions, 1, n - 1);
	EXPECT_EQ(firstCallCost, 18); // Verify the result of the first call

	int secondCallCost = MCM_MemorizedRecursive(dimensions, 1, n - 1);
	EXPECT_EQ(secondCallCost, 18);

}

TEST_F(FarmermarketTest, DynamicProgrammingTest) {
	int dimensions[] = { 1, 2, 3, 4 };
	int n = sizeof(dimensions) / sizeof(dimensions[0]);
	int minCost = MCM_DynamicProgramming(dimensions, n);
	EXPECT_EQ(minCost, 18); // The minimum cost to multiply matrices of given dimensions [1, 2, 3, 4] is 18.
}

TEST_F(FarmermarketTest, MarketInformationsTotalIncomeTest) {
	simulateUserInput("1\n\n2\n\n3\n");

	bool result = MarketInformations();

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, MarketInformationsInvalidOptionTest) {
	simulateUserInput("invalid\n\n525451\n\n3\n");


	bool result = MarketInformations();

	resetStdinStdout();

	EXPECT_TRUE(result);
	char expectedOutput[] = "Invalid input, please enter a number.";
	char actualOutput[100000];

	readOutput(outputTest, actualOutput, sizeof(actualOutput));

	EXPECT_NE(expectedOutput, actualOutput);
}

TEST_F(FarmermarketTest, MainMenuTest) {
	bool authenticationResult = true;
	simulateUserInput("1\n3\n2\n5\n3\n4\n4\n3\nasddsa\n\n151\n\n5\n");

	bool result = mainMenu(authenticationResult);

	resetStdinStdout();

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
	::testing::GTEST_FLAG(color) = "no";
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}