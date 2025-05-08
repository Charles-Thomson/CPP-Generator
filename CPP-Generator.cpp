// CPP-Generator.cpp : Defines the entry point for the application.
//

#include "CPP-Generator.h"
#include <coroutine>
#include <iostream>
#include <optional>
#include <tuple>
#include <format>;
#include <functional>

using std::cout;
using std::endl;
using std::tuple;
using std::tie;
using std::format;
using std::function;
using namespace std;

Generator::Generator(handle_type h) : handle(h) {}
Generator::~Generator() { if (handle) handle.destroy(); }


bool Generator::next() {
	if (!handle.done()) handle.resume();
	return !handle.done();

}

double Generator::value() const {
	return handle.promise().current_value;
}



Generator count_to_test_func(double n) {
	for (int i = 0; i <= n; i++) {
		co_yield i;
	}

}


 