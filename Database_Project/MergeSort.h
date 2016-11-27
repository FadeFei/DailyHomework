#ifndef MERGESORT_H
#define MERGESORT_H

// 序列排序
PROJECTLIST pairListSort(PROJECTLIST &unrankedDataList, int dataSize);
// 使用归并排序
void mergeSort(PAIRLIST &project, int dataSize);
void sort(PAIRLIST &project, int lo, int hi, PAIRLIST &add_to_the_tail);
void merge(PAIRLIST &project, int lo, int mid, int hi, PAIRLIST &add_to_the_tail);

#endif
