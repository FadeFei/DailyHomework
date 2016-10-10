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
	// 存放9个数码位（八数码加一个空位）所存的数字块（最后一块当作0）
	int state[9];
	int steps;
	// 存放偏移量（即每个数码离还原位的偏移量）
	int deviation;
};