#include <iostream>

using namespace std;

// ����ӿ�
class Command
{
public:
	virtual void execute() = 0;
};

// ������
class Invoker
{
public:
	Invoker(Command* command)
	{
		this->command = command;
	}
	void action()
	{
		command->execute();
	}
private:
	Command* command;
};

// ������
class Receiver
{
public:
	Receiver()
	{
	}
	void action()
	{
		cout << "Action has been taken." << endl;
	}
};

// ���������
class ConcreteCommand : public Command
{
public:
	ConcreteCommand(Receiver* receiver)
	{
		this->receiver = receiver;
	}
	void execute()
	{
		receiver->action();
	}
private:
	Receiver* receiver;
};

// �ͻ�
int main(int argc, char* argv[])
{
	// �ͻ�Ҫ��֪�����˭��
	Receiver* receiver = new Receiver();

	// �ͻ�Ҫ��֪������ʲô��
	Command* command = new ConcreteCommand(receiver);

	// �ͻ��������������
	Invoker* invoker = new Invoker(command);

	// ������ͨ��Command�ӿڰ������������ִ��
	invoker->action();

	return 0;
}