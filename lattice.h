// 定义lattice
#include <vector>
using namespace std;
class lattice
{
public:
	lattice();
	lattice(int a, double b);
	~lattice();

	// 输入为a b，将a和b分别设置为结点的编号和估值
	void setNoAndVal(int a, double b);
	// 设置编号
	void setNo(int a);
	//设置值
	void setVal(double a);
	// 获取编号
	int getNo();
	// 获取值
	double getVal();
	// 增加父母节点
	void addParNode(int a);
	// 增加子女节点
	void addKidNode(int a);
	// 获取父母结点编号数组
	vector<int>& getParList();
	// 获取子节点编号数组
	vector<int>& getKidList();
	//获取和设置最终估值
	void setFinalVal(double a);
	double getFinalVal();
	//获取所有能使最终估值变小的子节点的值之和，并将这些子节点的fanalVal设置为当前结点的val
	//用于贪心算法的每一次的choice的比较
	
	void set2KidChoose() {
		if (if2KidChoose) {
			if2KidChoose = false;
		}
		else {
			if2KidChoose = true;
		}
	}
	//用于标记节点是否已经被选择过了
	void setChoose(bool a) {
		if (a) {
			ifChoose = true;
		} else {
			ifChoose = false;
		}
	}
private:
	// 该结点的编号
	int No;
	// 该结点的值
	double val;
	// 该结点的最终估值
	int finalVal;
	// 该结点的父母节点号
	vector<int> parentList;
	//该结点的子节点号
	vector<int> kidList;
	// 该结点有没有被选中
	bool ifChoose;
	//该结点有没有被当作二级子节点
	bool if2KidChoose;
};
