#include <iostream>
#include <string>

using namespace std;
// --------------------
// Adaptee：适配者类 英式插头
class CEnOutletAdaptee
{
public:
	void EnPlug()
	{
		cout << "use en plug" << endl;
	}
};
// --------------------
// Target：目标抽象类  中式插座 
class CCnOutletTarget
{
public:
	virtual ~CCnOutletTarget() {};
	virtual void Cnplug()
	{
		cout << "中式插座！" << endl;
	};
};
// --------------------
// Adapter：适配器类 
class CCnOutletAdapter : public CCnOutletTarget
{
public:
	CCnOutletAdapter(CEnOutletAdaptee* pEnOutletAdaptee) :
		m_pEnOutletAdaptee(pEnOutletAdaptee) {};
	virtual ~CCnOutletAdapter() {};

	virtual void Cnplug()
	{
		cout << "adapter transfer" << endl;
		m_pEnOutletAdaptee->EnPlug();
	}

private:
	CEnOutletAdaptee* m_pEnOutletAdaptee;
};

// --------------------
int main()
{
	CEnOutletAdaptee *pEnOutletAdaptee = new CEnOutletAdaptee;

	CCnOutletTarget *pCnOutletTarget = new CCnOutletTarget();
	//CCnOutletTarget *pCnOutletTarget = new CCnOutletAdapter(pEnOutletAdaptee);

	pCnOutletTarget->Cnplug();

	delete pEnOutletAdaptee;
	delete pCnOutletTarget;

	system("pause");
	return 0;
}