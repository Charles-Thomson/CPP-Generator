// CPP-Generator.cpp : Defines the entry point for the application.
//

#include "CPP-Generator.h"
#include <coroutine>
#include <iostream>
#include <optional>

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

Generator count_to(int n) {
	for (int i = 1; i <= n; i++) {
		co_yield i;
	}

}
 