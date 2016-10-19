// 定义lattice
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
	int* getParList();
	// 获取子节点编号数组
	int* getKidList();
	//获取和设置最终估值
	void setFinalVal(double a);
	double getFinalVal();
	//获取所有能使最终估值变小的子节点的值之和
	int getMax() {
		vector<int> tempKidList = new vector<int>;
		tempKidList = getKidList;
		int kidNum = 0;
		double tempFinalVal = getVal();
		for (int i = 0; i < tempKidList.length(); i++) {
			if (tempKidList[i].getFinalVal() > tempFinalVal) {
				kidNum++;
			}
		}
		return (double)kidNum*tempFinalVal;
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
};