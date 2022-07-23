/*
 * @Author: xx xx@ubuntu.com
 * @Date: 2022-06-26 16:37:21
 * @LastEditors: xx xx@ubuntu.com
 * @LastEditTime: 2022-07-23 22:07:33
 * @FilePath: /DesignPatternsBasic/DesignPatterns/CreationalDesignPatterns/SimpleFactoryPattern.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// 简单工厂模式
// 主要特点是需要在工厂类中做判断，从而创造相应的产品，当增加新产品时，需要修改工厂类。使用简单工厂模式，我们只需要知道具体的产品型号就可以创建一个产品。
// 缺点：工厂类集中了所有产品类的创建逻辑，如果产品量较大，会使得工厂类变的非常臃肿。

// 对于简单设计模式的结构图，我们可以很清晰的看到它的组成：
// 1) 工厂类角色：这是本模式的核心，含有一定的商业逻辑和判断逻辑。
// 2) 抽象产品角色：它一般是具体产品继承的父类或者实现的接口。
// 3) 具体产品角色：工厂类所创建的对象就是此角色的实例。
// 简单设计模式存在的目的很简单：定义一个用于创建对象的接口。

// 缺点：对修改不封闭，新增加产品您要修改工厂。违法了鼎鼎大名的开闭法则（OCP）。


#include <iostream>
using namespace std;

// 简单工厂模式 Simple Factory Pattern
enum CTYPE { COREA, COREB };

class SingleCore
{
public:
	virtual void Show() = 0;
};


//单核A  
class SingleCoreA : public SingleCore
{
public:
	void Show() { cout << "SingleCore A" << endl; }
};


//单核B  
class SingleCoreB : public SingleCore
{
public:
	void Show() { cout << "SingleCore B" << endl; }
};

//唯一的工厂，可以生产两种型号的处理器核，在内部判断  
class Factory
{
public:
	SingleCore* CreateSingleCore(enum CTYPE ctype)
	{
		if (ctype == COREA) //工厂内部判断  
			return new SingleCoreA(); //生产核A  
		else if (ctype == COREB)
			return new SingleCoreB(); //生产核B  
		else
			return nullptr;
	}
};


int main()
{
	return 0;
}