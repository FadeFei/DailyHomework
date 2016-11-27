#include <cstdio>
#include <cstdlib>
#include "definition.h"
#include "IO.h"
#include "RandomOfGaussianDistribution.h"
#include "processing.h"

// 对数据进行预处理
// 将60000个object从数据库中读出
// 创建784维随即向量并把object投影在Line上面
// 将投影排序
// 返回排好序的投影的集合
PROJECTLIST dataPreprocess(
    const char *dataSet,                      // object的文件名
    const int cardinality,                    // object的多少，应为60000
    const int dimension,                      // object的维度，应为784
    const VECTORLIST &RandomVectorList        // 随即向量
    )
{
    PICTURELIST dataList = readFile(dataSet, cardinality);  //  function in FileIO, to read from dataset to memory
    PROJECTLIST rankedDataList = rankedProjectList(RandomVectorList, dimension, dataList, cardinality);  //  function in NormalDistribution, to create ranked projection list
    freeData(dataList);  //  function in FileIO, to free picture list and return ranked datalist
    return rankedDataList;
}

// 将查询集合向量投影到随机向量上面
PROJECTLIST queryPreprocess(
    const char *querySet,               // 查询集合文件名
    const int querySize,                // 查询集合大小，应为100
    const int cardinality,              // object的多少，应为60000
    const int dimension,                // object的维度，应为784
    const VECTORLIST &RandomVectorList  // 随即向量
    )
{
    PICTURELIST queryList = readFile(querySet, querySize);  //  function in FiloIO, to read queries from file, with the same formats with database elements
    PROJECTLIST unrankedQueryList = ProjectListWithoutRank(RandomVectorList, dimension, queryList, querySize);  //  function in FileIO, to project these queries into <DIMENSION> lines and generating Li projection lists
    freeData(queryList);  // function in FileIO, to return results by using MEDRANK algorithm
    return unrankedQueryList;
}
