#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <cmath>
#include <ctime>
#include <float.h>

#include "definition.h"
#include "block_file.h"
#include "processing.h"
#include "b+tree.h"
#include "MergeSort.h"
#include "IO.h"
#include "RandomOfGaussianDistribution.h"
#include "Medrank.h"
#include "OverallRatio.h"
#include "L2NN.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int startTime = clock();
    int *resultByMEDRANK, *resultByL2NN;
    int cardinality = 60000;
    int dimension = 28 * 28;
    int queryNumber = 100;
    const char *dataSet, *querySet;
    VECTORLIST randomVectors;
    PROJECTLIST rankedDataLists, unrankedQueryList;
    if (argc == 11) {
        string str[11];
        for (int i = 0; i < 11; i++) {
            str[i] = argv[i];
        }
        if (str[1] == "-n" && str[3] == "-d" && str[5] == "-qn"
            && str[7] == "-ds" && str[9] == "-qs") {
            cardinality = atoi((char*)str[2].data());
            dimension = atoi((char*)str[4].data());
            queryNumber = atoi((char*)str[6].data());
            dataSet = (char*)str[8].data();
            querySet = (char*)str[10].data();

            startTime = clock();
            //预先处理
            randomVectors = randomVector();
            rankedDataLists = dataPreprocess(dataSet, cardinality, dimension, randomVectors);
            // bulk-loading的执行以及磁盘存储
            storeOnDisk(rankedDataLists, cardinality);
            freeData(rankedDataLists, DIMENSION);
            //索引大小与索引时间
            int indexsize = indexSize(cardinality);
            printf("Index Size: %d, Index Time: %lds \n", indexsize, (clock() - startTime) / 1000000);
            //序列的构建
            unrankedQueryList = queryPreprocess(querySet, queryNumber, cardinality, dimension, randomVectors);
            // 释放内存
            freeData(randomVectors);
            //使用MEDRANK
            int IOcost = 0;
            resultByMEDRANK = searchByMEDRANK(unrankedQueryList, cardinality, queryNumber, IOcost);
            printf("Total Time Using MEDRANK: %lds\n", (clock() - startTime) / 1000000);
            printf("Total I/O Cost: %d.\n", IOcost);
             startTime = clock();
             resultByL2NN = searchByL2NN(dataSet, cardinality, querySet, queryNumber);
             printf("Total Time Using L2NN : %lds\n", (clock() - startTime) / 1000000);
            float avgRatio = overallRatio(cardinality, dataSet, queryNumber, querySet, resultByMEDRANK, resultByL2NN);
            printf("the average overall ratio of MEDRANK is %f.\n", avgRatio);
            free(resultByMEDRANK);
            free(resultByL2NN);
            return 0;
        }
    }
}
