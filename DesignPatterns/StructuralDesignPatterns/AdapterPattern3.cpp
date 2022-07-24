/*
 * @Author: xx xx@ubuntu.com
 * @Date: 2022-06-26 16:37:21
 * @LastEditors: xx xx@ubuntu.com
 * @LastEditTime: 2022-07-24 22:15:54
 * @FilePath: /DesignPatternsBasic/DesignPatterns/StructuralDesignPatterns/AdapterPattern3.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

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


///////////////////////////////////////////////////////
int main()
{
	std::cout<<"结构型模式 之 适配器模式 3\n\n";
	CEnOutletAdaptee *pEnOutletAdaptee = new CEnOutletAdaptee;

	CCnOutletTarget *pCnOutletTarget = new CCnOutletTarget();
	//CCnOutletTarget *pCnOutletTarget = new CCnOutletAdapter(pEnOutletAdaptee);

	pCnOutletTarget->Cnplug();

	delete pEnOutletAdaptee;
	delete pCnOutletTarget;

	system("pause");
	return 0;
}