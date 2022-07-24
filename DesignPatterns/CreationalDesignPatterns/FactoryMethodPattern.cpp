/*
 * @Author: xx xx@ubuntu.com
 * @Date: 2022-07-24 18:00:47
 * @LastEditors: xx xx@ubuntu.com
 * @LastEditTime: 2022-07-24 22:22:10
 * @FilePath: /DesignPatternsBasic/DesignPatterns/CreationalDesignPatterns/FactoryMethodPattern.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

// 工厂模式
// 在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。工厂模式作为一种创建模式，一般在创建复杂对象时，考虑使用；在创建简单对象时，建议直接new完成一个实例对象的创建。


// 工厂方法模式 定义一个创建对象的接口，其子类去具体现实这个接口以完成具体的创建工作。如果需要增加新的产品类，只需要扩展一个相应的工厂类即可。
// 缺点：产品类数据较多时，需要实现大量的工厂类，这无疑增加了代码量。

// 1.为了提高内聚（Cohesion）和松耦合（Coupling），我们经常会抽象出一些类的公共接口以形成抽象基类或者接口。这样我们可以通过声明一个指向基类的指针来指向实际的子类实现，达到了多态的目的。这里很容易出现的一个问题 n 多的子类继承自抽象基类，我们不得不在每次要用到子类的地方就编写诸如 new ×××;的代码。这里带来两个问题：
// 客户程序员必须知道实际子类的名称（当系统复杂后，命名将是一个很不好处理的问题，为了处理可能的名字冲突，有的命名可能并不是具有很好的可读性和可记忆性，就姑且不论不同程序员千奇百怪的个人偏好了）。
// 程序的扩展性和维护变得越来越困难。
// 2.还有一种情况就是在父类中并不知道具体要实例化哪一个具体的子类。这里的意思为：假设我们在类 A 中要使用到类 B，B 是一个抽象父类，在 A 中并不知道具体要实例化那一个 B 的子类，但是在类 A 的子类 D 中是可以知道的。在 A 中我们没有办法直接使用类似于 new ×××的语句，因为根本就不知道×××是什么。

// 以上两个问题也就引出了工厂模式的两个最重要的功能：
// 定义创建对象的接口，封装了对象的创建；
// 使得具体化类的工作延迟到了子类中。

// 对于工厂模式，为了使其能更好的解决多种情况的问题，将其分为三类：简单工厂模式（Simple Factory），工厂方法模式（Factory Method），抽象工厂模式（Abstract Factory）。
// 三种工厂模式的C++实现_weixin_34227447的博客-CSDN博客
// https://blog.csdn.net/weixin_34227447/article/details/92181959


// 缺点：每增加一种产品，就需要增加一个对象的工厂, 相比简单工厂模式，工厂方法模式需要更多的类定义

#include <iostream>
using namespace std;

// 工厂方法模式 Factory Method Pattern
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

class Factory
{
public:
	virtual SingleCore* CreateSingleCore() = 0;
};

/////////////////////////////////////
//生产A核的工厂  
class FactoryA : public Factory
{
public:
	SingleCoreA* CreateSingleCore() { return new SingleCoreA; }
};

//生产B核的工厂  
class FactoryB : public Factory
{
public:
	SingleCoreB* CreateSingleCore() { return new SingleCoreB; }
};


///////////////////////////////////////////////////////
int main()
{
	std::cout<<"创建型模式 之 工厂方法模式 \n\n";
	return 0;
}