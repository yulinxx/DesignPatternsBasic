#include <iostream>
using namespace std;

class War;

class State
{
public:
	virtual void Prophase() {}	// 前期
	virtual void Metaphase() {}	// 中期
	virtual void Anaphase() {}	// 后期
	virtual void End() {}			// 结束
	virtual void CurrentState(War *war) {} // 当前状态
};

// 战争
class War
{
private:
	State *m_pState;  //目前状态
	int m_nDays;      //战争持续时间

public:
	War(State *state) : m_pState(state), m_nDays(0) {}
	~War() { delete m_pState; }

	int GetDays() { return m_nDays; }
	void SetDays(int days) { m_nDays = days; }
	void SetState(State *state) { delete m_pState; m_pState = state; }
	void GetState() { m_pState->CurrentState(this); }
};


// 给出具体的状态类：

// 战争结束
class EndState : public State
{
public:
	void End(War *war) //结束阶段的具体行为
	{
		cout << "战争结束" << endl;
	}
	void CurrentState(War *war) { End(war); }
};

// 后期
class AnaphaseState : public State
{
public:
	void Anaphase(War *war) //后期的具体行为
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

// 中期
class MetaphaseState : public State
{
public:
	void Metaphase(War *war) //中期的具体行为
	{
		if (war->GetDays() < 20)
			cout << "第" << war->GetDays() << 
					"天：战争中期，进入相持阶段，双发各有损耗" << endl;
		else
		{
			war->SetState(new AnaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Metaphase(war); }
};

// 前期
class ProphaseState : public State
{
public:
	void Prophase(War *war)  //前期的具体行为
	{
		if (war->GetDays() < 10)
			cout << "第" << war->GetDays() <<
				"天：战争初期，双方你来我往，互相试探对方" << endl;
		else
		{
			war->SetState(new MetaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Prophase(war); }
};


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