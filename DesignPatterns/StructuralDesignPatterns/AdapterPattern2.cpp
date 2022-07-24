
// 适配器模式(Adapter Pattern)

#include <iostream>
using namespace std;

// "ITarget"
class Target
{
public:
	virtual void Request() {};
};

// "Adaptee"
class Adaptee
{
public:
	void SpecificRequest()
	{
		cout << "Called SpecificRequest()" << endl;
	}
};

// "Adapter"
class Adapter : public Adaptee, public Target
{
public:
	// Implements ITarget interface
	void Request()
	{
		// Possibly do some data manipulation
		// and then call SpecificRequest  
		this->SpecificRequest();
	}
};


///////////////////////////////////////////////////////
int main()
{
	std::cout<<"结构型模式 之 适配器模式 2 \n\n";

	// Create adapter and place a request
	Target *t = new Adapter();
	t->Request();

	return 0;
}