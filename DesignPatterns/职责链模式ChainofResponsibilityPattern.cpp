// ְ����ģʽChainofResponsibilityPattern.cpp

#include <string>
#include <iostream>
using namespace std;

//���������
class Manager
{
protected:
	Manager *m_manager;
	string m_name;
public:
	Manager(Manager *manager, string name) :m_manager(manager), m_name(name) {}
	virtual void DealWithRequest(string name, int num) {}
};

//����
class CommonManager : public Manager
{
public:
	CommonManager(Manager *manager, string name) :Manager(manager, name) {}
	void DealWithRequest(string name, int num)
	{
		if (num < 500) //����ְȨ֮��
		{
			cout << "����" << m_name << "��׼" << name << "��н" << num << "Ԫ" << endl << endl;
		}
		else
		{
			cout << "����" << m_name << "�޷����������ܼദ��" << endl;
			m_manager->DealWithRequest(name, num);
		}
	}
};

//�ܼ�
class Majordomo : public Manager
{
public:
	Majordomo(Manager *manager, string name) :Manager(manager, name) {}
	void DealWithRequest(string name, int num)
	{
		if (num < 1000) //�ܼ�ְȨ֮��
		{
			cout << "�ܼ�" << m_name << "��׼" << name << "��н" << num << "Ԫ" << endl << endl;
		}
		else
		{
			cout << "�ܼ�" << m_name << "�޷����������ܾ�����" << endl;
			m_manager->DealWithRequest(name, num);
		}
	}
};

//�ܾ���
class GeneralManager : public Manager
{
public:
	GeneralManager(Manager *manager, string name) :Manager(manager, name) {}
	void DealWithRequest(string name, int num)  //�ܾ�����Դ�����������
	{
		cout << "�ܾ���" << m_name << "��׼" << name << "��н" << num << "Ԫ" << endl << endl;
	}
};

// �ͻ����÷�ʽΪ��

int main()
{
	Manager *general = new GeneralManager(NULL, "A"); //�����ϼ����ܾ���û���ϼ�
	Manager *majordomo = new Majordomo(general, "B"); //�����ϼ�
	Manager *common = new CommonManager(majordomo, "C"); //�����ϼ�

	common->DealWithRequest("D", 300);   //Ա��DҪ���н
	common->DealWithRequest("E", 600);
	common->DealWithRequest("F", 1000);
	delete common; delete majordomo; delete general;

	return 0;
}