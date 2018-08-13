// ����ģʽ(Proxy Pattern)


/*
�ĵ���Ƕ��ͼ�ζ�����ĵ��༭������Щͼ�ζ���Ĵ��������ܴ�
���Ǵ��ĵ������Ѹ�٣���������ڴ��ĵ�ʱӦ����һ���Դ������п����ܴ�Ķ���
����Ϳ������ô���ģʽ���ڴ��ĵ�ʱ��������ͼ�ζ��󣬶��Ǵ�ͼ�ζ���Ĵ����������ʵ��ͼ�Ρ�
����������Ҫ��ͼ��ʱ�����ɴ�����򿪡�
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
		if (m_bigImage == NULL)
			m_bigImage = new BigImage(m_imageName);
		m_bigImage->Show();
	}
};


// �ͻ����ã�

int main()
{
	Image *image = new BigImageProxy("proxy.jpg"); //����
	image->Show(); //��Ҫʱ�ɴ������
	delete image;
	return 0;
}