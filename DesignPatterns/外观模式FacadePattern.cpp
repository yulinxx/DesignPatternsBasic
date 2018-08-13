// ���ģʽ(Facade Pattern)

#include <iostream>
using namespace std;

class Scanner
{
public:
	void Scan() { cout << "�ʷ�����" << endl; }
};

class Parser
{
public:
	void Parse() { cout << "�﷨����" << endl; }
};

class GenMidCode
{
public:
	void GenCode() { cout << "�����м����" << endl; }
};

class GenMachineCode
{
public:
	void GenCode() { cout << "����������" << endl; }
};

//�߲�ӿ�
class Compiler
{
public:
	void Run()
	{
		Scanner scanner;
		Parser parser;
		GenMidCode genMidCode;
		GenMachineCode genMacCode;
		scanner.Scan();
		parser.Parse();
		genMidCode.GenCode();
		genMacCode.GenCode();
	}
};


// �ͻ�ʹ�÷�ʽ��
int main()
{
	Compiler compiler;
	compiler.Run();
	return 0;
}