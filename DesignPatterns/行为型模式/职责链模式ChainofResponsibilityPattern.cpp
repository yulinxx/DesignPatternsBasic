// 职责链模式ChainofResponsibilityPattern.cpp
// 职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之前的耦合关系，
// 将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。

// 职责链上的处理者负责处理请求，客户只需要将请求发送到职责链上即可，
// 无需关心请求的处理细节和请求的传递，所有职责链将请求的发送者和请求的处理者解耦了。


#include <string>
#include <iostream>
using namespace std;

//抽象管理者
class Manager
{
protected:
	Manager *m_manager;
	string m_name;
public:
	Manager(Manager *manager, string name) :m_manager(manager), m_name(name) {}
	virtual void DealWithRequest(string name, int num) {}
};

//经理
class CommonManager : public Manager
{
public:
	CommonManager(Manager *manager, string name) :Manager(manager, name) {}
	void DealWithRequest(string name, int num)
	{
		if (num < 500) //经理职权之内
		{
			cout << "经理" << m_name << "批准" << name 
				<< "加薪" << num << "元" << endl << endl;
		}
		else
		{
			cout << "经理" << m_name << "无法处理，交由总监处理" << endl;
			m_manager->DealWithRequest(name, num);
		}
	}
};

//总监
class Majordomo : public Manager
{
public:
	Majordomo(Manager *manager, string name) :Manager(manager, name) {}
	void DealWithRequest(string name, int num)
	{
		if (num < 1000) //总监职权之内
		{
			cout << "总监" << m_name << "批准" << name 
				<< "加薪" << num << "元" << endl << endl;
		}
		else
		{
			cout << "总监" << m_name << "无法处理，交由总经理处理" << endl;
			m_manager->DealWithRequest(name, num);
		}
	}
};

//总经理
class GeneralManager : public Manager
{
public:
	GeneralManager(Manager *manager, string name) :Manager(manager, name) {}
	void DealWithRequest(string name, int num)  //总经理可以处理所有请求
	{
		cout << "总经理" << m_name << "批准" << name 
			<< "加薪" << num << "元" << endl << endl;
	}
};

/////////////////////////////////////
// 客户调用方式为：
int main()
{
	Manager *general = new GeneralManager(nullptr, "A"); //设置上级，总经理没有上级
	Manager *majordomo = new Majordomo(general, "B"); //设置上级
	Manager *common = new CommonManager(majordomo, "C"); //设置上级

	common->DealWithRequest("D", 300);   //员工D要求加薪
	common->DealWithRequest("E", 600);
	common->DealWithRequest("F", 1000);
	delete common; delete majordomo; delete general;

	return 0;
}