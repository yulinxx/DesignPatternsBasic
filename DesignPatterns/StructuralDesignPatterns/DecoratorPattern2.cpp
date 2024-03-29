/*
 * @Author: xx xx@ubuntu.com
 * @Date: 2022-06-26 16:37:21
 * @LastEditors: xx xx@ubuntu.com
 * @LastEditTime: 2022-07-24 22:10:58
 * @FilePath: /DesignPatternsBasic/DesignPatterns/StructuralDesignPatterns/DecoratorPattern2.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// 装饰模式(Decorator Pattern)

/*******************************************
* 装饰者模式  演示   2014.5.12             *
* by hnust_xiehonghao                      *
********************************************/

#include <iostream>
using namespace std;

//坦克抽象类 component
class Tank
{
public:

	virtual void shot()
	{
		cout << "向我开炮！" << endl;
	}
};

//Concrete Component  
class T50 :public Tank //具体的一种坦克 型号为T50 也可以有很多其它种类的坦克
{
public:
	void shot()
	{
		cout << "T50开炮" << endl;
	}
};

//Decorator   
class Decorator : public Tank//此处不应认为是is_a关系 而应该认为是like_a
{
protected:  //这里必须是protect哦  因为其它继承Decorator的类要用
	Tank *tank;//has_a的关系

public:
	void decorator(Tank *_tank)
	{
		this->tank = _tank;
	}
	void shot()
	{
		tank->shot();
	}
};


//DecoratorA  加大火力
class BigShot :public  Decorator
{

public:
	void shot()
	{
		//为了死的安详，我想被大火力打死，另外请静音
		cout << "大火力准备完毕" << endl;
		tank->shot();

	}
};


//DecoratorB     消音
class SilentShot :public Decorator
{

public:
	void shot()
	{
		//为保证是被炮打死 而不是震死，请静音
		cout << "消音完毕" << endl;
		tank->shot();
	}
};


///////////////////////////////////////////////////////
int main()
{
	std::cout<<"结构型模式 之 装饰模式(Decorator Pattern)\n\n";
	
	Tank *pTank = new T50();
	Decorator *pDecorator = new Decorator();
	pDecorator->decorator(pTank);

	BigShot *pBig = new BigShot();
	pBig->decorator(pDecorator);

	SilentShot *pBigSlient = new SilentShot();
	pBigSlient->decorator(pBig);

	pBigSlient->shot();

	return 0;
}
