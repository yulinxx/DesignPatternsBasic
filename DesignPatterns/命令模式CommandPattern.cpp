#include <iostream>  
#include <string>
#include <vector>
using namespace std;

/*
����ȥ�����Է���������ͨ������Ա����ˣ�������˭������Щ�˺�����ʲôʱ����ɵ���Щ�ˣ���ʵ���Ƕ���֪����
����֮�������ǡ��˵������ߡ�����ʦ�ǡ��˵�ʵ���ߡ���2��֮��������ϵģ�
���Ƕ���Щ�˵�����һЩ������硰�������������ȣ�����Ҳ��֪����˭������
��ʵ����� Command ģʽ��
��һ�������װΪһ�����󣬴Ӷ�ʹ����ò�ͬ������Կͻ����в�������
�������Ŷӻ��¼������־���Լ�֧�ֿɳ����Ĳ�����[GOF �����ģʽ��]
*/

// Barbecue �տ����⿾��Ұ�Ϳ�����
// Mutton ���������������������

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

/*����ʦ���ֻ࣬���𿾴�����*/
class Barbecuer
{
public:
	void BakeMutton() { cout << "Bake mutton" << endl; }
	void BakeChickenWing() { cout << "Bake ChickenWing" << endl; }
};

/*���������ࣺ��ִ�о�������Ľӿ�*/
class Command
{
public:
	Command() {}
	Command(Barbecuer *receiver) :m_pReceiver(receiver) {}
	virtual void ExecuteCommand() = 0; //ִ������
protected:
	Barbecuer *m_pReceiver;
};

/*����������:�����⴮����*/
class BakeMuttonCommand :public Command
{
public:
	BakeMuttonCommand(Barbecuer *pReceiver) { m_pReceiver = pReceiver; }
	void ExecuteCommand() { m_pReceiver->BakeMutton(); }
};

/*����������:�����ᴮ����*/
class BakeChickenWingCommand :public Command
{
public:
	BakeChickenWingCommand(Barbecuer *receiver) { m_pReceiver = receiver; }
	void ExecuteCommand()
	{
		m_pReceiver->BakeChickenWing();
	}
};

/*����Ա��*/
class Waiter
{
public:
	void SetOrder(Command *command)
	{
		p_commandList.push_back(command);
		cout << "���Ӳ˵�����" << endl;
	}

	void Notify()
	{
		vector<Command*>::iterator i;
		for (i = p_commandList.begin(); i != p_commandList.end(); ++i)
			(*i)->ExecuteCommand();
	}

private:
	vector<Command *>p_commandList; //�����൱��һ������������
};



int main(int argc, char *argv[])
{
	Barbecuer *pCook = new Barbecuer();	// ����ʦ��

	Command *pMutton = new BakeMuttonCommand(pCook); // ����
	Command *pChickenWing = new BakeChickenWingCommand(pCook); // ����
	

	//�������������͵�����Ա���������
	Waiter *pWaiter = new Waiter(); // ����Ա
	pWaiter->SetOrder(pMutton);
	pWaiter->SetOrder(pChickenWing);

	//����Ա֪ͨ����ʦ�����嶩��
	pWaiter->Notify();

	SAFE_DELETE(pCook);
	SAFE_DELETE(pMutton);
	SAFE_DELETE(pChickenWing);
	SAFE_DELETE(pWaiter);

	return 0;
}