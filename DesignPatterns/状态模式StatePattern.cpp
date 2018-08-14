#include <iostream>
using namespace std;

class War;

class State
{
public:
	virtual void Prophase() {}	// ǰ��
	virtual void Metaphase() {}	// ����
	virtual void Anaphase() {}	// ����
	virtual void End() {}			// ����
	virtual void CurrentState(War *war) {} // ��ǰ״̬
};

// ս��
class War
{
private:
	State *m_pState;  //Ŀǰ״̬
	int m_nDays;      //ս������ʱ��

public:
	War(State *state) : m_pState(state), m_nDays(0) {}
	~War() { delete m_pState; }

	int GetDays() { return m_nDays; }
	void SetDays(int days) { m_nDays = days; }
	void SetState(State *state) { delete m_pState; m_pState = state; }
	void GetState() { m_pState->CurrentState(this); }
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