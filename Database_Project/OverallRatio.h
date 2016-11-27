#ifndef OVERALLRATIO_H
#define OVERALLRATIO_H


// 用来测试overallRatio MEDRANK算法
float overallRatio(
	const int cardinality,			// 数据库基数
	const char* dataSet,			// 数据库文件
	const int querySize,			// 序列数量
	const char* querySet,			// 序列集合文件名
	int* resultOfMEDRANK,			// MEDRANK结果序列
	int* resultOfL2NN);				// L2NN结果序列

float countDistance(				// 平方距离和
	picture &object,			// 元素
	picture &query 				// 序列
	);

// count index Size of a single B+ tree
int indexSize(
	const int cardinality
	);

#endif
