#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <format>


#include "../CPP-Generator.h"

using std::cout;
using std::endl;
using std::format;


//*
// @brief Basic testing fo the count_to_test_function
// */
TEST(GeneratorTesting, CountsUpToGivenNumber) {
	cout << "Generator TestFunction" << endl;
	
	Generator gen = count_to_test_func(5);
	size_t upperLimit = 0;
	while (gen.next()) {
		EXPECT_DOUBLE_EQ(upperLimit, gen.value());
		upperLimit++;
	}
}

//*
// @ brief Basic Algorithm used in part with testGeneratorFunctionWithPassedAlgorithm 
// 
// */
double TestAlgorithm(double valA, double valB) {
	return valA + valB;
}


//*
// @brief Function to test the reciving and leverage of a passed algorithm in the generator class
// 
// @param testFunction - The function to be called recursivly 
// @retrun Generator function 
// */
Generator testGeneratorFunctionWithPassedAlgorithm(double (*testFunction)(double, double), double setValue, vector<double> testValues) {
	
	for (size_t i = 0; i < testValues.size(); i++) {
		double x = testFunction(testValues[i], setValue);
		co_yield x;
	}
}


//*
// @Brief Test if value Produced by Generator is of expected value 
// 
// @param gen The generator object
// @param expectedValues Vector<double> of the expected results from the generator
// */
void AssertGeneratorProducesValue(Generator& gen, vector<double>& expectedValues) {
	size_t i = 0;

	while (gen.next()) {
		ASSERT_LT(i, expectedValues.size()) << "Index out of bounds";
		
		string scopeTraceMessage = format("Expected Value : {} -> Actual Value : {}", expectedValues[i], gen.value());
		SCOPED_TRACE(scopeTraceMessage);
		EXPECT_DOUBLE_EQ(gen.value(), expectedValues[i]);
		i++;
	}
	// Check all values have been tested
	ASSERT_EQ(i, expectedValues.size());

}

//*
// @brief Testing the passing of an algorithm to a generator function
// 
// */
TEST(GeneratorTesting, AppliesAlgorithmToEachValue) {
	
	double setValue = 10;
	vector<double> testValues = { 1.1,2,3,4,5,6.6 };

	vector<double> expectedResult = { 11.1,12,13,14,15,16.6 };
	// Passed function converted to pointer
	Generator gen = testGeneratorFunctionWithPassedAlgorithm(TestAlgorithm, setValue, testValues);
	AssertGeneratorProducesValue(gen, expectedResult);

}