
// 建造者模式：将复杂对象的构建和其表示分离，使得相同的构建过程可以产生不同的表示。

// 以下情形可以考虑使用建造者模式：
// 对象的创建复杂，但是其各个部分的子对象创建算法一定。
// 需求变化大，构造复杂对象的子对象经常变化，但将其组合在一起的算法相对稳定。

// 建造者模式的优点：
// 将对象的创建和表示分离，客户端不需要了解具体的构建细节。
// 增加新的产品对象时，只需要增加其具体的建造类即可，不需要修改原来的代码，扩展方便。
// 产品之间差异性大，内部变化较大、较复杂时不建议使用建造者模式。



#include <iostream>
using namespace std;

class Builder
{
public:
	virtual void BuildHead() {}
	virtual void BuildBody() {}
	virtual void BuildLeftArm() {}
	virtual void BuildRightArm() {}
	virtual void BuildLeftLeg() {}
	virtual void BuildRightLeg() {}
};

//构造瘦人
class ThinBuilder : public Builder
{
public:
	void BuildHead() { cout << "build thin body" << endl; }
	void BuildBody() { cout << "build thin head" << endl; }
	void BuildLeftArm() { cout << "build thin leftarm" << endl; }
	void BuildRightArm() { cout << "build thin rightarm" << endl; }
	void BuildLeftLeg() { cout << "build thin leftleg" << endl; }
	void BuildRightLeg() { cout << "build thin rightleg" << endl; }
};

//构造胖人
class FatBuilder : public Builder
{
public:
	void BuildHead() { cout << "build fat body" << endl; }
	void BuildBody() { cout << "build fat head" << endl; }
	void BuildLeftArm() { cout << "build fat leftarm" << endl; }
	void BuildRightArm() { cout << "build fat rightarm" << endl; }
	void BuildLeftLeg() { cout << "build fat leftleg" << endl; }
	void BuildRightLeg() { cout << "build fat rightleg" << endl; }
};

//构造的指挥官
class Director
{
private:
	Builder *m_pBuilder;
public:
	Director(Builder *builder) { m_pBuilder = builder; }
	void Create() {
		m_pBuilder->BuildHead();
		m_pBuilder->BuildBody();
		m_pBuilder->BuildLeftArm();
		m_pBuilder->BuildRightArm();
		m_pBuilder->BuildLeftLeg();
		m_pBuilder->BuildRightLeg();
	}
};


///////////////////////////////////////////////////////
// 客户的使用方式;
int main()
{
	std::cout<<"创建型模式 之 建造者模式 \n\n";

	FatBuilder thin;
	Director director(&thin);
	director.Create();
	return 0;
}