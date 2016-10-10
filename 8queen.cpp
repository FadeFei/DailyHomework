#include "8queen.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

vector<_8queen> caseOfQueen;
void generator(int);
double randDouble();
int hillClimb(_8queen);
int firstHillClimb(_8queen);
int randRestartHillClimb(_8queen);
int simAnnealing(_8queen);

_8queen::_8queen() {
	steps = 0;
	numOfConflict = -1;
}

_8queen::_8queen(int *temp_state) {
	for (int i = 0; i < 8; i++) {
		state[i] = temp_state[i];
	}
	steps = 0;
	numOfConflict = -1;
}

_8queen::_8queen(const _8queen & temp_queen) {
	for (int i = 0; i < 9; i++) {
		state[i] = temp_queen.state[i];
	}
	numOfConflict = temp_queen.numOfConflict;
	steps = temp_queen.steps;
}

int _8queen::getNumOfConflict() {
	return numOfConflict;
}
int _8queen::getSteps() {
	return steps;
}

void _8queen::calNumOfConflict() {
	numOfConflict = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = i + 1; j < 8; j++) {
			bool sameRow = (state[i] == state[j]);
			bool sameSlash = (j - i == abs(state[j] - state[i]));
			if (sameRow || sameSlash) {
				numOfConflict++;
			}
		}
	}
}

void _8queen::setSteps(int temp_steps) {
	steps = temp_steps;
}

void _8queen::setState(int index, int temp_state) {
	state[index] = temp_state;
}

vector<_8queen> _8queen::getSuccessors() {
	vector<_8queen> successors;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bool sameState = (state[i] == state[j]);
			if (!sameState) {
				_8queen successorState(state);
				// 移动一步（每列一共七个位置可以移动）
				successorState.setState(i, j);
				successorState.calNumOfConflict();
				successorState.setSteps(this->steps + 1);
				successors.push_back(successorState);
			}
		}
	}
	return successors;
}

bool _8queen::sameState(_8queen & temp_queen) {
	for (int i = 0; i < 8; i++) {
		bool same = (state[i] == temp_queen.state[i]);
		if (!same) {
			return false;
		}
	}
	return true;
}


void generator(int caseSize) {
	for (int i = 0; i < caseSize; i++) {
		int temp_state[8];
		for (int j = 0; j < 8; j++) {
			temp_state[j] = rand() % 8;
		}
		_8queen temp_queen(temp_state);
		temp_queen.calNumOfConflict();
		caseOfQueen.push_back(temp_queen);
	}
	return;
}


int hillClimb(_8queen curState) {
	while (1) {
		int index = 0;
		if (curState.getNumOfConflict() == 0) {
			return curState.getSteps();
		}
		vector<_8queen> successors = curState.getSuccessors();
 		for (int i = 0; i < successors.size(); i++) {
			if (successors[index].getNumOfConflict() > successors[i].getNumOfConflict()) {
				index = i;
			}
		}
		if (successors[index].getNumOfConflict() >= curState.getNumOfConflict()) {
			return -1;
		}
		curState = successors[index];
	}
	return -1;
}

int firstHillClimb(_8queen curState) {
	while (1) {
		vector<_8queen> betterCase;
		vector<_8queen> successors = curState.getSuccessors();
		if (curState.getNumOfConflict() == 0) {
			return curState.getSteps();
		}
		for (int i = 0; i < successors.size(); i++) {
			if (successors[i].getNumOfConflict() < curState.getNumOfConflict()) {
				betterCase.push_back(successors[i]);
			}
		}
		if (betterCase.size() == 0)
			return -1;
		int i = rand() % betterCase.size();
		curState = betterCase[i];
	}
	return -1;
}
int randRestartHillClimb(_8queen curState) {
	while (1) {
		int index = 0;
		if (curState.getNumOfConflict() == 0) {
			return curState.getSteps();
		}
		vector<_8queen> successors = curState.getSuccessors();
		for (int i = 0; i < successors.size(); i++) {
			if (successors[index].getNumOfConflict() > successors[i].getNumOfConflict()) {
				index = i;
			}
		}
		if (successors[index].getNumOfConflict() >= curState.getNumOfConflict()) {
			int temp_state[8];
			for (int j = 0; j < 8; j++) {
				temp_state[j] = rand() % 8;
			}
			_8queen temp_queen(temp_state);
			temp_queen.calNumOfConflict();
			curState = temp_queen;
		} else {
			curState = successors[index];
		}
	}
}

int simAnnealing(_8queen curState) {
	double maxT = 300, minT = 0.00001;
	double lower = 0.9999;
	while (1) {
		int index = 0;
		if (curState.getNumOfConflict() == 0) {
			return curState.getSteps();
		}
		_8queen next(curState);
		next.setSteps(curState.getSteps());
		while (next.sameState(curState)){
			next.setState(rand() % 8, rand() % 8);
			next.setSteps(next.getSteps() + 1);
		}
		next.calNumOfConflict();

		int deltaE = next.getNumOfConflict() - curState.getNumOfConflict();
		if (deltaE < 0) {
			curState = next;
		}
		else if (pow(2.71828, 0 - deltaE / maxT) > (double)(rand()%100)/100.0) {
			curState = next;
		}
		maxT *= lower;
	}
}

int main() {
	int cases = 1000;
	srand((unsigned)time(NULL));
	generator(cases);
	int times = 0;
	for (int j = 0; j < 10; j++) {
		int succedCase[4] = { 0 };
		int sumOfSteps[4] = { 0 };
		int step[4];
		times++;
		cout << "第" << times << "次测试" << endl;
		for (int i = 0; i < cases/10; i++) {
			step[0] = simAnnealing(caseOfQueen[i]);
			if (step[0] != -1) {
				sumOfSteps[0] += step[0];
				succedCase[0]++;
			}
		}
		cout << "模拟退火法        总测试数: " << cases/10 << setw(15) << "总步数:" << sumOfSteps[0]  << setw(15) 
			<< "成功次数:" << succedCase[0] << setw(10) << "成功概率为：" << ((double)succedCase[0] / (double)(cases/10) * 100.0) << "%" << endl;

		for (int i = 0; i < cases; i++) {
			step[1] = hillClimb(caseOfQueen[i]);
			if (step[1] != -1) {
				sumOfSteps[1] += step[1];
				succedCase[1]++;
			}
		}
		cout << "最陡上升爬山法    总测试数: " << cases << setw(15) << "总步数:" << sumOfSteps[1] << setw(15)
			<< "成功次数:" << succedCase[1] << setw(10) << "成功概率为：" << ((double)succedCase[1] / (double)cases * 100.0) << "%" << endl;

		for (int i = 0; i < cases; i++) {
			step[2] = firstHillClimb(caseOfQueen[i]);
			if (step[2] != -1) {
				sumOfSteps[2] += step[2];
				succedCase[2]++;
			}
		}
		cout << "首选爬山法 　　   总测试数: " << cases << setw(15) << "总步数:" << sumOfSteps[2] << setw(15)
			<< "成功次数:" << succedCase[2] << setw(10) << "成功概率为：" << ((double)succedCase[2] / (double)cases * 100.0) << "%" << endl;

		for (int i = 0; i < cases/10; i++) {
			step[3] = randRestartHillClimb(caseOfQueen[i]);
			if (step[3] != -1) {
				sumOfSteps[3] += step[3];
				succedCase[3]++;
			}
		}
		cout << "随机重启爬山法    总测试数: " << cases / 10 << setw(15) << "总步数:" << sumOfSteps[3] << setw(15)
			<< "成功次数:" << succedCase[3] << setw(10) << "成功概率为：" << ((double)succedCase[3] / (double)(cases / 10) * 100.0) << "%" << endl
			<< endl;
	}
	system("pause");
}