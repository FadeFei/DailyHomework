﻿/*----------------------------------------------------------------
// 版权所有。
//
// 文件名：lattice.cpp
// 文件功能描述：算法第一次大作业
// author：group_1, FeiGu, （小组成员自行添加）
// 时间：2016-10-20 15:30:37
// 创建标识：version_1
//
// 修改标识：（请在修改后注明第几次修改）
//
// 修改描述：（请在修改后注明修改部分）
//----------------------------------------------------------------*/





#include "lattice.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdio>
using namespace std;

int n, k;
vector<lattice> nodeSet;

string my_itoa(int n) {
	int i, temp, len = 0;
	int a[1000] = {0};
	char c[1000] = {0};
	string s;
	temp = n;
	while (temp / 10 != 0) {
		a[len] = temp % 10;
		temp = temp / 10;
		len++;
	}
	if (temp != 0) {
		a[len] = temp;
		len++;
	}
	for (i = 0; i < len / 2; i++) {
		temp = a[i];
		a[i] = a[len - i - 1];
		a[len - i - 1] = temp;
	}
	for (i = 0; i < len; i++) {
		c[i] = a[i] + 48;
		s += c[i];
	}
	return s;
} 


//构造函数 仅设置编号和值
lattice::lattice() {
	setNo(0);
	setVal(0);
	setFinalVal(0);
	//setChoose(false);
}
lattice::lattice(int a, double b) {
	setNo(a);
	setVal(b);
	setFinalVal(b);
	//setChoose(false);
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


void calculateVal(int k) {
	//进行K轮的操作
	bool ifParentChoose[100] = { false };
	//储存最终结果
	vector<int> finalResult;
	time_t startTime, endTime;

	/*time(&startTime);*/
	for (int round = 0; round < k; round++) {
		//每轮对所有未选中的结点进行计算其选中后的收益
		//得到当前令收益最大的那个点

		//记录收益值最大（即选了它之后节省的值最多）的节点编号
		int currentMaxNo;
		int tempParentNo;
		//记录最大收益值
		int currentMaxVal = 0;
		int tempMaxVal;


		for (int parentNo = 1; parentNo < n; parentNo++) {
			cout << "=======================================================================" << endl;
			cout << "第" << round + 1 << "轮，第" << nodeSet[parentNo].getNo() << "个节点的收益测试" << endl;
			if (ifParentChoose[parentNo] != true ) {
				//记录收益值最大（即选了它之后节省的值最多）的节点编号
				tempParentNo = parentNo;
				//记录最大收益值
				//获得当前节点的val
				int tempParentVal = nodeSet[parentNo].getVal();
				int tempParentFinalVal = nodeSet[parentNo].getFinalVal();
				if (tempParentFinalVal > tempParentVal) {
					tempMaxVal = tempParentFinalVal - tempParentVal;
				}
				else {
					tempMaxVal = tempParentVal - tempParentFinalVal;
				}
				//tempMaxVal = nodeSet[parentNo].getFinalVal() - tempParentVal;

				vector<int> tempKidList = nodeSet[parentNo].getKidList();

				int tempKidListSize = tempKidList.size();
					for (int i = 0; i < tempKidListSize; i++) {
						//这里的kidNo不应该是类中的No，而应该减一，或者我把类中的编号从0开始
						int tempKidNo = tempKidList[i] - 1;
						//获得当前子节点的finalVal
						int tempKidFinalVal = nodeSet[tempKidNo].getFinalVal();

						if (tempKidFinalVal > tempParentVal) {
							tempMaxVal += (tempKidFinalVal - tempParentVal);
						}
					}
					cout << "第" << round + 1 << "轮的第" << nodeSet[tempParentNo].getNo() << "号结点的总收益为" << tempMaxVal << endl;
				if (tempMaxVal > currentMaxVal) {
					currentMaxVal = tempMaxVal;
					currentMaxNo = tempParentNo;
				}
			}
		}



		//把最大收益结点压进数组里
		int tempNo = nodeSet[currentMaxNo].getNo();
		finalResult.push_back(tempNo);
		cout << "第" << round + 1 << "轮的" << "最大收益结点为" << nodeSet[currentMaxNo].getNo() << endl;
		nodeSet[currentMaxNo].setFinalVal(nodeSet[currentMaxNo].getVal());
		ifParentChoose[currentMaxNo] = true;
		//对最后选出来的那个节点，把它的子节的finalVal设置为它的finalVal
		vector<int> tempKidList = nodeSet[currentMaxNo].getKidList();
		nodeSet[currentMaxNo].setFinalVal(nodeSet[currentMaxNo].getVal());
		for (int kidNo = 0; kidNo < tempKidList.size(); kidNo++) {
			//这里的kidNo不应该是类中的No，而应该减一，或者我把类中的编号从0开始
			int tempKidNo = tempKidList[kidNo] - 1;

			if (nodeSet[currentMaxNo].getFinalVal() < nodeSet[tempKidNo].getFinalVal()) {
				nodeSet[tempKidNo].setFinalVal(nodeSet[currentMaxNo].getFinalVal());
			}
		}
		//for (int i = 0; i < n; i++) {
		//	cout << nodeSet[i].getNo() << "号节点当前最终估值为" << nodeSet[i].getFinalVal() << endl;
		//		/*<< "子节点编号为" << endl;*/
		//	/*vector<int> tempKidList = nodeSet[i].getKidList();
		//	for (int i = 0; i < tempKidList.size(); i++) {
		//		cout << tempKidList[i] << " ";
		//	}*/
		//	cout << endl;
		//}
	}
	/*time(&endTime);
	cout << "计算所用时间";
	printf("%ld\n", endTime - startTime);*/

	cout << "结果路径为：" << "1→";
	for (int i = 0; i < finalResult.size(); i++) {
		if (i < finalResult.size() - 1) {
			cout << finalResult[i] << "→";
		}
		else {
			cout << finalResult[i] << endl;
		}
	}
}

// 程序主函数
int main() {
		
	// 焦轩修改部分
	char buf[1024];
	FILE *fp = NULL;
	int len;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		perror("fail to read");
		exit(1);
	} 
	fscanf(fp, "%d", &n);
	fscanf(fp, "%d", &k);
	fscanf(fp, "\n");



	/*==============================分割线===========================================*/

	// cout << "testing" << endl;
	
	// cout << "输入结点数量和k的数量" << endl;
	// cin >> n >> k;
	// //输入多个结点，给其编号并赋值
	// cout << "输入节点编号和值" << endl;
	for (int i = 0; i < n; i++) {
		int num, val;
	//焦轩修改部分
		fscanf(fp, "%d", &num);
		fscanf(fp, "%d", &val);
		fscanf(fp, "\n");
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
	// int numOfBorder;
	// cout << "输入边的数量" << endl;
	// cin >> numOfBorder;
	// cout << "输入父节点、子节点编号" << endl;


	//焦轩修改部分
	fscanf(fp, "%d", &numOfBorder);
	fscanf(fp, "\n");

	for (int i = 0; i < numOfBorder; i++) {
		int parentNum, kidNum;

		//焦轩修改部分
		fscanf(fp, "%d", &parentNum);
		fscanf(fp, "%d", &kidNum);
		fscanf(fp, "\n");
		nodeSet[parentNum - 1].addKidNode(kidNum);
	}

	//输入边之后，对所有结点的子节点进行计算，因为算法定义子节点除了直接连着的外，子节点的子节点也是该结点的子节点
	for (int parentNo = n; parentNo > 1; parentNo--) {
		//用于获取二级子节点的时候判重
		int ifKidChoose[100] = { 0 };
		//获得与当前结点直接相连的子节点编号
		vector<int> _1KidList = nodeSet[parentNo - 1].getKidList();
		//第一层循环，遍历所有第一级子节点
		if (_1KidList.size() != 0) {
			for (int i = 0; i < _1KidList.size(); i++) {
				//_1KidList中子节点的实际编号
				int _1KidNo = _1KidList[i];
				vector<int> _2KidList = nodeSet[_1KidNo-1].getKidList();
				//第二层循环，遍历所有第二级子节点
				if (_2KidList.size() != 0) {
					for (int j = 0; j < _2KidList.size(); j++) {
						int _2KidNo = _2KidList[j];
						if (ifKidChoose[_2KidNo] != 1) {
							//cout << "将" << _2KidNo << "号二级子节点加入结点" << nodeSet[parentNo - 1].getNo() << "中" << endl;
							nodeSet[parentNo - 1].addKidNode(_2KidNo);
							ifKidChoose[_2KidNo] = 1;
						}
					}
				}
				else {
					continue;
				}
			}
		}
		else {
			continue;
		}
	}
	//进行K轮操作
	calculateVal(k);

	//system("pause");
}




