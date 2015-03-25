#include <iostream>

class MyBaseClass {
public:
	MyBaseClass() {
		std::cout << "MyBaseClass constructor\n";
	}
	virtual ~MyBaseClass() {
		std::cout << "MyBaseClass destructor\n";
	}
};

class MyDerivedClass : public MyBaseClass {
public:
	MyDerivedClass() {
		std::cout << "MyDerivedClass constructor\n";
	}
	~MyDerivedClass() {
		std::cout << "MyDerivedClass destructor\n";
	}
};

#include <exception>
class MyExceptingDerivedClass : public MyBaseClass {
public:
	MyExceptingDerivedClass() {
		std::cout << "MyExceptionDerviedClass constructor - about to except!\n";
		throw std::exception();
	}
	~MyExceptingDerivedClass() {
		std::cout << "MyExceptingDerivedClass destructor\n";
	}
};

int main() {
	{
		MyBaseClass base;
	}
	{
		MyDerivedClass derived;
	}
	{
		try{
			MyExceptingDerivedClass* excepting = new MyExceptingDerivedClass();
			// What is the value of this line if the exception is thrown?
			// It could be NULL in some sense.
		} catch(std::exception &e) {
			std::cout << "Caught an exception creating my derived class on the heap!\n";
		}
	}

	// Of course if that were the case, what does that mean for objects on the stack?

	{
		try{
			// e.g. like here.
			MyExceptingDerivedClass excepting;
			// what is the value of excepting at this (pseudo-)line?
		} catch(std::exception &e) {
			std::cout << "Caught an exception creating my derived class on the stack\n";
		}
		// Wow. That's really cool. There never 'is' a malformed object by
		// virtue of the interaction between scoping and exceptions.
		// By the time the program begins execution within the catch block,
		// we've exitted the scope of the try block, where any symbols defined
		// for that scope alone no longer exist.
		// line 57 is never fully evaluated, and it's impossible for anything
		// after to be executed.
		// Awesome.
	}

	{
		// program death!
		MyExceptingDerivedClass excepting;
	}
}

