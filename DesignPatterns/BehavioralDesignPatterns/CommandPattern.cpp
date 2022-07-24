#include <iostream>  
#include <string>
#include <vector>
using namespace std;

/*
我们去餐厅吃饭，我们是通过服务员来点菜，具体是谁来做这些菜和他们什么时候完成的这些菜，其实我们都不知道。
抽象之，我们是“菜单请求者”，厨师是“菜单实现者”，2者之间是松耦合的，
我们对这些菜的其他一些请求比如“撤销，重做”等，我们也不知道是谁在做。
其实这就是 命令 Command 模式。
将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；
对请求排队或记录请求日志，以及支持可撤消的操作。[GOF 《设计模式》]
*/

// Barbecue 烧烤烤肉烤肉野餐烤肉宴
// Mutton 羊肉羔羊肉涮羊肉羊肉类

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }

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
	Command(Barbecuer *receiver) :m_pReceiver(receiver) {}
	virtual void ExecuteCommand() = 0; //执行命令
	
protected:
	Barbecuer *m_pReceiver;
};

/*具体命令类:烤羊肉串命令*/
class BakeMuttonCommand :public Command
{
public:
	BakeMuttonCommand(Barbecuer *pReceiver) { m_pReceiver = pReceiver; }
	void ExecuteCommand() { m_pReceiver->BakeMutton(); }
};

/*具体命令类:烤鸡翅串命令*/
class BakeChickenWingCommand :public Command
{
public:
	BakeChickenWingCommand(Barbecuer *receiver) { m_pReceiver = receiver; }
	void ExecuteCommand()
	{
		m_pReceiver->BakeChickenWing();
	}
};

/*服务员类*/
class Waiter
{
public:
	void SetOrder(Command *command)
	{
		p_commandList.push_back(command);
		cout << "增加菜单命令" << endl;
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


///////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	std::cout<<"行为型模式 之 命令模式\n\n";

	Barbecuer *pCook = new Barbecuer();	// 烤肉师傅

	Command *pMutton = new BakeMuttonCommand(pCook); // 羊肉
	Command *pChickenWing = new BakeChickenWingCommand(pCook); // 鸡翅
	

	//将订单对象推送到服务员的命令队列
	Waiter *pWaiter = new Waiter(); // 服务员
	pWaiter->SetOrder(pMutton);
	pWaiter->SetOrder(pChickenWing);

	//服务员通知烤肉师傅具体订单
	pWaiter->Notify();

	SAFE_DELETE(pCook);
	SAFE_DELETE(pMutton);
	SAFE_DELETE(pChickenWing);
	SAFE_DELETE(pWaiter);

	return 0;
}