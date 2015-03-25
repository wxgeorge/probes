#include <iostream>

class A {
public:
	A() { std::cout << "A::A() called!" << "\n"; this->do_me(); }
	void do_me() { std::cout << "A::do_me()!" << "\n"; }
};

class B : public A {
public:
	B() { std::cout << "B::B() called!" << "\n"; this->do_me(); }
	void do_me() { std::cout << "B::do_me()!" << "\n"; }
};

int main() {
	// what will I print?
	B b;
	
}
