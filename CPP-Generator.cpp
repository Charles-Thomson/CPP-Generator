// CPP-Generator.cpp : Defines the entry point for the application.
//

#include "CPP-Generator.h"
#include <coroutine>
#include <iostream>
#include <optional>
#include <tuple>
#include <format>;

using std::cout;
using std::endl;
using std::tuple;
using std::tie;
using std::format;
using namespace std;

Generator::Generator(handle_type h) : handle(h) {}
Generator::~Generator() { if (handle) handle.destroy(); }


bool Generator::next() {
	if (!handle.done()) handle.resume();
	return !handle.done();

}

int Generator::value() const {
	return handle.promise().current_value;
}

string Generator::label() const {
	return handle.promise().label;

}


Generator count_to(int n) {
	for (int i = 1; i <= n; i++) {
		co_yield i;
	}

}

Generator test_alg(tuple<double,double> layers, int n) {
	double valA;
	double valB;
	tie(valA, valB) = layers;
	
	cout << format("Layer input : {} -> Layer output : {}", valA, valB) << endl;

	for (int i = 1; i <= n; i++) {
		co_yield i;
	}

}

void Generator::set_alg(string newAlg) {
	alg = newAlg;


}

void Generator::PrintAlg() {
	cout << "Current Alg : " << alg << endl;

}
 