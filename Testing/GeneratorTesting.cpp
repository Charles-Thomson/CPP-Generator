#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include "../CPP-Generator.cpp"

using std::cout;
using std::endl;



TEST(GeneratorTesting, PlaceHolderTest) {
	cout << "Generator TestFunction" << endl;
	
	Generator gen = count_to(5);
	while (gen.next()) {
		cout << "Generator item : " << gen.value() << endl;
	
	}
	// Set to fail to see outputs
	ASSERT_EQ(1, 2);


}


//*
// Use Case
// Need to be able pass in the alg and layers tuple
// The values are then returned from the generator function 
// - Possible to define a generator function for each ?
// - Cleaner approach: Single function that takes algorithm (lambda?) and process acordingly
// */
TEST(GeneratorTesting, GeneratorAlgorithmPassing) {

	
	tuple<double, double> testLayers = {2, 10};

	Generator gen = test_alg(testLayers, 2);



	while (gen.next()) {
		cout << "Generator item : " << gen.value() << endl;

	}


	// Fail point for prinitng
	ASSERT_EQ(1, 2);

}