
#include <iostream>
using namespace std;


//抽象接口
class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};

//三种具体的替换算法
class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace() { cout << "Least Recently Used replace algorithm" << endl; }
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace() { cout << "First in First out replace algorithm" << endl; }
};

class Random_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace() { cout << "Random replace algorithm" << endl; }
};

// -------------------------------------------------------------------------
// 接着给出Cache的定义，这里很关键，Cache的实现方式直接影响了客户的使用方式，
// 其关键在于如何指定替换算法。
// 方式一：直接通过参数指定，传入一个特定算法的指针。

//Cache需要用到替换算法
class CacheA
{
private:
	ReplaceAlgorithm *m_ra;
public:
	CacheA(ReplaceAlgorithm *ra) { m_ra = ra; }
	~CacheA() { delete m_ra; }
	void Replace() { m_ra->Replace(); }
};


//如果用这种方式，客户就需要知道这些算法的具体定义。
// 只能以下面这种方式使用，可以看到暴露了太多的细节。

int main()
{
	CacheA cache(new LRU_ReplaceAlgorithm()); // 暴露了算法的定义
	cache.Replace();
	return 0;
}

// -------------------------------------------------------------------------
// 方式二：也是直接通过参数指定，只不过不是传入指针，而是一个标签。
// 这样客户只要知道算法的相应标签即可，而不需要知道算法的具体定义。
//Cache需要用到替换算法
enum RA { LRU, FIFO, RANDOM }; //标签
class CacheB
{
private:
	ReplaceAlgorithm *m_ra;
public:
	CacheB(enum RA ra)
	{
		if (ra == LRU)
			m_ra = new LRU_ReplaceAlgorithm();
		else if (ra == FIFO)
			m_ra = new FIFO_ReplaceAlgorithm();
		else if (ra == RANDOM)
			m_ra = new Random_ReplaceAlgorithm();
		else
			m_ra = NULL;
	}
	~CacheB() { delete m_ra; }
	void Replace() { m_ra->Replace(); }
};

//相比方式一，这种方式用起来方便多了。其实这种方式将简单工厂模式与策略模式结合在一起，
// 算法的定义使用了策略模式，而Cache的定义其实使用了简单工厂模式。
int main()
{
	CacheB cache(LRU); //指定标签即可
	cache.Replace();
	return 0;
}


//上面两种方式，构造函数都需要形参。构造函数是否可以不用参数呢？下面给出第三种实现方式。

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
//方式三：利用模板实现。算法通过模板的实参指定。当然了，还是使用了参数，只不过不是构造函数的参数。
// 在策略模式中，参数的传递难以避免，客户必须指定某种算法。

//Cache需要用到替换算法
template <class RA>
class CacheC
{
private:
	RA m_ra;
public:
	CacheC() { }
	~CacheC() { }
	void Replace() { m_ra.Replace(); }
};

// 使用方式如下：
int main()
{
	CacheC<Random_ReplaceAlgorithm> cache; //模板实参
	cache.Replace();
	return 0;
}