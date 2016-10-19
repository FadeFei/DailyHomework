#include "lattice.h"
#include <iostream.h>
#include <vector>
using namespace std;
//构造函数 仅设置编号和值
lattice::lattice() {
	setNo(0);
	setVal(0);
}
lattice::lattice(int a, double b) {
	setNo(a);
	setVal(b);
}

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
int lattice::getVal() {
	return val;
}
void lattice::addParNode(int a) {
	parentList.push_back(a);
}
void lattice::addKidNode(int a) {
	kidList.push_back(a);
}
vector<int> lattice::getParList() {
	return parentList;
}
vector<int> lattice::getKidList() {
	return kidList;
}
void lattice::setFinalVal(double a) {
	finalVal = a;
}
double lattice::getFinalVal() {
	return finalVal;
}