#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

//父类  
class Resume
{
protected:
	char *name;
public:
	Resume() {}
	virtual ~Resume() {}
	virtual Resume* Clone() { return NULL; }
	virtual void Set(char *n) {}
	virtual void Show() {}
};

class ResumeA : public Resume
{
public:
	ResumeA(const char *str);  //构造函数  
	ResumeA(const ResumeA &r); //拷贝构造函数  
	~ResumeA();                //析构函数  
	ResumeA* Clone();          //克隆，关键所在  
	void Show();               //显示内容  
};

ResumeA::ResumeA(const char *str)
{
	if (str == NULL) {
		name = new char[1];
		name[0] = '\0';
	}
	else {
		name = new char[strlen(str) + 1];
		strcpy(name, str);
	}
}

ResumeA::~ResumeA() { delete[] name; }
ResumeA::ResumeA(const ResumeA &r) {
	name = new char[strlen(r.name) + 1];
	strcpy(name, r.name);
}

ResumeA* ResumeA::Clone() {
	return new ResumeA(*this);
}

void ResumeA::Show() {
	cout << "ResumeA name : " << name << endl;
}

class ResumeB : public Resume
{
public:
	ResumeB(const char *str);  //构造函数  
	ResumeB(const ResumeB &r); //拷贝构造函数  
	~ResumeB();                //析构函数  
	ResumeB* Clone();          //克隆，关键所在  
	void Show();               //显示内容  
};

ResumeB::ResumeB(const char *str)
{
	if (str == NULL) {
		name = new char[1];
		name[0] = '\0';
	}
	else {
		name = new char[strlen(str) + 1];
		strcpy(name, str);
	}
}

ResumeB::~ResumeB() { delete[] name; }

ResumeB::ResumeB(const ResumeB &r) {
	name = new char[strlen(r.name) + 1];
	strcpy(name, r.name);
}

ResumeB* ResumeB::Clone() {
	return new ResumeB(*this);
}

void ResumeB::Show() {
	cout << "ResumeB name : " << name << endl;
}

int main(int argc, char* argv[])
{
	Resume *r1 = new ResumeA("A");
	Resume *r2 = new ResumeB("B");
	Resume *r3 = r1->Clone();
	Resume *r4 = r2->Clone();

	r1->Show(); r2->Show();

	//删除r1,r2  
	delete r1; delete r2;
	r1 = r2 = NULL;

	//深拷贝所以对r3,r4无影响  
	r3->Show(); r4->Show();
	delete r3; delete r4;
	r3 = r4 = NULL;
	return 0;
}