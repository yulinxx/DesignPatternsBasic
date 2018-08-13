#include <iostream>
using namespace std;

// ��������ģʽ Factory Method Pattern
class SingleCore
{
public:
	virtual void Show() = 0;
};

//����A  
class SingleCoreA : public SingleCore
{
public:
	void Show() { cout << "SingleCore A" << endl; }
};

//����B  
class SingleCoreB : public SingleCore
{
public:
	void Show() { cout << "SingleCore B" << endl; }
};

class Factory
{
public:
	virtual SingleCore* CreateSingleCore() = 0;
};

//����A�˵Ĺ���  
class FactoryA : public Factory
{
public:
	SingleCoreA* CreateSingleCore() { return new SingleCoreA; }
};

//����B�˵Ĺ���  
class FactoryB : public Factory
{
public:
	SingleCoreB* CreateSingleCore() { return new SingleCoreB; }
};