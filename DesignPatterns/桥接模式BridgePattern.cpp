//桥接模式(Bridge Pattern)


#include <iostream>
using namespace std;


//操作系统
class OS
{
public:
	virtual void InstallOS_Imp() {}
};

class WindowOS : public OS
{
public:
	void InstallOS_Imp() { cout << "安装Window操作系统" << endl; }
};

class LinuxOS : public OS
{
public:
	void InstallOS_Imp() { cout << "安装Linux操作系统" << endl; }
};


//计算机
class Computer
{
public:
	virtual void InstallOS(OS *pOS) {}
};

class DellComputer : public Computer
{
public:
	void InstallOS(OS *pOS) { pOS->InstallOS_Imp(); }
};


class HPComputer : public Computer
{
public:
	void InstallOS(OS *pOS) { pOS->InstallOS_Imp(); }
};


// 客户使用方式：
int main()
{
	OS *pOSWnd = new WindowOS();
	OS *pOSLinux = new LinuxOS();

	Computer *pDellComputer = new DellComputer();
	pDellComputer->InstallOS(pOSWnd);

	Computer *pHpComputer = new HPComputer();
	pHpComputer->InstallOS(pOSLinux);
	return 0;
}