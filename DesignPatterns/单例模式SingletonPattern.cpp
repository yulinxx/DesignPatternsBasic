#include <iostream>
using namespace std;

class Singleton
{
public:
	static Singleton* GetInstance(const char* name);
	virtual void Show() {}
protected:  //����Ϊ�����������˽�����ԣ������޷����ʸ���Ĺ��캯��
	Singleton() {}
private:
	static Singleton *singleton; //Ψһʵ����ָ��
};


Singleton* Singleton::singleton = NULL;

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



class SingletonA : public Singleton
{
	friend class Singleton; //����Ϊ��Ԫ�࣬�������޷���������Ĺ��캯��
public:
	void Show() { cout << "SingletonA" << endl; }
private:   //Ϊ�������ԣ���������޷�ͨ�����캯������ʵ����
	SingletonA() {}
};


class SingletonB : public Singleton
{
	friend class Singleton; //����Ϊ��Ԫ�࣬�������޷���������Ĺ��캯��
public:
	void Show() { cout << "SingletonB" << endl; }
private:  //Ϊ�������ԣ���������޷�ͨ�����캯������ʵ����
	SingletonB() {}
};



int main()
{
	Singleton *st = Singleton::GetInstance("SingletonA");
	st->Show();
	return 0;
}