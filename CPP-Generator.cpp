// CPP-Generator.cpp : Defines the entry point for the application.
//

#include "CPP-Generator.h"
#include <coroutine>
#include <iostream>
#include <optional>

using namespace std;

class Generator {
public:

	// Define the promise type struct
	struct promise_type {
		// Value returned to caller. yieled by co_yield
		int current_value;

		Generator get_return_object() {
			return Generator{ coroutine_handle<promise_type>::from_promise(*this) };
		
		}

		




	};

	using handle_type = coroutine_handle<promise_type>;

	explicit Generator(handle_type h) : handle(h) {}

private:
	handle_type handle;


};
