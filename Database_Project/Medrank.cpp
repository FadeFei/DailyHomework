#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "definition.h"
#include "block_file.h"
#include "Medrank.h"
#include <iostream>
#include <sstream>
using namespace std;

//利用二分法查找bNode中的key的index
int searchKey(const bNode &data, float key) {
    int l = 0, h = data.num_entries - 1;
    if (key < data.key[l])
        return -1;
    int temp;
    while (l < h) {
        temp = (l + h) / 2;
        if (data.key[temp] == key) {
            return temp;
        } else if (data.key[temp] < key) {
            l = temp + 1;
            if (data.key[l] > key)
                return temp;
        } else {
            h = temp - 1;
            if (data.key[h] <= key)
                return h;
        }
    }
    return h;
}

float leftShift(BlockFile &searchData, bNode &data, cursor &point, int &IOcost) {
    searchData.read_block((Block) &data, point.index);
    IOcost++;
    if (point.index == -1) {
         return -1;
    } else {
        if (point.rank == 0) {
            //BNODE没有point的情况，读取左兄弟最右边的POINT
            point.rank = ENTRYSIZE - 1;
             //从BNODE的最右边开始读取Piont的值
            point.index = data.left_sibling;
            if (point.index != -1) {
                //左兄弟存在，读取左兄弟的数据
                searchData.read_block((Block) &data, point.index);
                IOcost++;
            } else {
                // 没有左兄弟，说明为最左的BNode了
                return -1;
            }
        } else {
            point.rank--;
        }
        point.pValue = data.key[point.rank];
        point.pictureId = data.son[point.rank];
        return point.pValue;
    }
}

float rightShift(BlockFile &searchData, bNode &data,cursor &point, int &IOcost){
    searchData.read_block((Block) &data, point.index);
    IOcost++;
    if (point.index == -1) {
         return -1;
    } else {

        if (point.rank + 1 < data.num_entries) {
            point.rank += 1;
        } else {
            //获取右兄弟的Bnode
            point.rank = 0;
            point.index = data.right_sibling;
            if (point.index != -1) {
                searchData.read_block((Block) &data, point.index);
                IOcost++;
            } else {
                return -1;
            }
        }
        point.pValue = data.key[point.rank];
        point.pictureId = data.son[point.rank];
        return point.pValue;
    }
}

void Place(const PROJECTLIST &projectList, BLOCKFILELIST &blockFileList,CURSORLIST &Li,
    CURSORLIST  Hi, const int query, int &IOcost) {
    bNode data;
    for (int i = 0; i < DIMENSION; i++) {
        //对于每个LINE在块中查找查询的值
        Li[i].index = (*blockFileList[i]).num_blocks_ - 1;
        do {
            (*blockFileList[i]).read_block((Block) &data, Li[i].index);
            IOcost++;
            Li[i].rank = searchKey(data, projectList[i][query].pValue);
            if (Li[i].rank != -1) {
                Li[i].index = data.son[Li[i].rank];
                Li[i].pictureId = data.son[Li[i].rank];
            }
        } while(data.level != 0 && Li[i].rank != -1);

          // 找到的情况：Li和Hi的index设置为Block的index
        if (Li[i].rank != -1) {
            Li[i].index = data.index;
            Li[i].pValue = data.key[Li[i].rank];
            Hi[i].index = data.index;
            Hi[i].rank = Li[i].rank;
            Hi[i].pictureId = Li[i].pictureId;
            Hi[i].pValue = Li[i].pValue;
        } else {
            Li[i].index = -1;
            // 读取最左边的块
            (*blockFileList[i]).read_block((Block) &data, 0);
            IOcost++;
             //Hi为第一个Point
            Hi[i].index = 0;
            Hi[i].rank = 0;
            Hi[i].pictureId = data.son[0];
            Hi[i].pValue = data.key[0];
        }

        //Li和Hi指向同一块时，分别左移右移
        if (Li[i].rank != -1 && Li[i].pValue == projectList[i][query].pValue) {
            leftShift((*blockFileList[i]), data, Li[i], IOcost);
            rightShift((*blockFileList[i]), data, Hi[i], IOcost);
        } else if (Hi[i].pValue <= projectList[i][query].pValue) {
        //Hi值小于查询qi的值，确保Hi大于qi
            float indexHi = rightShift((*blockFileList[i]), data, Hi[i], IOcost);
            if (indexHi != -1 && Hi[i].pValue <= projectList[i][query].pValue) {
                rightShift((*blockFileList[i]), data, Hi[i], IOcost);
            }
        }
    }
    return;
}
int medrankforeachquery(const PROJECTLIST &projectList, BLOCKFILELIST &blockFileList,
    int* &frequence, CURSORLIST &Li, CURSORLIST &Hi, const int query,int &IOcost) {
    int result = -1, position;
    float sub1, sub2;
     // 为CNN向量寻找最少频率的需求
    const int requirement = MINFREQ * DIMENSION;
    bNode dataLo[DIMENSION];
    bNode dataHi[DIMENSION];
    while (result < 0) {
        for (int i = 0; i < DIMENSION && result < 0; i++) {
            //位于Hi指针链中（右侧），保存位置右移
            if (Li[i].index == -1) {
                position = Hi[i].pictureId;
                rightShift((*blockFileList[i]), dataHi[i], Hi[i], IOcost);
            } else if (Hi[i].index == -1) {
                //位于Li指针链中（左侧）保存位置左移
                position = Li[i].pictureId;
                leftShift((*blockFileList[i]), dataLo[i], Li[i], IOcost);
            } else {
                sub1 = projectList[i][query].pValue - Li[i].pValue;
                sub2 = Hi[i].pValue - projectList[i][query].pValue;
                if (sub1 < sub2) {
                    position = Li[i].pictureId;
                    leftShift((*blockFileList[i]), dataLo[i], Li[i], IOcost);
                } else {
                    position = Hi[i].pictureId;
                    rightShift((*blockFileList[i]), dataHi[i], Hi[i], IOcost);
                }
            }
            frequence[position]++;
            if (frequence[position] >= requirement) {
                result = position;
            }
        }
    }
    return result;
}

int *searchByMEDRANK(PROJECTLIST &Qlist, const int cardinality, const int qsize,  int &IO)
{
    //获取起始时间
    int starttime = clock();
    //用于存储所有查询q的MEDRANK之后的最大值的object的index
    int* results = new int[qsize];
    //用于储存得票数foi
    int* frequence = new int[(cardinality+1)];
    // 建立Li和Hi
    CURSORLIST Li = new cursor[DIMENSION];
    CURSORLIST Hi = new cursor[DIMENSION];

    BLOCKFILELIST blockFileList = new BLOCKPOINT[DIMENSION];
    // 从磁盘中读取数据
    char name[12] = "tree_00.dat";
    for (int i = 0; i < DIMENSION; i++) {
        blockFileList[i] = new BlockFile(name, sizeof(bNode));
        if (name[6] > '9') {
            name[6] = '0';
            name[5]++;
        }
    }

    for (int i = 0; i < qsize; i++) {
        //foi初始为0
        for (int j = 0; j < cardinality + 1; j++)  frequence[j] = 0;

        // 将序列中的指针位置进行调整
        Place(Qlist, blockFileList, Li, Hi, i, IO);
        results[i] = medrankforeachquery(Qlist, blockFileList, frequence, Li, Hi, i, IO);
        printf("After MEDRANK By test q%d, result is object%d\n", i, results[i]);
    }
    printf("MEDRANK Algorithm spends %lds\n", (clock() - starttime) / 1000000);


    for (int i = 0; i < DIMENSION; i++) {
        delete blockFileList[i];
    }
    delete []frequence;
    delete []Li;
    delete []Hi;
    return results;
}

