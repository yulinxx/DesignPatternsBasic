//�Ž�ģʽ(Bridge Pattern)


#include <iostream>
using namespace std;


//����ϵͳ
class OS
{
public:
	virtual void InstallOS_Imp() {}
};

class WindowOS : public OS
{
public:
	void InstallOS_Imp() { cout << "��װWindow����ϵͳ" << endl; }
};

class LinuxOS : public OS
{
public:
	void InstallOS_Imp() { cout << "��װLinux����ϵͳ" << endl; }
};


//�����
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


// �ͻ�ʹ�÷�ʽ��
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