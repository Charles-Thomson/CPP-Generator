﻿// CPP-Generator.h : Include file for standard system include files,
// or project specific include files.

#ifndef CPP_GENERATOR_H
#define CPP_GENERATOR_H

#include <coroutine>
#include <iostream>
#include <optional>

using namespace std;

class Generator {
public:

	

	// Define the promise type struct
	struct promise_type {
		// Value returned to caller. yieled by co_yield
		double current_value;
		


		//Returns the object a user is to interact with
		Generator get_return_object() {
			return Generator{ coroutine_handle<promise_type>::from_promise(*this) };

		}

		// Stops the coroutine immediatly after creation. Pause before entry to body* 
		suspend_always initial_suspend() { return {}; }

		// Controles behaviour after coroutine finishes (after final yeild or return)
		suspend_always final_suspend() noexcept { return {}; }


		// Called when co_yield is used
		// Sets the current value, sets the coroutine to suspend
		suspend_always yield_value(double value) {
			current_value = value;
			return{};
		}

		// Requiered even if not used

		void return_void() {}


		// Defeines the process when coroutine throws an error
		void unhandled_exception() { terminate(); }



	};

	using handle_type = coroutine_handle<promise_type>;

	Generator(std::nullptr_t) : handle(nullptr) {}

	explicit Generator(handle_type h);
	~Generator();

	// Move constructor
	Generator(Generator&& other) noexcept;

	// Move assignment operator
	Generator& operator=(Generator&& other) noexcept;

	// Delete copy constructor and copy assignment
	Generator(const Generator&) = delete;
	Generator& operator=(const Generator&) = delete;


	bool next();

	double value() const;

	

private:
	handle_type handle;
	


};

Generator count_to_test_func(double n);




#endif //!CPP_GENERATOR_H

