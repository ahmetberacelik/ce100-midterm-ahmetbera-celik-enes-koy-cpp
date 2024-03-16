#include "gtest/gtest.h"
#include "../../farmermarket/header/farmermarket.h"
class FarmermarketTest : public ::testing::Test {
protected:
	ProductSeason item1 = { 20, "Apple", "Fall" };
	ProductSeason item2 = { 10, "Banana", "Summer" };
	ProductSeason item3 = { 15, "Cherry", "Summer" };
	ProductSeason item4 = { 5, "Date", "Winter" };
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

	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, UserAuthenticationRegisterTest) {
	fputs("2\nNew User\n123456\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();

	EXPECT_TRUE(authResult);
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
	fputs("invalid\n\n4\n", testIn);
	rewind(testIn);

	bool authResult = userAuthentication(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
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
	fputs("Ahmet", testIn);
	rewind(testIn);

	bool authResult = browseVendor(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, VendorNotFoundTest) {
	fputs("NonExistingVendor", testIn);
	rewind(testIn);

	bool authResult = browseVendor(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, ProductSearchTest) {
	fputs("Banana", testIn);
	rewind(testIn);

	bool authResult = searchProduct(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ProductNotFoundTest) {
	fputs("NonExistingProduct", testIn);
	rewind(testIn);

	bool authResult = searchProduct(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_FALSE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuValidOptionTest1) {
	fputs("1\nAhmet\n\n3\n", testIn);
	rewind(testIn);

	bool authResult = listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuValidOptionTest2) {
	fputs("2\nBanana\n\n3\n", testIn);
	rewind(testIn);

	bool authResult = listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuInvalidOptionTest) {
	fputs("invalid\n\n3\n", testIn);
	rewind(testIn);

	bool authResult = listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
	EXPECT_TRUE(authResult);
}

TEST_F(FarmermarketTest, ListingInfosMenuInvalidOptionTestWithNumber) {
	fputs("5\n\n3\n", testIn);
	rewind(testIn);

	bool authResult = listingOfInfos(testIn, testOut);

	rewind(testOut);

	ReadTestOutput();
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
	int productsFound = loadProductSeasonsAndPrint(testIn, testOut, testLoadFilename, selectedSeason);

	EXPECT_EQ(productsFound, 3);
	remove(testLoadFilename);
}

TEST_F(FarmermarketTest, SeasonalProduceGuideTest) {
	fputs("invalid\n\n1\n\n2\n\n3\n\n4\n\n5\n", testIn);
	rewind(testIn);

	bool result = seasonalProduceGuide(testIn, testOut);
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

TEST_F(FarmermarketTest, CompareAndPrintLCSTest) {
	char season1[] = "Summer";
	char season2[] = "Summer";
	char name1[] = "Watermelon";
	char name2[] = "Melon";
	int price = 50;

	bool result = compareAndPrintLCS(season1, season2, name1, name2, price, testOut);

	ReadTestOutput();

	const char* expectedOutput = "|- Name 1: Watermelon, Name 2: Melon, Price: 50\n";
	EXPECT_TRUE(result);
	EXPECT_STREQ(testOutputBuffer, expectedOutput);

	strcpy(season1, "Summer");
	strcpy(season2, "Winter");

	result = compareAndPrintLCS(season1, season2, name1, name2, price, testOut);

	ReadTestOutput();

	EXPECT_TRUE(result);
}

TEST_F(FarmermarketTest, MaxFunctionTest) {
	EXPECT_EQ(10, max(5, 10)); // Test where second parameter is greater
	EXPECT_EQ(10, max(10, 5)); // Test where first parameter is greater
	EXPECT_EQ(5, max(5, 5));   // Test where both parameters are equal
}

/*TEST_F(FarmermarketTest, KnapsackFunctionTest) {
	const int W = 50; // Total weight capacity of the knapsack
	int wt[] = { 10, 20, 30 }; // Weights of the items
	int val[] = { 60, 100, 120 }; // Values of the items
	const int n = sizeof(val) / sizeof(val[0]); // Number of items
	int selectedItems[n]; // To store the selected item indices
	memset(selectedItems, 0, sizeof(selectedItems)); // Initialize with zeros

	// Maximum value expected to be carried is 220 (items 2 and 3)
	int maxValue = knapsack(W, wt, val, n, selectedItems);
	EXPECT_EQ(maxValue, 220);

	// Check if the selected items array has the correct items
	EXPECT_EQ(selectedItems[0], 0); // Item 1 (weight 10) is not selected
	EXPECT_EQ(selectedItems[1], 1); // Item 2 (weight 20) is selected
	EXPECT_EQ(selectedItems[2], 1); // Item 3 (weight 30) is selected
}*/

TEST_F(FarmermarketTest, SuggestPurchasesTest) {
	int budget = 100;
	bool result = suggestPurchases(testOut, budget);
	EXPECT_TRUE(result);

	budget = 0;
	result = suggestPurchases(testOut, budget);
	EXPECT_FALSE(result);
}

TEST_F(FarmermarketTest, CompareProductsTest) {
    fputs("Summer\n", testIn);
    rewind(testIn);

    bool result = CompareProducts(testIn, testOut);

    EXPECT_TRUE(result);

    ReadTestOutput();
    const char* expectedOutput = "|Products at the same price as Summer season products:\n";
    EXPECT_NE(nullptr, strstr(testOutputBuffer, expectedOutput));
}

TEST_F(FarmermarketTest, CompareProductsTestInvalid) {
	fputs("InvalidSeason\n", testIn);
	rewind(testIn);
	bool result = CompareProducts(testIn, testOut);

	EXPECT_FALSE(result);
	ReadTestOutput();
	const char* expectedError = "Invalid season. Please enter a valid season.\n";
	EXPECT_NE(nullptr, strstr(testOutputBuffer, expectedError));
}

/*TEST_F(FarmermarketTest, BuyProductsTest) {
	fputs("Apple\n", testIn);
	rewind(testIn);

	bool result = BuyProducts(testIn, testOut);
	rewind(testOut);
	ReadTestOutput();
	EXPECT_TRUE(result);
	char expectedOutput[] = "cdcd";
	EXPECT_STREQ(testOutputBuffer, expectedOutput);
}*/

TEST_F(FarmermarketTest, BuyProductsTestInvalid) {
	fputs("NonExistentProduct\n", testIn);
	rewind(testIn);

	bool result = BuyProducts(testIn, testOut);

	EXPECT_FALSE(result);
	ReadTestOutput();
	const char* expectedNotFoundMessage = "Product not found";
	EXPECT_NE(nullptr, strstr(testOutputBuffer, expectedNotFoundMessage));
}

/*TEST_F(FarmermarketTest, BuyProductsTestLowBudget) {
	fputs("Apple\n", testIn);
	rewind(testIn);

	bool result = BuyProducts(testIn, testOut);

	EXPECT_FALSE(result);
	ReadTestOutput();
	const char* expectedBudgetMessage = "Insufficient budget to buy Apple from";
	EXPECT_NE(nullptr, strstr(testOutputBuffer, expectedBudgetMessage));
}*/


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