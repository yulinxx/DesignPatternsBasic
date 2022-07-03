// 状态模式(state pattern)

// 状态模式：允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类。
// 它有两种使用情况：
// （1）一个对象的行为取决于它的状态, 并且它必须在运行时刻根据状态改变它的行为。
// （2）一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态。
// 本文的例子为第一种情况，以战争为例，假设一场战争需经历四个阶段：前期、中期、后期、结束。
// 当战争处于不同的阶段，战争的行为是不一样的，也就说战争的行为取决于所处的阶段，而且随着时间的推进是动态变化的。
// https://blog.csdn.net/pomelozero/article/details/76713677

#include <iostream>
using namespace std;

class War;

///////////////////////////////////////////////////
class State
{
public:
	virtual void Prophase() {}			   // 前期
	virtual void Metaphase() {}			   // 中期
	virtual void Anaphase() {}			   // 后期
	virtual void End() {}				   // 结束
	virtual void CurrentState(War *war) {} // 当前状态
};

///////////////////////////////////////////////////
// 战争
class War
{
public:
	War(State *state) : m_pState(state), m_nDays(0) {}
	~War() { delete m_pState; }

	int GetDays() { return m_nDays; }
	void SetDays(int days) { m_nDays = days; }
	void SetState(State *state)
	{
		delete m_pState;
		m_pState = state;
	}
	void GetState() { m_pState->CurrentState(this); }

private:
	State *m_pState = nullptr; // 目前状态
	int m_nDays;			   // 战争持续时间
};

// 给出具体的状态类：

///////////////////////////////////////////////////
// 战争结束
class EndState : public State
{
public:
	void End(War *war) // 结束阶段的具体行为
	{
		cout << "战争结束" << endl;
	}
	void CurrentState(War *war) { End(war); }
};

/////////////////////////////////////
// 后期
class AnaphaseState : public State
{
public:
	void Anaphase(War *war) // 后期的具体行为
	{
		if (war->GetDays() < 30)
			cout << "第" << war->GetDays() << "天：战争后期，双方拼死一搏" << endl;
		else
		{
			war->SetState(new EndState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Anaphase(war); }
};

///////////////////////////////////////////////////
// 中期
class MetaphaseState : public State
{
public:
	void Metaphase(War *war) // 中期的具体行为
	{
		if (war->GetDays() < 20)
			cout << "第" << war->GetDays() << "天：战争中期，进入相持阶段，双发各有损耗" << endl;
		else
		{
			war->SetState(new AnaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Metaphase(war); }
};

///////////////////////////////////////////////////
// 前期
class ProphaseState : public State
{
public:
	void Prophase(War *war) // 前期的具体行为
	{
		if (war->GetDays() < 10)
			cout << "第" << war->GetDays() << "天：战争初期，双方你来我往，互相试探对方" << endl;
		else
		{
			war->SetState(new MetaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Prophase(war); }
};

///////////////////////////////////////////////////
// 测试案例
int main()
{
	War *pWar = new War(new ProphaseState());
	for (int i = 1; i < 40; i += 5)
	{
		pWar->SetDays(i);
		pWar->GetState();
	}
	delete pWar;
	return 0;
}
