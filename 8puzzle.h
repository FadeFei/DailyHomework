#define _8PUZZLE

#include <vector>
#include <set>
using namespace std;

class _8puzzle {
public:
	_8puzzle();
	_8puzzle(int * _array);
	_8puzzle(const _8puzzle & p);
	int getDev();
	int getSteps();
	void getState();
	void setStep(int _step);
	void setDev();
	vector<_8puzzle> getSuccessor();

private:
	// ���9������λ���������һ����λ����������ֿ飨���һ�鵱��0��
	int state[9];
	int steps;
	// ���ƫ��������ÿ�������뻹ԭλ��ƫ������
	int deviation;
};