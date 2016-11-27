#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "definition.h"
#include "block_file.h"
#include "IO.h"
#include "OverallRatio.h"

float countDistance_(picture &object, picture &query) {
    // 初始距离为0
    float sumOfDistance = 0.0;
    // 序列相加
    for (int i = 0; i < PICTURE_SIZE; i++) {
        sumOfDistance += pow((query.data[i] - object.data[i]), 2);
    }
    return sumOfDistance;
}

int indexSize(const int cardinality) {
    int count = 0;
    for (int i = cardinality; i != 1;) {
        i = i / ENTRYSIZE + 1;
        count += i;
    }
    return count * DIMENSION;
}

float overallRatio(
    const int cardinality,          // 数据库参数
    const char* dataSet,            // 数据库文件名
    const int querySize,            // 序列数量
    const char* querySet,           // 序列集合文件名
    int* resultOfMEDRANK,           // MEDRANK的输出结果
    int* resultOfL2NN)              // L2NN的输出结果
{

    float* sumOfRatio = new float[querySize];
    PICTURELIST database = readFile(dataSet, cardinality);
    PICTURELIST query = readFile(querySet, querySize);
    float distanceOfMEDRANK = 0.0;
    float distanceOfL2NN = 0.0;

    for (int i = 0; i < querySize; i++) {
        distanceOfMEDRANK = countDistance_(database[resultOfMEDRANK[i]], query[i]);
        distanceOfL2NN = countDistance_(database[resultOfL2NN[i]], query[i]);
        distanceOfMEDRANK = sqrt(distanceOfMEDRANK);
        distanceOfL2NN = sqrt(distanceOfL2NN);
        sumOfRatio[i] = distanceOfMEDRANK / distanceOfL2NN;
    }


    // 平均ratio的计算
    float sum = 0.0;
    for (int i = 0; i < querySize; i++) {
        sum += sumOfRatio[i];
    }
    sum  = sum / querySize;

    // 释放内存
    freeData(database);
    freeData(query);
    delete []sumOfRatio;
    return sum;
}

