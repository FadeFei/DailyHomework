#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "definition.h"
#include "block_file.h"
#include "IO.h"
using namespace std;

// 从file中将数据读入内存
PICTURELIST readFile(const char *File, const int cardinality) {
    // 分配新的内存给数据库中的数据，用Vector指向这些数据的首指针
    PICTURELIST Vector = new picture[cardinality];
    FILE *fp = fopen(File, "r");
    if (!fp) {
        // 输出错误信息
        cout << "file " << File << " open fail." << endl;
        char temp[] = "";
        error(temp, true);
    }
    //将数据库中的数据一个一个付给Vecotr中相应的值
    else for (int i = 0; i < cardinality; i++) {
        fscanf(fp, "%d", &Vector[i].objectId);
        for (int j = 0; j < PICTURE_SIZE; j++) {
            fscanf(fp, "%d", &Vector[i].data[j]);
        }
    }

    fclose(fp);
    return Vector;
}

// 释放掉分配的内存
void freeData(PICTURELIST &Vector) {
    delete []Vector;
    Vector = NULL;
}
