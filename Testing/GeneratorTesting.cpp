#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include "../CPP-Generator.cpp"

using std::cout;
using std::endl;



TEST(GeneratorTesting, PlaceHolderTest) {
	cout << "Generator TestFunction" << endl;
	
	auto gen = count_to(5);
	while (gen.next()) {
		cout << "Generator item : " << gen.value() << endl;
	
	}




	// Set to fail to see outputs
	ASSERT_EQ(1, 2);


}