/*此部分是为获得文档中：Algorithm1：Indexing
						Input：the number of random projections m*/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <float.h>
#include "definition.h"
#include "MergeSort.h"
#include "RandomOfGaussianDistribution.h"


/*获得服从高斯分布的随机数
参考维基百科：https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform#Implementation
再根据百度百科Box-Muller做了简化*/
//float GaussianDistribution()
float normal_distribution() {
	double u1, u2;
	u1 = rand()*(1.0 / RAND_MAX);
	u2 = rand()*(1.0 / RAND_MAX);
	double z0, z1;
	double pi = 3.14159265358979323846;

	//以下两个表达式选其一即可
	z0 = sqrt(-2 * log(u1))*cos(2 * pi*u2);
	//z1 = sqrt(-2 * log(u1))*sin(2 * pi*u2);
	return z0;
}

//用于生成随机向量
//vector* RandomOfVector()
VECTORLIST randomVector() {

	/*向量列表用于存放随机向量（随机数服从高斯分布）
	根据文档：We limit the number of random projections m = 50*/
	vector* ListOfVector = new vector[50];


	/*参考文档：‖𝑜−𝑞‖=√(∑(𝑖=1 i=𝑑) (𝑜_𝑖−𝑞_𝑖 )^2 )
	生成向量的值*/
	for (int i = 0; i < 50; i++) {
		double mod = 0;
		/*参考文档：the dimensionality of the data objects is d = 784
		利用高斯分布函数生成向量的值*/
		for (int j = 0; j < 784; j++) {
			ListOfVector[i].data[j] = normal_distribution();
			mod = mod + pow(ListOfVector[i].data[j], 2);
		}

		/*再根据文档要求：
		Firstly, we randomly generate m random projection vectors {a1, a2, .... am},  where each aj is a d-
		dimensional vector whose entries are drawn independently and uniformly from the standard Normal
		distribution N(0, 1) and we normalize each ai to have unit length.*/
		mod = sqrt(mod);
		for (int k = 0; k < 784; k++) {
			ListOfVector[i].data[k] = ListOfVector[i].data[k] / mod;
		}

	}

	/*返回的是整个向量表*/
	return ListOfVector;
}


/*未根据等级排序的投影表
VecList：随机向量表
d：object的维度
ObjList：object表
cardinality：database的基数*/
//这里关于object表的引用表示可能出问题
// ProjectList ProjectListWithoutRank(const vector* &VecList, const int d, const image* &ObjList, const int cardinality)
PROJECTLIST ProjectListWithoutRank(const VECTORLIST &VecList, const int d, const PICTURELIST &ObjList, const int cardinality) {
	PROJECTLIST ProListWithouRank = new PAIRLIST[50];
	for (int i = 0; i < 50; i++) {
		ProListWithouRank[i] = new pair[cardinality];
		for (int j = 0; j < cardinality; j++) {
			/*用内积求object的等级*/
			float InnerProduction = 0;
			for (int k = 0; k < d; k++) {
				InnerProduction += VecList[i].data[k] * ObjList[j].data[k];
			}
			ProListWithouRank[i][j].pValue = InnerProduction;
			/*object对应的编号*/
			ProListWithouRank[i][j].pictureId = ObjList[j].objectId;
		}
	}
	return ProListWithouRank;
}

PROJECTLIST rankedProjectList(const VECTORLIST &VecList, const int d, const PICTURELIST &ObjList, const int cardinality) {
	PROJECTLIST ProListWithouRank = new PAIRLIST[50];
	for (int i = 0; i < 50; i++) {
		ProListWithouRank[i] = new pair[cardinality];
		for (int j = 0; j < cardinality; j++) {
			/*用内积求object的等级*/
			float InnerProduction = 0;
			for (int k = 0; k < d; k++) {
				InnerProduction += VecList[i].data[k] * ObjList[j].data[k];
			}
			ProListWithouRank[i][j].pValue = InnerProduction;
			/*object对应的编号*/
			ProListWithouRank[i][j].pictureId = ObjList[j].objectId;
		}
	}

	/*根据rank的值进行排序*/
	PROJECTLIST ProListWithRank = pairListSort(ProListWithouRank, cardinality);
	return ProListWithRank;
}

/*释放申请的动态内存空间*/
// void FreeDataOfVecList(vector* VecList) {
void freeData(VECTORLIST &VecList) {
	delete(VecList);
	VecList = NULL;
}

// void FreeDataOfPairList(pair* PairList) {
void freeData(PAIRLIST &PairList) {
	delete(PairList);
	PairList = NULL;
}

// void FreeDataOfProjectList(PROJECTLIST &ProList, const int d) {
void freeData(PROJECTLIST &ProList, const int d) {
	/*此处要注意的是ProList下包含有d个数对表*/
	for (int i = 0; i < d; i++) {
		freeData(ProList[i]);
	}
	delete(ProList);
	ProList = NULL;
}
