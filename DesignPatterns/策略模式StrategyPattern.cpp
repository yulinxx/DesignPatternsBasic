

//����ӿ�
class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};
//���־�����滻�㷨
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


// ���Ÿ���Cache�Ķ��壬����ܹؼ���Cache��ʵ�ַ�ʽֱ��Ӱ���˿ͻ���ʹ�÷�ʽ����ؼ��������ָ���滻�㷨��

// ��ʽһ��ֱ��ͨ������ָ��������һ���ض��㷨��ָ�롣

//Cache��Ҫ�õ��滻�㷨
class Cache
{
private:
	ReplaceAlgorithm *m_ra;
public:
	Cache(ReplaceAlgorithm *ra) { m_ra = ra; }
	~Cache() { delete m_ra; }
	void Replace() { m_ra->Replace(); }
};


//��������ַ�ʽ���ͻ�����Ҫ֪����Щ�㷨�ľ��嶨�塣ֻ�����������ַ�ʽʹ�ã����Կ�����¶��̫���ϸ�ڡ�

int main()
{
	Cache cache(new LRU_ReplaceAlgorithm()); //��¶���㷨�Ķ���
	cache.Replace();
	return 0;
}


// ��ʽ����Ҳ��ֱ��ͨ������ָ����ֻ�������Ǵ���ָ�룬����һ����ǩ�������ͻ�ֻҪ֪���㷨����Ӧ��ǩ���ɣ�������Ҫ֪���㷨�ľ��嶨�塣
//Cache��Ҫ�õ��滻�㷨
enum RA { LRU, FIFO, RANDOM }; //��ǩ
class Cache
{
private:
	ReplaceAlgorithm *m_ra;
public:
	Cache(enum RA ra)
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
	~Cache() { delete m_ra; }
	void Replace() { m_ra->Replace(); }
};

//��ȷ�ʽһ�����ַ�ʽ������������ˡ���ʵ���ַ�ʽ���򵥹���ģʽ�����ģʽ�����һ���㷨�Ķ���ʹ���˲���ģʽ����Cache�Ķ�����ʵʹ���˼򵥹���ģʽ��
int main()
{
	Cache cache(LRU); //ָ����ǩ����
	cache.Replace();
	return 0;
}
�������ַ�ʽ�����캯������Ҫ�βΡ����캯���Ƿ���Բ��ò����أ��������������ʵ�ַ�ʽ��
��ʽ��������ģ��ʵ�֡��㷨ͨ��ģ���ʵ��ָ������Ȼ�ˣ�����ʹ���˲�����ֻ�������ǹ��캯���Ĳ������ڲ���ģʽ�У������Ĵ������Ա��⣬�ͻ�����ָ��ĳ���㷨��

//Cache��Ҫ�õ��滻�㷨
template <class RA>
class Cache
{
private:
	RA m_ra;
public:
	Cache() { }
	~Cache() { }
	void Replace() { m_ra.Replace(); }
};
ʹ�÷�ʽ���£�
int main()
{
	Cache<Random_ReplaceAlgorithm> cache; //ģ��ʵ��
	cache.Replace();
	return 0;
}