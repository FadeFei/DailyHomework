#ifndef DEFINE_H
#define DEFINE_H

// 数据库成员的维度
#define PICTURE_SIZE 784
#define ROW 28
#define COL 28
// MINFREQ初始化
#define MINFREQ 0.5
#define PAGE_SIZE 1024
// 方阵空间的维度
#define DIMENSION 50
#define PI 3.1415926535898

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


// 块文件头的长度
const int BFHEAD_LENGTH = (int) (sizeof(int) * 2);
const int SIZEINT = (int) sizeof(int);

// 利用B+树指针存储(key, son)
// [the total size (1KB) - other node values] / (sizeof(key) + sizeof(son))
const int ENTRYSIZE = (PAGE_SIZE - sizeof(char) - sizeof(int) * 4) / (sizeof(float) + sizeof(int));

// 存储维度28 * 28
struct picture {
    int objectId;
    int data[PICTURE_SIZE];
};

// 使用一个向量来校对文件
// 从N(0, 1)中读出向量
struct vector {
    float data[PICTURE_SIZE];
};

// (Ci, Vij) 意味着在 Ci <pictureId> 中的向量ID在LI中
//Vij (pValue) 意味着向量的秩 i 在Line j中
struct pair {
    int pictureId;
    float pValue;
};

// B+ 树
struct bNode {
    char level;        // b+tree等级
    int index;          // 在块文件中的序列
    int num_entries;   // 在节点中的元素数目
    int left_sibling;   // 左子节点
    int right_sibling;  // 右子节点
    float key[ENTRYSIZE];        // 标记
    int son[ENTRYSIZE];           // 子节点ID
};


struct cursor {
    int index;          // 块文件index - 1
    int rank;           // 节点序列
    int pictureId;         // 数据库ID
    float pValue;       // 投影
};

typedef pair* PAIRLIST;
typedef PAIRLIST* PROJECTLIST;
typedef picture* PICTURELIST;
typedef vector* VECTORLIST;
typedef bNode* NODELIST;
//typedef NODELIST* LEVEL;
typedef cursor* CURSORLIST;
typedef char* Block;

#endif
