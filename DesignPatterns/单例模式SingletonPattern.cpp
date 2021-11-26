#include <iostream>
using namespace std;


class Singleton
{
public:
	static Singleton* GetInstance(const char* name);
	virtual void Show() {}
protected:  //必须为保护，如果是私有属性，子类无法访问父类的构造函数
	Singleton() {}
private:
	static Singleton *singleton; //唯一实例的指针
};


Singleton* Singleton::singleton = NULL;

class SingletonA;
class SingletonB;



class SingletonA : public Singleton
{
	friend class Singleton; //必须为友元类，否则父类无法访问子类的构造函数
public:
	void Show() { cout << "SingletonA" << endl; }
private:   //为保护属性，这样外界无法通过构造函数进行实例化
	SingletonA() {}
};


class SingletonB : public Singleton
{
	friend class Singleton; //必须为友元类，否则父类无法访问子类的构造函数
public:
	void Show() { cout << "SingletonB" << endl; }
private:  //为保护属性，这样外界无法通过构造函数进行实例化
	SingletonB() {}
};


Singleton* Singleton::GetInstance(const char* name)
{
	if (singleton == NULL)
	{
		if (strcmp(name, "SingletonA") == 0)
			singleton = new SingletonA();
		else if (strcmp(name, "SingletonB") == 0)
			singleton = new SingletonB();
		else
			singleton = new Singleton();
	}
	return singleton;
}



int main()
{
	Singleton *st = Singleton::GetInstance("SingletonA");
	st->Show();
	return 0;
}