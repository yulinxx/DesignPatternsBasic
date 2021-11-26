#include <iostream>

using namespace std;

// 命令接口
class Command
{
public:
	virtual void execute() = 0;
};

// 调用者
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

// 接收者
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

// 具体的命令
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

// 客户
int main(int argc, char* argv[])
{
	// 客户要告知命令发给谁？
	Receiver* receiver = new Receiver();

	// 客户要告知命令是什么？
	Command* command = new ConcreteCommand(receiver);

	// 客户把命令给调用者
	Invoker* invoker = new Invoker(command);

	// 调用者通过Command接口把命令交给接收者执行
	invoker->action();

	return 0;
}