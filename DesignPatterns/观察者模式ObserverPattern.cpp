
/*
当博主发表新文章的时候，即博主状态发生了改变，那些订阅的读者就会收到通知，
然后进行相应的动作，比如去看文章，或者收藏起来。
博主与读者之间存在种一对多的依赖关系。
*/

#include <iostream>
#include <list>
#include <string>
using namespace std;

//观察者
class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void Update() {}
};

//博客
class Blog
{
public:
	Blog() {}
	virtual ~Blog() {}
	void Attach(Observer *observer) { m_observers.push_back(observer); }	 //添加观察者
	void Remove(Observer *observer) { m_observers.remove(observer); }        //移除观察者
	void Notify() //通知观察者
	{
		list<Observer*>::iterator iter = m_observers.begin();
		for (; iter != m_observers.end(); iter++)
			(*iter)->Update();
	}
	virtual void SetStatus(string s) { m_status = s; } //设置状态
	virtual string GetStatus() { return m_status; }    //获得状态

private:
	list<Observer* > m_observers; //观察者链表

protected:
	string m_status; //状态
};



//具体博客类
class BlogCSDN : public Blog
{
private:
	string m_name; //博主名称
public:
	BlogCSDN(string name) : m_name(name) {}
	~BlogCSDN() {}
	void SetStatus(string s) { m_status = "CSDN通知 : " + m_name + s; } //具体设置状态信息
	string GetStatus() { return m_status; }
};

//具体观察者
class ObserverBlog : public Observer
{
private:
	string m_name;  //观察者名称
	Blog *m_blog;   //观察的博客，当然以链表形式更好，就可以观察多个博客
public:
	ObserverBlog(string name, Blog *blog) : m_name(name), m_blog(blog) {}
	~ObserverBlog() {}
	void Update()  //获得更新状态
	{
		string status = m_blog->GetStatus();
		cout <<m_name << "-------" << status << endl;
	}
};

// 客户的使用方式：
int main()
{
	Blog *blog = new BlogCSDN("wuzhekai1985");
	Observer *observer1 = new ObserverBlog("tutupig", blog);
	blog->Attach(observer1);
	blog->SetStatus("发表设计模式C++实现（15）——观察者模式");
	blog->Notify();
	delete blog; 
	delete observer1;
	return 0;
}