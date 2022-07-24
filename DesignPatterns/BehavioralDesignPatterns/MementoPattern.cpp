// 备忘录模式MementoPattern
// 备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。
// 这样以后就可以将该对象恢复到原来保存的状态。

// 备忘录模式中需要定义的角色类：
// Originator(发起人)：
// 负责创建一个备忘录Memento，用以记录当前时刻自身的内部状态，并可使用备忘录恢复内部状态。
// Originator可以根据需要决定Memento存储自己的哪些内部状态。

// Memento(备忘录)：
// 负责存储Originator对象的内部状态，并可以防止Originator以外的其他对象访问备忘录。
// 备忘录有两个接口：Caretaker只能看到备忘录的窄接口，他只能将备忘录传递给其他对象。
// Originator却可看到备忘录的宽接口，允许它访问返回到先前状态所需要的所有数据。

// Caretaker(管理者):
// 负责备忘录Memento，不能对Memento的内容进行访问或者操作。



#include <iostream>
#include <vector>

using namespace std;

//需保存的信息
class Memento
{
public:
	int m_vitality; //生命值
	int m_attack;   //进攻值
	int m_defense;  //防守值
public:
	Memento(int vitality, int attack, int defense) :
		m_vitality(vitality), m_attack(attack), m_defense(defense) {}

	Memento& operator=(const Memento &memento)
	{
		m_vitality = memento.m_vitality;
		m_attack = memento.m_attack;
		m_defense = memento.m_defense;
		return *this;
	}
};

//游戏角色
class GameRole
{
private:
	int m_vitality; //生命值
	int m_attack;   //进攻值
	int m_defense;  //防守值
public:
	GameRole() : m_vitality(100), m_attack(100), m_defense(100) {}

	//保存进度，只与Memento对象交互，并不牵涉到Caretake
	Memento Save() 
	{
		Memento memento(m_vitality, m_attack, m_defense);
		return memento;
	}

	//载入进度，只与Memento对象交互，并不牵涉到Caretake
	void Load(Memento memento)  
	{
		m_vitality = memento.m_vitality;
		m_attack = memento.m_attack;
		m_defense = memento.m_defense;
	}

	void Show() { cout << "vitality : " << m_vitality << ", attack : " 
		<< m_attack << ", defense : " << m_defense << endl; }

	void Attack() { m_vitality -= 10; m_attack -= 10;  m_defense -= 10; }
};

//保存的进度库
class CareTake
{
public:
	CareTake() {}

	void Save(Memento menento) { m_vecMemento.push_back(menento); }

	Memento Load(int state) { return m_vecMemento[state]; }

private:
	vector<Memento> m_vecMemento;
};


///////////////////////////////////////////////////////
//测试案例
int main()
{
	std::cout<<"行为型模式 之 备忘录模式\n\n";

	CareTake caretake;
	GameRole role;

	role.Show();   //初始值
	caretake.Save(role.Save()); //保存状态

	role.Attack();
	role.Show();  //进攻后
	role.Load(caretake.Load(0)); //载入状态 
	role.Show();  //恢复到状态0
	return 0;
}