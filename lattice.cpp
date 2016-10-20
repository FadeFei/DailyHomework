#include "lattice.h"
#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<lattice> nodeSet;

//构造函数 仅设置编号和值
lattice::lattice() {
	setNo(0);
	setVal(0);
}
lattice::lattice(int a, double b) {
	setNo(a);
	setVal(b);
}
lattice::~lattice() {}

void lattice::setNoAndVal(int a, double b) {
	setNo(a);
	setVal(b);
}

void lattice::setNo(int a) {
	No = a;
}
void lattice::setVal(double a) {
	val = a;
}
int lattice::getNo() {
	return No;
}
double lattice::getVal() {
	return val;
}
void lattice::addParNode(int a) {
	parentList.push_back(a);
}
void lattice::addKidNode(int a) {
	kidList.push_back(a);
}
vector<int>& lattice::getParList() {
	return parentList;
}
vector<int>& lattice::getKidList() {
	return kidList;
}
void lattice::setFinalVal(double a) {
	finalVal = a;
}
double lattice::getFinalVal() {
	return finalVal;
}

// 程序主函数
int main() {
	cout << "testing" << endl;
	
	cout << "输入结点数量和k的数量" << endl;
	cin >> n >> k;
	//输入多个结点，给其编号并赋值
	cout << "输入节点编号和值" << endl;
	for (int i = 0; i < n; i++) {
		int num, val;
		cin >> num >> val;
		lattice tempNode;
		tempNode.setNo(num);
		tempNode.setVal(val);
		if (i > 0) {
			tempNode.setFinalVal(nodeSet[0].getFinalVal());
		}
		else
		{
			tempNode.setFinalVal(val);
		}
		nodeSet.push_back(tempNode);
	}
	//输入多条边，确定父子节点
	int numOfBorder;
	cout << "输入边的数量" << endl;
	cin >> numOfBorder;
	for (int i = 0; i < numOfBorder; i++) {
		int parentNum, kidNum;
		cout << "输入父节点、子节点编号" << endl;
		cin >> parentNum >> kidNum;
		nodeSet[parentNum - 1].addKidNode(kidNum);
	}
	//输入边之后，对所有结点的子节点进行计算，因为算法定义子节点除了直接连着的外，子节点的子节点也是该结点的子节点
	for (int parentNo = n; parentNo > 1; parentNo--) {
		//获得与当前结点直接相连的子节点编号
		vector<int> _1KidList = nodeSet[parentNo - 1].getKidList();
		//第一层循环，遍历所有第一级子节点
		if (_1KidList.size() != 0) {
			for (int i = 0; i < _1KidList.size(); i++) {
				int _1KidNo = _1KidList[i] - 1;
				vector<int> _2KidList = nodeSet[_1KidNo].getKidList();
				//第二层循环，遍历所有第二级子节点
				if (_2KidList.size() != 0) {
					for (int j = 0; j < _2KidList.size(); j++) {
						int _2KidNo = _2KidList[j];
						nodeSet[parentNo].addKidNode(_2KidNo);
					}
				}
			}
		}
	}
	//输出所有结点的所有子节点
	for (int parentNo = 0; parentNo < n; parentNo++) {
		vector<int> tempKidList = nodeSet[parentNo].getKidList();
		int kidSize = tempKidList.size();
		cout << "第" << n + 1 << "个节点的所有子节点编号为： ";
		for (int i = 0; i < kidSize; i++) {
			cout << tempKidList[i] << " ";
		}
		cout << endl;
	}
	//进行K轮的操作
	for (int round = 0; round < k; round++) {
		//每轮对所有未选中的结点进行计算其选中后的收益
		//得到当前令收益最大的那个点

		//记录收益值最大（即选了它之后节省的值最多）的节点编号
		int currentMaxNo = 1;
		int tempParentNo;
		//记录最大收益值
		int currentMaxVal = 0;
		int tempMaxVal;
		for (int parentNo = 1; parentNo < n; parentNo++) {
			//记录收益值最大（即选了它之后节省的值最多）的节点编号
			tempParentNo = parentNo;
			//记录最大收益值
			tempMaxVal = 0;
			vector<int> tempKidList = nodeSet[parentNo].getKidList();
			//KidNo是对于当前的父节点而言的第几个子节点
			cout << "当前第" << parentNo << "个节点的子节点数量为" << tempKidList.size() << endl;
			int tempKidListSize = tempKidList.size();
			for (int kidNo = 0; kidNo < tempKidListSize; kidNo++) {
				//这里的kidNo不应该是类中的No，而应该减一，或者我把类中的编号从0开始
				int tempKidNo = tempKidList[kidNo]-1;
				//获得当前子节点的finalVal
				int tempKidFinalVal = nodeSet[tempKidNo].getFinalVal();
				//获得当前节点的val
				int tempParentVal = nodeSet[parentNo].getVal();
				if (tempKidFinalVal > tempParentVal) {
					tempMaxVal += (tempKidFinalVal - tempParentVal);
				}
			}
			if (tempMaxVal > currentMaxVal) {
				currentMaxVal = tempMaxVal;
				currentMaxNo = tempParentNo;
			}
		}
		cout << "最大收益结点为" << currentMaxNo << endl;
		nodeSet[currentMaxNo].setFinalVal(nodeSet[currentMaxNo].getVal());
		nodeSet[currentMaxNo].setChoose(true);
		//对最后选出来的那个节点，把它的子节的finalVal设置为它的finalVal
		vector<int> tempKidList = nodeSet[currentMaxNo].getKidList();
		for (int kidNo = 0; kidNo < tempKidList.size(); kidNo++) {
			//这里的kidNo不应该是类中的No，而应该减一，或者我把类中的编号从0开始
			int tempKidNo = tempKidList[kidNo] - 1;
			nodeSet[tempKidNo].setFinalVal(nodeSet[currentMaxNo].getVal());
		}
		for (int i = 0; i < n; i++) {
			cout << nodeSet[i].getNo() << "号节点估值为  " << nodeSet[i].getVal()
				<< "当前最终估值为" << nodeSet[i].getFinalVal()
				<< "子节点编号为" << endl;
			vector<int> tempKidList = nodeSet[i].getKidList();
			for (int i = 0; i < tempKidList.size(); i++) {
				cout << tempKidList[i] << " ";
			}
			cout << endl;
		}
	}

	/*for (int i = 0; i < n; i++) {
		cout << nodeSet[i].getNo() << "号节点估值为  " << nodeSet[i].getVal() 
			<< "当前最终估值为" << nodeSet[i].getFinalVal()
			<< "子节点编号为" << endl;
		vector<int> tempKidList = nodeSet[i].getKidList();
		for (int i = 0; i < tempKidList.size(); i++) {
			cout << tempKidList[i] << " ";
		}
		cout << endl;
	}*/
	system("pause");
}

//获取所有能使最终估值变小的子节点的值之和，并将这些子节点的fanalVal设置为当前结点的val
//用于贪心算法的每一次的choice的比较
double getMax() {
	return 0;
}

