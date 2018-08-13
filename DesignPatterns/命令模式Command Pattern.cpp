#include <iostream>  
#include <string>
#include <vector>
using namespace std;

/*
我们去餐厅吃饭，我们是通过服务员来点菜，具体是谁来做这些菜和他们什么时候完成的这些菜，其实我们都不知道。
抽象之，我们是“菜单请求者”，厨师是“菜单实现者”，2者之间是松耦合的，
我们对这些菜的其他一些请求比如“撤销，重做”等，我们也不知道是谁在做。
其实这就是 Command 模式。
将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；
对请求排队或记录请求日志，以及支持可撤消的操作。[GOF 《设计模式》]
*/

// Barbecue 烧烤烤肉烤肉野餐烤肉宴
// Mutton 羊肉羔羊肉涮羊肉羊肉类

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

/*烤肉师傅类，只负责烤串工作*/
class Barbecuer
{
public:
	void BakeMutton() { cout << "Bake mutton" << endl; }
	void BakeChickenWing() { cout << "Bake ChickenWing" << endl; }
};

/*抽象命令类：是执行具体操作的接口*/
class Command
{
public:
	Command() {}
	Command(Barbecuer *receiver) :p_receiver(receiver) {}
	virtual void ExecuteCommand() = 0; //执行命令
protected:
	Barbecuer *p_receiver;
};

/*具体命令类:烤羊肉串命令*/
class BakeMuttonCommand :public Command
{
public:
	BakeMuttonCommand(Barbecuer *receiver) { p_receiver = receiver; }
	void ExecuteCommand() { p_receiver->BakeMutton(); }
};

/*具体命令类:烤鸡翅串命令*/
class BakeChickenWingCommand :public Command
{
public:
	BakeChickenWingCommand(Barbecuer *receiver) { p_receiver = receiver; }
	void ExecuteCommand()
	{
		p_receiver->BakeChickenWing();
	}
};

/*服务员类*/
class Waiter
{
public:
	void SetOrder(Command *command)
	{
		p_commandList.push_back(command);
		cout << "增加烤肉命令" << endl;
	}

	void Notify()
	{
		vector<Command*>::iterator i;
		for (i = p_commandList.begin(); i != p_commandList.end(); ++i)
			(*i)->ExecuteCommand();
	}

private:
	vector<Command *>p_commandList; //这里相当于一个命令对象队列
};



int main(int argc, char *argv[])
{
	//生成烤肉师傅、服务员、订单对象
	Barbecuer *p_cook = new Barbecuer();	// 烤肉师傅
	Waiter *p_waiter = new Waiter(); // 服务员

	Command *p_mutton = new BakeMuttonCommand(p_cook); // 羊肉
	Command *p_chickenwing = new BakeChickenWingCommand(p_cook); // 鸡翅
	

	//将订单对象推送到命令队列
	p_waiter->SetOrder(p_mutton);
	p_waiter->SetOrder(p_chickenwing);

	//服务员通知烤肉师傅具体订单
	p_waiter->Notify();

	SAFE_DELETE(p_cook);
	SAFE_DELETE(p_mutton);
	SAFE_DELETE(p_chickenwing);
	SAFE_DELETE(p_waiter);

	return 0;
}