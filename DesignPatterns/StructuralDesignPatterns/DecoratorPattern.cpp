// 装饰模式(Decorator Pattern)
// 装饰模式：动态地给一个对象添加一些额外的功能，它是通过创建一个包装对象，也就是装饰来包裹真实的对象。
// 新增加功能来说，装饰器模式比生产子类更加灵活。

// 以下情形考虑使用装饰模式：
// 需要扩展一个类的功能，或给一个类添加附加职责。
// 需要动态的给一个对象添加功能，这些功能可以再动态的撤销。
// 需要增加由一些基本功能的排列组合而产生的非常大量的功能，从而使继承关系变的不现实。
// 当不能采用生成子类的方法进行扩充时。一种情况是，可能有大量独立的扩展，为支持每一种组合将产生大量的子类，
// 使得子类数目呈爆炸性增长。另一种情况可能是因为类定义被隐藏，或类定义不能用于生成子类。

#include <string>
#include <iostream>
using namespace std;

// --------------------------
// 公共抽象类
class Phone
{
public:
	Phone() {}
	virtual ~Phone() {}
	virtual void ShowDecorate() {}
};

// --------------------------
// 具体的手机类的定义：

//具体的手机类
class iPhone : public Phone
{
private:
	string m_name; //手机名称
public:
	iPhone(string name) : m_name(name) {}
	~iPhone() {}
	void ShowDecorate() { cout << m_name << "的装饰" << endl; }
};

// 具体的手机类
class NokiaPhone : public Phone
{
private:
	string m_name;
public:
	NokiaPhone(string name) : m_name(name) {}
	~NokiaPhone() {}
	void ShowDecorate() { cout << m_name << "的装饰" << endl; }
};

// --------------------------
// 装饰类的实现：

//装饰类
class DecoratorPhone : public Phone
{
private:
	Phone *m_phone;  //要装饰的手机
public:
	DecoratorPhone(Phone *phone) : m_phone(phone) {}
	virtual void ShowDecorate() { m_phone->ShowDecorate(); }
};
// --------------------------
// 具体的装饰类
class DecoratorPhoneA : public DecoratorPhone
{
public:
	DecoratorPhoneA(Phone *phone) : DecoratorPhone(phone) {}
	void ShowDecorate() { DecoratorPhone::ShowDecorate(); AddDecorate(); }
private:
	void AddDecorate() { cout << "增加挂件" << endl; } // 增加的装饰
};

// 具体的装饰类
class DecoratorPhoneB : public DecoratorPhone
{
public:
	DecoratorPhoneB(Phone *phone) : DecoratorPhone(phone) {}
	void ShowDecorate() { DecoratorPhone::ShowDecorate(); AddDecorate(); }
private:
	void AddDecorate() { cout << "屏幕贴膜" << endl; } // 增加的装饰
};


///////////////////////////////////////////////////////
// 客户使用方式：
int main()
{
	std::cout<<"结构型模式 之 装饰模式(Decorator Pattern)\n\n";

	Phone *pPohone = new NokiaPhone("6300");
	Phone *dpa = new DecoratorPhoneA(pPohone); // 装饰，增加挂件
	Phone *dpb = new DecoratorPhoneB(dpa);    // 装饰，屏幕贴膜
	dpb->ShowDecorate();

	delete dpa;
	delete dpb;
	delete pPohone;
	return 0;
}