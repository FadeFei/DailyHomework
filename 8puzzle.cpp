#include "8puzzle.h"
#include <iostream>
#include <time.h>
#include <iomanip>
#define random(x) (rand()%(x))
using namespace std;

vector<_8puzzle> caseOfPuzzle;
_8puzzle::_8puzzle() {
	deviation = -1;
	steps = 0;
}
_8puzzle::_8puzzle(int *ary) {
	for (int i = 0; i < 9; i++) {
		state[i] = ary[i];
	}
	steps = 0;
	setDev();
}
_8puzzle::_8puzzle(const _8puzzle &p) {
	for (int i = 0; i < 9; i++) {
		state[i] = p.state[i];
	}
	deviation = p.deviation;
	steps = p.steps;
}

int _8puzzle::getDev() {
	if (deviation == -1) {
		setDev();
	}
	return deviation;
}
int _8puzzle::getSteps() {
	return steps;
}

void _8puzzle::setDev() {
	// 不在原位的数码的数量
	int dif = 0;
	for (int i = 0; i < 8; i++) {
		bool ifDif = (state[i] == i + 1);
		if (!ifDif) {
			dif++;
		}
	}
	if (state[8] != 0) {
		dif++;
	}

	// 曼哈顿距离
	int manhatan = 0;
	int x, y;

	for (int i = 0; i < 9; i++) {
		// 0号块不在的位置
		if (state[i]) {
			x = (state[i] - 1) / 3;
			y = (state[i] - 1) % 3;
		}
		else {
			x = y = 2;
		}
		manhatan = manhatan + abs(x - i / 3) + abs(y - i % 3);
	}
	deviation = dif + manhatan;
}

void _8puzzle::setStep(int s) {
	steps = s;
}

vector<_8puzzle> _8puzzle::getSuccessor() {
	vector<_8puzzle> neighbors;
	// 上下左右四个方向
	int dir[] = { -3, 3, -1, 1 };
	int i;
	for (i = 0; i < 9; i++) {
		if (state[i] == 0) {
			// 找到空位
			break;
		}
	}
	for (int j = 0; j < 4; j++) {
		_8puzzle neighbor(*this);
		int index = i + dir[j];
		if (index >= 0 && index < 8 && j < 2) {
			swap(neighbor.state[i], neighbor.state[index]);
			neighbor.setDev();
			neighbor.setStep(this->steps + 1);
			neighbors.push_back(neighbor);
		}
		else if (i % 3 + dir[j] < 3 && i % 3 + dir[j] >= 0 && j >= 2) {
			swap(neighbor.state[i], neighbor.state[index]);
			neighbor.setDev();
			neighbor.setStep(this->steps + 1);
			neighbors.push_back(neighbor);
		}
	}
	return neighbors;
}

void generator(int size) {
	/*srand((int)time(NULL));
	while (size--) {
		int factors[9], temp_size = 9;
		for (int i = 0; i < 9; i++) {
			factors[i] = i;
		}
		int temp_state[9];
		while (temp_size > 1) {
			int select = random(temp_size--);
			temp_state[temp_size] = factors[select];
			factors[select] = factors[temp_size];
		}
		temp_state[0] = factors[0];
		_8puzzle instance(factors);
		instances.push_back(instance);
	}*/
	srand((int)time(NULL));
	while (size--) {
		int factors[9], temp_size = 9;
		for (int i = 0; i < 9; i++) {
			factors[i] = i;
		}
		int temp_state[9];
		while (temp_size > 1) {
			int select = random(temp_size--);
			temp_state[temp_size] = factors[select];
			factors[select] = factors[temp_size];
		}
		temp_state[0] = factors[0];
		_8puzzle instance(temp_state);
		caseOfPuzzle.push_back(instance);
	}
}

int hillClimb(_8puzzle curState) {
	while (1) {
		if (curState.getDev() == 0) {
			return curState.getSteps();
		}
		vector<_8puzzle> neighbors = curState.getSuccessor();
		int index = 0;
		for (int i = 1; i < neighbors.size(); i++) {
			if (neighbors[index].getDev() > neighbors[i].getDev()) {
				index = i;
			}
		}
		_8puzzle next(neighbors[index]);
		if (next.getDev() >= curState.getDev()) {
			return -1;
		}
		curState = next;
	}
	return -1;
}
int firstHillClimb(_8puzzle curState) {
	while (1) {
		if (curState.getDev() == 0) {
			return curState.getSteps();
		}
		vector<_8puzzle> successors = curState.getSuccessor();
		vector<_8puzzle> betterCase;
		for (int i = 1; i < successors.size(); i++) {
			if (successors[i].getDev() < curState.getDev()) {
				betterCase.push_back(successors[i]);
			}
		}
		if (betterCase.size() == 0) {
			return -1;
		}
		int index = rand() % betterCase.size();
		curState = betterCase[index];
	}
	return -1;
}

int randRestartHillClimb(_8puzzle curState) {
	int times = 0;
	while (1) {
		int index = 0;
		if (curState.getDev() == 0) {
			return curState.getSteps();
		}

		vector<_8puzzle> successors = curState.getSuccessor();
		for (int i = 0; i < successors.size(); i++) {
			if (successors[index].getDev() > successors[i].getDev()) {
				index = i;
			}
		}
		if (successors[index].getDev() >= curState.getDev()) {
			int factors[9], temp_size = 9;
			for (int i = 0; i < 9; i++) {
				factors[i] = i;
			}
			int temp_puzzle[9];
			while (temp_size > 1) {
				int select = random(temp_size--);
				temp_puzzle[temp_size] = factors[select];
				factors[select] = factors[temp_size];
			}
			temp_puzzle[0] = factors[0];
			_8puzzle instance(temp_puzzle);
			curState = temp_puzzle;
			times++;
			//cout << "THIS IS THE TIMES OF" << times << "RESTART" << endl;
		}
		else {
			curState = successors[index];
		}
	}
}

int simAnealing(_8puzzle curState) {
	double maxT = 300, minT = 0.0001;
	double lower = 0.99;
	int times = 0;
	while (maxT > minT) {
		if (curState.getDev() == 0) {
			return curState.getSteps();
		}
		vector<_8puzzle> neighbors = curState.getSuccessor();
		_8puzzle next = neighbors[rand() % neighbors.size()];

		int deltaE = next.getDev() - curState.getDev();
		if (deltaE < 0) {
			curState = next;
		}
		else if (pow(2.71828, 0 - deltaE / maxT) > (double)(rand() % 100) / 100.0) {
			curState = next;
		}
		maxT *= lower;
		times++;
	}
	return -1;
}
void _8puzzle::getState() {
	for (int i = 0; i < 9; i++) {
		cout << state[i] << " ";
	}
	cout << endl;
}
int main() {
	int cases = 10000;
	srand((unsigned)time(NULL));
	generator(cases);
	int times = 0;
	for (int j = 0; j < 10; j++) {
		int succedCase[4] = { 0 };
		int sumOfSteps[4] = { 0 };
		int step[4];
		times++;
		cout << "第" << times << "次测试" << endl;
		for (int i = 0; i < cases / 10; i++) {
			step[0] = simAnealing(caseOfPuzzle[i]);
			if (step[0] != -1) {
				sumOfSteps[0] += step[0];
				succedCase[0]++;
			}
		}
		cout << "模拟退火法        总测试数: " << cases / 100 << setw(15) << "总步数:" << sumOfSteps[0] << setw(15)
			<< "成功次数:" << succedCase[0] << setw(10) << "成功概率为：" << ((double)succedCase[0] / (double)(cases / 100) * 100.0) << "%" << endl;

		for (int i = 0; i < cases; i++) {
			step[1] = hillClimb(caseOfPuzzle[i]);
			if (step[1] != -1) {
				sumOfSteps[1] += step[1];
				succedCase[1]++;
			}
		}
		cout << "最陡上升爬山法    总测试数: " << cases << setw(15) << "总步数:" << sumOfSteps[1] << setw(15)
			<< "成功次数:" << succedCase[1] << setw(10) << "成功概率为：" << ((double)succedCase[1] / (double)cases * 100.0) << "%" << endl;

		for (int i = 0; i < cases; i++) {
			step[2] = firstHillClimb(caseOfPuzzle[i]);
			if (step[2] != -1) {
				sumOfSteps[2] += step[2];
				succedCase[2]++;
			}
		}
		cout << "首选爬山法 　　   总测试数: " << cases << setw(15) << "总步数:" << sumOfSteps[2] << setw(15)
			<< "成功次数:" << succedCase[2] << setw(10) << "成功概率为：" << ((double)succedCase[2] / (double)cases * 100.0) << "%" << endl;

		for (int i = 0; i < cases / 100; i++) {
			step[3] = randRestartHillClimb(caseOfPuzzle[i]);
			if (step[3] != -1) {
				sumOfSteps[3] += step[3];
				succedCase[3]++;
			}
		}
		cout << "随机重启爬山法    总测试数: " << cases / 100 << setw(15) << "总步数:" << sumOfSteps[3] << setw(15)
			<< "成功次数:" << succedCase[3] << setw(10) << "成功概率为：" << ((double)succedCase[3] / (double)(cases / 100) * 100.0) << "%" << endl
			<< endl;
	}
	system("pause");
}