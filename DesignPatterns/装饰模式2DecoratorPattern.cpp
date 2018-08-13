// װ��ģʽ(Decorator Pattern)

/*******************************************
* װ����ģʽ  ��ʾ   2014.5.12             *
* by hnust_xiehonghao                      *
********************************************/

#include <iostream>
using namespace std;

//̹�˳����� component
class Tank
{
public:

	virtual void shot()
	{
		cout << "���ҿ��ڣ�" << endl;
	}
};

//Concrete Component  
class T50 :public Tank //�����һ��̹�� �ͺ�ΪT50 Ҳ�����кܶ����������̹��
{
public:
	void shot()
	{
		cout << "T50����" << endl;
	}
};

//Decorator   
class Decorator : public Tank//�˴���Ӧ��Ϊ��is_a��ϵ ��Ӧ����Ϊ��like_a
{
protected:  //���������protectŶ  ��Ϊ�����̳�Decorator����Ҫ��
	Tank *tank;//has_a�Ĺ�ϵ

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


//DecoratorA  �Ӵ����
class BigShot :public  Decorator
{

public:
	void shot()
	{
		//Ϊ�����İ��꣬���뱻����������������뾲��
		cout << "�����׼�����" << endl;
		tank->shot();

	}
};


//DecoratorB     ����
class SilentShot :public Decorator
{

public:
	void shot()
	{
		//Ϊ��֤�Ǳ��ڴ��� �������������뾲��
		cout << "�������" << endl;
		tank->shot();
	}
};

int main()
{
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
