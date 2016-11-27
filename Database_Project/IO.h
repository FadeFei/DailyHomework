#ifndef IO_H
#define IO_H

// 从内存之中读取数据
PICTURELIST readFile(const char *File, const int dataSize);
// 释放内存
void freeData(PICTURELIST &Vector);

#endif
