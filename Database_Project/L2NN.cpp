#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <float.h>
#include "definition.h"
#include "block_file.h"
#include "IO.h"
#include "L2NN.h"

int *searchByL2NN(const char* dataSet, const int cardinality,
    const char* querySet, const int querySize) {
    // 查询结果列表
    int* resultList = new int[querySize];
    float* sumOfDistance = new float[(cardinality+1)];

    // 打开数据集合和序列文件
    PICTURELIST database = readFile(dataSet, cardinality);
    PICTURELIST query = readFile(querySet, querySize);

    // 开始统计时间
    // 创建块文件 读取磁盘

    for (int i = 0; i < querySize; i++) {
    	// 为序列统计距离
    	for (int j = 1; j <= cardinality; j++) {
    		countDistance(database[j], query[i], sumOfDistance[j]);
    	}
    	for (int j = 1; j <= cardinality; j++) {
            // 完整的距离
			sumOfDistance[j] = sqrt(sumOfDistance[j]);
		}

        // 利用最小距离找到最近的向量
		float minimum = FLT_MAX;
		int result = -1;
		for (int j = 1; j <= cardinality; j++) {
			if (sumOfDistance[j] < minimum) {
				minimum = sumOfDistance[j];
				result = j;
			}
		}
        // 在结果列表存储
		resultList[i] = result;
    }

    // 释放数据
    delete []database;
    delete []query;

    return resultList;
}

void countDistance(picture &object, picture &query, float &sumOfDistance) {
    // 初始化距离为0
	sumOfDistance = 0.0;
    // 平方和
	for (int i = 0; i < PICTURE_SIZE; i++) {
		sumOfDistance += pow((query.data[i] - object.data[i]), 2);
	}
}
