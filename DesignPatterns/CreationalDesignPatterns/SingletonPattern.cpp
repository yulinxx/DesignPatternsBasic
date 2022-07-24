// 单例模式顾名思义，保证一个类仅可以有一个实例化对象，并且提供一个可以访问它的全局接口。
// 实现单例模式必须注意一下几点：
// 单例类只能由一个实例化对象。单例类必须自己提供一个实例化对象。
// 单例类必须提供一个可以访问唯一实例化对象的接口。
// 单例模式分为懒汉和饿汉两种实现方式。

// 懒汉单例模式
// 懒汉：故名思义，不到万不得已就不会去实例化类，也就是说在第一次用到类实例的时候才会去实例化一个对象。
// 在访问量较小，甚至可能不会去访问的情况下，采用懒汉实现，这是以时间换空间。

// 饿汉单例模式
// 饿汉：饿了肯定要饥不择食。所以在单例类定义的时候就进行实例化。
// 在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间。

// 保证一个类仅有一个实例，并提供一个访问它的全局访问点
// 实现要点
// 构造函数应该声明为非公有，从而禁止外界创建实例。
// 拷贝操作和移动操作也应该禁止。
// 只能通过 Singleton 的公有特定类操作访问它的唯一实例（C++中的一个公有静态成员函数）。
// 有局部静态对象和动态内存分配两种实现，C++11起最佳实践是局部静态对象的方法。
// 线程安全。

// 单例模式三种模式，饿汉(饥汉)、饱汉(懒汉)、双重锁模式

// 懒汉和饿汉的最大区别就在于创建对象时候是否实例化；有new就是饿汉，反之就是懒汉

// 懒汉式的特点是延迟加载，比如配置文件，采用懒汉式的方法，
// 顾名思义，懒汉么，很懒的，配置文件的实例直到用到的时候才会加载。

// 饿汉式的特点是一开始就加载了，如果说懒汉式是“时间换空间”，
// 那么饿汉式就是“空间换时间”，因为一开始就创建了实例，所以每次用到的之后直接返回就好了。

// https://blog.csdn.net/kai_zone/article/details/103098810

#include <iostream>
#include <cassert>
#include <mutex>

/////////////////////////////////////
//  懒汉式
// 最推荐的懒汉式单例(magic static )——局部静态变量
// 保证了并发线程在获取静态局部变量的时候一定是初始化过的，所以具有线程安全性。
// 这是最推荐的一种单例实现方式：

// 通过局部静态变量的特性保证了线程安全 (C++11, GCC > 4.3, VS2015支持该特性);
// 不需要使用共享指针，代码简洁；
// 注意在使用的时候需要声明单例的引用 Single& 才能获取对象。
// 另外网上有人的实现返回指针而不是返回引用
// static Singleton* get_instance(){
//     static Singleton instance;
//     return &instance;
// }
// 这样做并不好，理由主要是无法避免用户使用delete instance导致对象被提前销毁。还是建议大家使用返回引用的方式。
class Singleton
{
public:
	~Singleton()
	{
		std::cout << "destructor called!" << std::endl;
	}
	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton &) = delete;
	static Singleton &get_instance()
	{
		static Singleton instance;
		return instance;
	}

private:
	Singleton()
	{
		std::cout << "constructor called!" << std::endl;
	}
};

/////////////////////////////////////
//  懒汉式
// 存在内存泄漏. 注意到类中只负责new出对象，却没有负责delete对象，
// 因此只有构造函数被调用，析构函数却没有被调用;因此会导致内存泄漏。
// 解决办法： 使用共享指针;
class SingletonB
{
private:
	SingletonB()
	{
		std::cout << "constructor called!" << std::endl;
	}

	SingletonB(SingletonB &) = delete;
	SingletonB &operator=(const Singleton &) = delete;
	static SingletonB *m_instance_ptr;
	static std::mutex m_mutex;

public:
	~SingletonB()
	{
		std::cout << "destructor called!" << std::endl;
	}

	static SingletonB *get_instance()
	{
		// 加锁，使用互斥量来达到线程安全。这里使用了两个 if 判断语句的技术称为双检锁；
		// 好处是，只有判断指针为空的时候才加锁，避免每次调用 get_instance的方法都加锁，锁的开销毕竟还是有点大的。
		if (m_instance_ptr == nullptr)
		{
			std::lock_guard<std::mutex> lk(m_mutex);
			if (m_instance_ptr == nullptr)
			{
				m_instance_ptr = new SingletonB();
			}
			return m_instance_ptr;
		}
	}
	void use() const { std::cout << "in use" << std::endl; }
};

SingletonB *SingletonB::m_instance_ptr = nullptr;
std::mutex SingletonB::m_mutex;

/////////////////////////////////////
// 饿汉模式
class SingletonC
{
public:
	static SingletonC *getintence()
	{
		return &intence;
	}

private:
	SingletonC()
	{
	}
	/*Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);*/
	//这个为C++98，如果时在类内定义的友元函数还可以构建新的对象
	SingletonC(const SingletonC &) = delete;			//所以C++13对这个问题进行了完善 提供了直接删除这个函数，
														// 它定义在pubic里面也不能进行拷贝构造和赋值
	SingletonC &operator=(const SingletonC &) = delete; // c++13里面提供了直接删除
	static SingletonC intence;
};

SingletonC SingletonC::intence;


///////////////////////////////////////////////////////
int main()
{
	std::cout<<"创建型模式 之 单例模式 \n\n";

	auto &a = Singleton::get_instance();
	auto &b = Singleton::get_instance();
	assert(&a == &b);

	SingletonB *instance = SingletonB::get_instance();
	SingletonB *instance_2 = SingletonB::get_instance();

	SingletonC *instanceC = SingletonC::getintence();

	return 0;
}