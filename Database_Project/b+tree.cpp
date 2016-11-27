#include <cstdio>
#include <cmath>
#include "definition.h"
#include "block_file.h"
#include "b+tree.h"

// 块加载
void BulkLoading(const PAIRLIST &projection, const int n, char* fileName) {
    int height = 0;    //  B+树的高度
    // 因为每个树节点最多能有ENTRYSIZE个孩子节点
    for (int i = n; i > 0; i /= ENTRYSIZE) {
        height++;
    }
    // 对于给定的一条线，它需要height条节点链表去构建B+树
    NODELIST* nodelist = new NODELIST[height];

    int allocate_size = 1;
    // 为树的每一层分配足够大的空间，从上到下依次乘以ENTRYSIZE
    for (int i = height-1; i >= 0; i--) {
        nodelist[i] = new bNode[allocate_size];
        allocate_size *= ENTRYSIZE;
    }

    // 调用构造函数创建一个块文件来储存数据
    BlockFile outputFile(fileName, sizeof(bNode));

    int index_ = 0;                    //  块的下标
    int cur_projection = 0;     //  线line的当前下标
    int level_size = n;              // 当前层次的节点总数
    int last_level_size = n;     //  上一层的节点总数

    for (char level = 0; level < height; level++) {  //  从下往上遍历树的每一个层次
        last_level_size = level_size;          // 更新上一层次节点数
        level_size = ceil((float)level_size/ENTRYSIZE);  // 当前节点树为(上一层节点数/ENTRYSIZE)，再向上取整
        int sum = 0;     //  当前层次entry的总数
        int cur_index = 0;    // 此时下一层次孩子节点的下标
        for (int i = 0; i < level_size; i++) {  // 遍历当层所有的树节点bnode
            nodelist[level][i].num_entries = 0;     // 当前树节点的entry总数初始化为0
            for (int j = 0; j < ENTRYSIZE && sum < last_level_size && cur_projection <= n; j++) {  // 遍历当前节点的entry进行赋值
                if (level == 0) {  // 树的最底层， 把线line的数据插入到B+树节点中
                    nodelist[0][i].key[j] = projection[cur_projection].pValue;
                    nodelist[0][i].son[j] = projection[cur_projection].pictureId;
                    cur_projection++;  //  当前下标不应该超过线line的长度n
                } else {    // 通过连接节点建立节点之间的父子关系，构建完整B+树
                    nodelist[level][i].key[j] = nodelist[level-1][cur_index].key[0];
                    nodelist[level][i].son[j] = nodelist[level-1][cur_index].index;
                    cur_index++;  // 下一层对应节点下标+1，相当于向右移动一个节点
                }
                nodelist[level][i].num_entries++;  // 当前树节点的entry总数加一
                sum++;     //  当层entry总数不应该大于上一层节点总数
            }
            nodelist[level][i].level = level;
            nodelist[level][i].index = index_; index_++;
            nodelist[level][i].left_sibling= i-1;
            nodelist[level][i].right_sibling = (i == level_size-1) ? -1 : i+1;
            // 把当前树节点作为一个块添加到整个块文件中
            outputFile.append_block((Block)(&nodelist[level][i]));
        }
    }
    // 释放空间，避免内存错误
    for (int i = 0; i < height; i++) {
        delete []nodelist[i];
    }
}

 // 建B+树，并储存数据到本地磁盘
void storeOnDisk(const PROJECTLIST &projectLists,  const int n) {
    char name[12] = "tree_00.dat";  // 文件命名
    for (int i = 0; i < DIMENSION; i++) {
        BulkLoading(projectLists[i], n, name);  // 通过块加载来建树
        // 文件重命名
        name[6]++;
        if (name[6] > '9') {
            name[6] = '0';
            name[5]++;
        }
    }
}

