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
	Command(Barbecuer *receiver) :p_receiver(receiver) {}
	virtual void ExecuteCommand() = 0; //ִ������
protected:
	Barbecuer *p_receiver;
};

/*����������:�����⴮����*/
class BakeMuttonCommand :public Command
{
public:
	BakeMuttonCommand(Barbecuer *receiver) { p_receiver = receiver; }
	void ExecuteCommand() { p_receiver->BakeMutton(); }
};

/*����������:�����ᴮ����*/
class BakeChickenWingCommand :public Command
{
public:
	BakeChickenWingCommand(Barbecuer *receiver) { p_receiver = receiver; }
	void ExecuteCommand()
	{
		p_receiver->BakeChickenWing();
	}
};

/*����Ա��*/
class Waiter
{
public:
	void SetOrder(Command *command)
	{
		p_commandList.push_back(command);
		cout << "���ӿ�������" << endl;
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
	//���ɿ���ʦ��������Ա����������
	Barbecuer *p_cook = new Barbecuer();	// ����ʦ��
	Waiter *p_waiter = new Waiter(); // ����Ա

	Command *p_mutton = new BakeMuttonCommand(p_cook); // ����
	Command *p_chickenwing = new BakeChickenWingCommand(p_cook); // ����
	

	//�������������͵��������
	p_waiter->SetOrder(p_mutton);
	p_waiter->SetOrder(p_chickenwing);

	//����Ա֪ͨ����ʦ�����嶩��
	p_waiter->Notify();

	SAFE_DELETE(p_cook);
	SAFE_DELETE(p_mutton);
	SAFE_DELETE(p_chickenwing);
	SAFE_DELETE(p_waiter);

	return 0;
}