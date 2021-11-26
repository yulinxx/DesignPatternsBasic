#include <string>
#include <iostream>
using namespace std;

class Mediator;

// 抽象人
class Person
{
protected:
	Mediator *m_pMediator; //中介

public:
	virtual void SetMediator(Mediator *pMediator) {} // 设置中介
	virtual void SendMessage(string message) {}    // 向中介发送信息
	virtual void GetMessage(string message) {}     // 从中介获取信息
};


// 抽象中介机构
class Mediator
{
public:
	virtual void Send(string message, Person *person) {}
	virtual void SetRenter(Person *A) {}  // 设置其中一方
	virtual void SetLandlord(Person *B) {}
};

// 租房者
class Renter : public Person
{
public:
	void SetMediator(Mediator *pMediator) { m_pMediator = pMediator; }

	void SendMessage(string message) { m_pMediator->Send(message, this); }
	void GetMessage(string message) { cout << "租房者收到信息" << message; }
};

// 房东
class Landlord : public Person
{
public:
	void SetMediator(Mediator *pMediator) { m_pMediator = pMediator; }
	void SendMessage(string message) { m_pMediator->Send(message, this); }
	void GetMessage(string message) { cout << "房东收到信息：" << message; }
};


// 房屋中介
class HouseMediator : public Mediator
{
private:
	Person *m_pRenter;	// 租房者
	Person *m_pLandlord;	// 房东

public:
	HouseMediator() : m_pRenter(0), m_pLandlord(0) {}
	void SetRenter(Person *A) { m_pRenter = A; }
	void SetLandlord(Person *B) { m_pLandlord = B; }

	void Send(string message, Person *person)
	{
		if (person == m_pRenter)	// 租房者给房东发信息
			m_pLandlord->GetMessage(message); // 房东收到信息
		else
			m_pRenter->GetMessage(message);
	}
};


// 客户使用方式如下：

int main()
{
	Mediator *pMediator = new HouseMediator();	// 房屋中介
	Person *pPerson1 = new Renter();    // 租房者
	Person *pPerson2 = new Landlord();  // 房东

	pMediator->SetRenter(pPerson1);
	pMediator->SetLandlord(pPerson2);

	pPerson1->SetMediator(pMediator);
	pPerson2->SetMediator(pMediator);

	pPerson1->SendMessage("我想在南京路附近租套房子，价格800元一个月\n");
	pPerson2->SendMessage("出租房子：南京路100号，70平米，1000元一个月\n");

	delete pPerson1; delete pPerson2; delete pMediator;

	return 0;
}