// 适配器模式(Adapter Pattern)

// 适配器模式可以将一个类的接口转换成客户端希望的另一个接口，使得原来由于接口不兼容而不能在一起工作的那些类可以在一起工作。
// 通俗的讲就是当我们已经有了一些类，而这些类不能满足新的需求，此时就可以考虑是否能将现有的类适配成可以满足新需求的类。
// 适配器类需要继承或依赖已有的类，实现想要的目标接口。

// 缺点：过多地使用适配器，会让系统非常零乱，不易整体进行把握。
// 比如，明明看到调用的是 A 接口，其实内部被适配成了 B 接口的实现，
// 一个系统如果太多出现这种情况，无异于一场灾难。因此如果不是很有必要，可以不使用适配器，而是直接对系统进行重构。


#include <iostream>
#include <string>
using namespace std;

//双端队列
class Deque
{
public:
	void push_back(int x) { cout << "Deque push_back" << endl; }
	void push_front(int x) { cout << "Deque push_front" << endl; }
	void pop_back() { cout << "Deque pop_back" << endl; }
	void pop_front() { cout << "Deque pop_front" << endl; }
};

//顺序容器
class Sequence
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

//栈
class Stack : public Sequence
{
public:
	void push(int x) { deque.push_back(x); }
	void pop() { deque.pop_back(); }
private:
	Deque deque; //双端队列
};

//队列
class Queue : public Sequence
{
public:
	void push(int x) { deque.push_back(x); }
	void pop() { deque.pop_front(); }
private:
	Deque deque; //双端队列
};


////////////////////////////////
int main()
{
	Sequence *s1 = new Stack();
	Sequence *s2 = new Queue();

	s1->push(1); s1->pop();

	s2->push(1); s2->pop();

	delete s1; delete s2;
	return 0;
}