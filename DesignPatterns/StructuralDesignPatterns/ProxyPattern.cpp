// 代理模式(Proxy Pattern)

// 代理模式：为其它对象提供一种代理以控制这个对象的访问。
// 在某些情况下，一个对象不适合或者不能直接引用另一个对象，而代理对象可以在客户端和目标对象之间起到中介作用。
// 优点：
// 职责清晰。真实的角色只负责实现实际的业务逻辑，不用关心其它非本职责的事务，通过后期的代理完成具体的任务。这样代码会简洁清晰。
// 代理对象可以在客户端和目标对象之间起到中介的作用，这样就保护了目标对象。
// 扩展性好。

// 关键代码：一个是真正的你要访问的对象(目标类)，一个是代理对象,
// 真正对象与代理对象实现同一个接口,先访问代理类再访问真正要访问的对象。

/*
文档中嵌入图形对象的文档编辑器。有些图形对象的创建开销很大。
但是打开文档必须很迅速，因此我们在打开文档时应避免一次性创建所有开销很大的对象。
这里就可以运用代理模式，在打开文档时，并不打开图形对象，而是打开图形对象的代理以替代真实的图形。
待到真正需要打开图形时，仍由代理负责打开。
*/


#include <string>
#include <iostream>
using namespace std;

class Image
{
public:
	Image(string name) : m_imageName(name) {}
	virtual ~Image() {}
	virtual void Show() {}

protected:
	string m_imageName;
};

class BigImage : public Image
{
public:
	BigImage(string name) :Image(name) {}
	~BigImage() {}
	void Show() { cout << "Show big image : " << m_imageName << endl; }
};

class BigImageProxy : public Image
{
private:
	BigImage *m_bigImage;

public:
	BigImageProxy(string name) :Image(name), m_bigImage(0) {}
	~BigImageProxy() { delete m_bigImage; }

	void Show()
	{
		if (m_bigImage == nullptr)
			m_bigImage = new BigImage(m_imageName);
		m_bigImage->Show();
	}
};


///////////////////////////////////////////////////////
// 客户调用：
int main()
{
	std::cout<<"结构型模式 之 代理模式(Proxy Pattern)\n\n";

	Image *image = new BigImageProxy("proxy.jpg"); //代理
	image->Show(); //需要时由代理负责打开
	delete image;
	return 0;
}