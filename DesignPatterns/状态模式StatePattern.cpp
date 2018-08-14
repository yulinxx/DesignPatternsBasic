#include <iostream>
using namespace std;

class War;
class State
{
public:
	virtual void Prophase() {}
	virtual void Metaphase() {}
	virtual void Anaphase() {}
	virtual void End() {}
	virtual void CurrentState(War *war) {}
};

// ս��
class War
{
private:
	State *m_state;  //Ŀǰ״̬
	int m_days;      //ս������ʱ��
public:
	War(State *state) : m_state(state), m_days(0) {}
	~War() { delete m_state; }
	int GetDays() { return m_days; }
	void SetDays(int days) { m_days = days; }
	void SetState(State *state) { delete m_state; m_state = state; }
	void GetState() { m_state->CurrentState(this); }
};


// ���������״̬�ࣺ

// ս������
class EndState : public State
{
public:
	void End(War *war) //�����׶εľ�����Ϊ
	{
		cout << "ս������" << endl;
	}
	void CurrentState(War *war) { End(war); }
};

// ����
class AnaphaseState : public State
{
public:
	void Anaphase(War *war) //���ڵľ�����Ϊ
	{
		if (war->GetDays() < 30)
			cout << "��" << war->GetDays() << "�죺ս�����ڣ�˫��ƴ��һ��" << endl;
		else
		{
			war->SetState(new EndState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Anaphase(war); }
};

// ����
class MetaphaseState : public State
{
public:
	void Metaphase(War *war) //���ڵľ�����Ϊ
	{
		if (war->GetDays() < 20)
			cout << "��" << war->GetDays() << 
					"�죺ս�����ڣ�������ֽ׶Σ�˫���������" << endl;
		else
		{
			war->SetState(new AnaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Metaphase(war); }
};

// ǰ��
class ProphaseState : public State
{
public:
	void Prophase(War *war)  //ǰ�ڵľ�����Ϊ
	{
		if (war->GetDays() < 10)
			cout << "��" << war->GetDays() <<
				"�죺ս�����ڣ�˫������������������̽�Է�" << endl;
		else
		{
			war->SetState(new MetaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) { Prophase(war); }
};


// ���԰���
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