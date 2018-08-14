#include <string>
#include <iostream>
using namespace std;

class Mediator;

// ������
class Person
{
protected:
	Mediator *m_pMediator; //�н�

public:
	virtual void SetMediator(Mediator *pMediator) {} // �����н�
	virtual void SendMessage(string message) {}    // ���н鷢����Ϣ
	virtual void GetMessage(string message) {}     // ���н��ȡ��Ϣ
};


// �����н����
class Mediator
{
public:
	virtual void Send(string message, Person *person) {}
	virtual void SetRenter(Person *A) {}  // ��������һ��
	virtual void SetLandlord(Person *B) {}
};

// �ⷿ��
class Renter : public Person
{
public:
	void SetMediator(Mediator *pMediator) { m_pMediator = pMediator; }

	void SendMessage(string message) { m_pMediator->Send(message, this); }
	void GetMessage(string message) { cout << "�ⷿ���յ���Ϣ" << message; }
};

// ����
class Landlord : public Person
{
public:
	void SetMediator(Mediator *pMediator) { m_pMediator = pMediator; }
	void SendMessage(string message) { m_pMediator->Send(message, this); }
	void GetMessage(string message) { cout << "�����յ���Ϣ��" << message; }
};


// �����н�
class HouseMediator : public Mediator
{
private:
	Person *m_pRenter;	// �ⷿ��
	Person *m_pLandlord;	// ����

public:
	HouseMediator() : m_pRenter(0), m_pLandlord(0) {}
	void SetRenter(Person *A) { m_pRenter = A; }
	void SetLandlord(Person *B) { m_pLandlord = B; }

	void Send(string message, Person *person)
	{
		if (person == m_pRenter)	// �ⷿ�߸���������Ϣ
			m_pLandlord->GetMessage(message); // �����յ���Ϣ
		else
			m_pRenter->GetMessage(message);
	}
};


// �ͻ�ʹ�÷�ʽ���£�

int main()
{
	Mediator *pMediator = new HouseMediator();	// �����н�
	Person *pPerson1 = new Renter();    // �ⷿ��
	Person *pPerson2 = new Landlord();  // ����

	pMediator->SetRenter(pPerson1);
	pMediator->SetLandlord(pPerson2);

	pPerson1->SetMediator(pMediator);
	pPerson2->SetMediator(pMediator);

	pPerson1->SendMessage("�������Ͼ�·�������׷��ӣ��۸�800Ԫһ����\n");
	pPerson2->SendMessage("���ⷿ�ӣ��Ͼ�·100�ţ�70ƽ�ף�1000Ԫһ����\n");

	delete pPerson1; delete pPerson2; delete pMediator;

	return 0;
}