#define _8QUEEN
#include <vector>
using namespace std;
class _8queen {
public:
	_8queen();
	_8queen(int *);
	_8queen(const _8queen &);

	//��õ�ǰ����ɹ������ĸ���
	int getNumOfConflict();
	// ��õ�ǰ�ƶ��Ĳ���
	int getSteps();
	// ���㻥��ɹ������ĸ���
	void calNumOfConflict();
	// ���ò���
	void setSteps(int);
	// ���ã��ı䣩index����״̬��valueȡ0-7
	void setState(int index, int value);
	// �������һ���ʺ��ƶ�һ��֮���״̬���ڵ�ǰ���ƶ���
	vector<_8queen> getSuccessors();
	// �������״̬�Ƿ���ͬ
	bool sameState(_8queen &);
private:
	// �������̵Ļʺ���������
	int state[8];
	// ����ɹ������ĸ���
	int numOfConflict;
	int steps;
};
#ifndef _8QUEEN
#endif