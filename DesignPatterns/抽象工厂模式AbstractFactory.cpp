// ���󹤳�ģʽ Abstract Factory

#include <iostream>
using namespace std;

//����  
class SingleCore
{
public:
	virtual void Show() = 0;
};

class SingleCoreA : public SingleCore
{
public:
	void Show() { cout << "Single Core A" << endl; }
};

class SingleCoreB :public SingleCore
{
public:
	void Show() { cout << "Single Core B" << endl; }
};

//���  
class MultiCore
{
public:
	virtual void Show() = 0;
};

class MultiCoreA : public MultiCore
{
public:
	void Show() { cout << "Multi Core A" << endl; }
};

class MultiCoreB : public MultiCore
{
public:
	void Show() { cout << "Multi Core B" << endl; }
};

//����  
class CoreFactory
{
public:
	virtual SingleCore* CreateSingleCore() = 0;
	virtual MultiCore* CreateMultiCore() = 0;
};

//����A��ר����������A�ͺŵĴ�����  
class FactoryA :public CoreFactory
{
public:
	SingleCore* CreateSingleCore() { return new SingleCoreA(); }
	MultiCore* CreateMultiCore() { return new MultiCoreA(); }
};

//����B��ר����������B�ͺŵĴ�����  
class FactoryB : public CoreFactory
{
public:
	SingleCore* CreateSingleCore() { return new SingleCoreB(); }
	MultiCore* CreateMultiCore() { return new MultiCoreB(); }
};