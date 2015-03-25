#include <memory>
#include <iostream>

class MyObject {
public:
	MyObject() { std::cout << "MyObject constructor called!\n"; }
	~MyObject() { std::cout << "MyObject destructor called!\n"; }
};

int main(){
	MyObject* raw=new MyObject;
	std::shared_ptr<MyObject> shared(raw);
	std::cout << "About to enter inner scope.\n";
	// Don't do this!
	//{
	//	std::shared_ptr<MyObject> shared2(raw); // don't
	//}
	// delete raw would get called here, and then 
	// again at the end of this scope. Death.
	{
		// This allocation, however, is ok.
		std::shared_ptr<MyObject> shared2(shared);
		std::cout << "Created shared2.\n";
		shared.reset();
	}
	std::cout << "Inner scope concluded.\n";
}