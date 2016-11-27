#include "definition.h"
#include "MergeSort.h"
#include <cstdlib>

// 对无序的链表排序
PROJECTLIST pairListSort(PROJECTLIST &unrankedDataList, int cardinality) {
    for (int i = 0; i < DIMENSION; i++) {
        mergeSort(unrankedDataList[i], cardinality);
    }
    return unrankedDataList;
}

// pairListSort中归并排序要用到的函数
void mergeSort(PAIRLIST &project, int cardinality) {
    PAIRLIST add_to_the_tail = new pair[cardinality];
    sort(project, 0, cardinality - 1, add_to_the_tail);
    delete(add_to_the_tail);
}


void sort(PAIRLIST &project, int lo, int hi,
        PAIRLIST &add_to_the_tail  // 用于暂时存储数据，并在最后将剩余部分加在链表最后
) {
    if (hi <= lo) return;
    // 对前一半和后一半进行排序
    int mid = (lo + hi) / 2;
    sort(project, lo, mid, add_to_the_tail);
    sort(project, mid + 1, hi, add_to_the_tail);
    // 将前一半和后一半进行合并
    merge(project, lo, mid, hi, add_to_the_tail);
}

void merge(PAIRLIST &project,  // 无序链表
    int lo, int mid, int hi,
    PAIRLIST &add_to_the_tail  // 用于暂时存储数据，并在最后将剩余部分加在链表最后
) {
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++)
        add_to_the_tail[k] = project[k];
    for (int k = lo; k <= hi; k++) {
        if (i > mid)
            project[k] = add_to_the_tail[j++];
        else if (j > hi)
            project[k] = add_to_the_tail[i++];
        else if (add_to_the_tail[j].pValue < add_to_the_tail[i].pValue)
            project[k] = add_to_the_tail[j++];
        else
            project[k] = add_to_the_tail[i++];
    }
}
