//桥接模式(Bridge Pattern)
// 桥接模式：将抽象部分与实现部分分离，使它们都可以独立变换。

// 以下情形考虑使用桥接模式：
// 当一个对象有多个变化因素的时候，考虑依赖于抽象的实现，而不是具体的实现。
// 当多个变化因素在多个对象间共享时，考虑将这部分变化的部分抽象出来再聚合/合成进来。
// 当一个对象的多个变化因素可以动态变化的时候。

// 优点：
// 将实现抽离出来，再实现抽象，使得对象的具体实现依赖于抽象，满足了依赖倒转原则。
// 更好的可扩展性。
// 可动态的切换实现。桥接模式实现了抽象和实现的分离，在实现桥接模式时，就可以实现动态的选择具体的实现。

// 关键代码：将现实独立出来，抽象类依赖现实类。

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

/////////////////////////////////////
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