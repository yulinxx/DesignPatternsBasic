#include <iostream>
using namespace std;

// �򵥹���ģʽ Simple Factory Pattern
enum CTYPE { COREA, COREB };

class SingleCore
{
public:
	virtual void Show() = 0;
};


//����A  
class SingleCoreA : public SingleCore
{
public:
	void Show() { cout << "SingleCore A" << endl; }
};


//����B  
class SingleCoreB : public SingleCore
{
public:
	void Show() { cout << "SingleCore B" << endl; }
};

//Ψһ�Ĺ������������������ͺŵĴ������ˣ����ڲ��ж�  
class Factory
{
public:
	SingleCore* CreateSingleCore(enum CTYPE ctype)
	{
		if (ctype == COREA) //�����ڲ��ж�  
			return new SingleCoreA(); //������A  
		else if (ctype == COREB)
			return new SingleCoreB(); //������B  
		else
			return NULL;
	}
};