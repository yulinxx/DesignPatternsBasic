// 代理模式(Proxy Pattern)


/*
虚代理的情况，下面给两个智能引用的例子。
一个是C++中的auto_ptr，另一个是smart_ptr。自己实现了一下。
给出auto_ptr的代码实现：
*/


/*
https://blog.csdn.net/wuzhekai1985/article/details/6669219
auto_ptr 类就是一个代理，客户只需操作auto_prt的对象，而不需要与被代理的指针pointee打交道。
auto_ptr 的好处在于为动态分配的对象提供异常安全。
因为它用一个对象存储需要被自动释放的资源，然后依靠对象的析构函数来释放资源。
这样客户就不需要关注资源的释放，由auto_ptr 对象自动完成。
实现中的一个关键就是重载了解引用操作符和箭头操作符，从而使得auto_ptr的使用与真实指针类似。

我们知道C++中没有垃圾回收机制，可以通过智能指针来弥补，
下面给出智能指针的一种实现，采用了引用计数的策略。
*/

template<class T>
class auto_ptr {
public:
	explicit auto_ptr(T *p = 0) : pointee(p) {}
	auto_ptr(auto_ptr<T>& rhs) : pointee(rhs.release()) {}
	~auto_ptr() { delete pointee; }

	auto_ptr<T>& operator=(auto_ptr<T>& rhs)
	{
		if (this != &rhs) reset(rhs.release());
		return *this;
	}

	T& operator*() const { return *pointee; }
	T* operator->() const { return pointee; }
	T* get() const { return pointee; }

	T* release()
	{
		T *oldPointee = pointee;
		pointee = 0;
		return oldPointee;
	}

	void reset(T *p = 0)
	{
		if (pointee != p) {
			delete pointee;
			pointee = p;
		}
	}

private:
	T *pointee;
};



template <typename T>
class smart_ptr
{
public:
	smart_ptr(T *p = 0) : pointee(p), count(new size_t(1)) { }  //初始的计数值为1
	smart_ptr(const smart_ptr &rhs) : 
		pointee(rhs.pointee), count(rhs.count) { ++*count; } //拷贝构造函数，计数加1

	~smart_ptr() { decr_count(); }              //析构，计数减1，减到0时进行垃圾回收，即释放空间

	smart_ptr& operator= (const smart_ptr& rhs) //重载赋值操作符
	{
		//给自身赋值也对，因为如果自身赋值，计数器先减1，再加1，并未发生改变
		++*count;
		decr_count();
		pointee = rhs.pointee;
		count = rhs.count;
		return *this;
	}

	//重载箭头操作符和解引用操作符，未提供指针的检查
	T *operator->() { return pointee; }
	const T *operator->() const { return pointee; }
	T &operator*() { return *pointee; }
	const T &operator*() const { return *pointee; }
	size_t get_refcount() { return *count; } //获得引用计数器值

private:
	T *pointee;       //实际指针，被代理  
	size_t *count;    //引用计数器

	void decr_count() //计数器减1
	{
		if (--*count == 0)
		{
			delete pointee;
			delete count;
		}
	}
};