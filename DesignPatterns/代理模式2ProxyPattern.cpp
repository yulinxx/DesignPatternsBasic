// ����ģʽ(Proxy Pattern)


/*
���������������������������õ����ӡ�
һ����C++�е�auto_ptr����һ����smart_ptr���Լ�ʵ����һ�¡�
����auto_ptr�Ĵ���ʵ�֣�
*/


/*
https://blog.csdn.net/wuzhekai1985/article/details/6669219
auto_ptr �����һ�������ͻ�ֻ�����auto_prt�Ķ��󣬶�����Ҫ�뱻�����ָ��pointee�򽻵���
auto_ptr �ĺô�����Ϊ��̬����Ķ����ṩ�쳣��ȫ��
��Ϊ����һ������洢��Ҫ���Զ��ͷŵ���Դ��Ȼ����������������������ͷ���Դ��
�����ͻ��Ͳ���Ҫ��ע��Դ���ͷţ���auto_ptr �����Զ���ɡ�
ʵ���е�һ���ؼ����������˽����ò������ͼ�ͷ���������Ӷ�ʹ��auto_ptr��ʹ������ʵָ�����ơ�

����֪��C++��û���������ջ��ƣ�����ͨ������ָ�����ֲ���
�����������ָ���һ��ʵ�֣����������ü����Ĳ��ԡ�
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
	smart_ptr(T *p = 0) : pointee(p), count(new size_t(1)) { }  //��ʼ�ļ���ֵΪ1
	smart_ptr(const smart_ptr &rhs) : 
		pointee(rhs.pointee), count(rhs.count) { ++*count; } //�������캯����������1

	~smart_ptr() { decr_count(); }              //������������1������0ʱ�����������գ����ͷſռ�

	smart_ptr& operator= (const smart_ptr& rhs) //���ظ�ֵ������
	{
		//������ֵҲ�ԣ���Ϊ�������ֵ���������ȼ�1���ټ�1����δ�����ı�
		++*count;
		decr_count();
		pointee = rhs.pointee;
		count = rhs.count;
		return *this;
	}

	//���ؼ�ͷ�������ͽ����ò�������δ�ṩָ��ļ��
	T *operator->() { return pointee; }
	const T *operator->() const { return pointee; }
	T &operator*() { return *pointee; }
	const T &operator*() const { return *pointee; }
	size_t get_refcount() { return *count; } //������ü�����ֵ

private:
	T *pointee;       //ʵ��ָ�룬������  
	size_t *count;    //���ü�����

	void decr_count() //��������1
	{
		if (--*count == 0)
		{
			delete pointee;
			delete count;
		}
	}
};