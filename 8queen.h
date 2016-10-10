#define _8QUEEN
#include <vector>
using namespace std;
class _8queen {
public:
	_8queen();
	_8queen(int *);
	_8queen(const _8queen &);

	//获得当前互相可攻击到的个数
	int getNumOfConflict();
	// 获得当前移动的步数
	int getSteps();
	// 计算互相可攻击到的个数
	void calNumOfConflict();
	// 设置步数
	void setSteps(int);
	// 设置（改变）index处的状态，value取0-7
	void setState(int index, int value);
	// 获得任意一个皇后移动一步之后的状态（在当前列移动）
	vector<_8queen> getSuccessors();
	// 检查两个状态是否相同
	bool sameState(_8queen &);
private:
	// 八列棋盘的皇后所在行数
	int state[8];
	// 互相可攻击到的个数
	int numOfConflict;
	int steps;
};
#ifndef _8QUEEN
#endif