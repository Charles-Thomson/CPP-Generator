// CPP-Generator.cpp : Defines the entry point for the application.
//

#include "CPP-Generator.h"
#include <coroutine>
#include <iostream>
#include <optional>
#include <tuple>
#include <format>
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

Generator::Generator(Generator&& other) noexcept : handle(other.handle) {
	other.handle = nullptr;
}

Generator& Generator::operator=(Generator&& other) noexcept {
	if (this != &other) {
		if (handle) handle.destroy();
		handle = other.handle;
		other.handle = nullptr;
	}
	return *this;
}


bool Generator::next() {
	if (!handle || handle.done())
		return false;

	handle.resume();
	return !handle.done();

}

double Generator::value() const {
	if (!handle)
		throw std::runtime_error("Attempt to get value from null coroutine handle.");
	return handle.promise().current_value;
}


Generator count_to_test_func(double n) {
	for (int i = 0; i <= n; i++) {
		co_yield i;
	}
}


 