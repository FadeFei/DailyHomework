#ifndef RandomOfGaussianDistribution_H
#define RandomOfGaussianDistribution_H

float normal_distribution();

VECTORLIST randomVector();


PROJECTLIST ProjectListWithoutRank(const VECTORLIST &VecList, const int d, const PICTURELIST &ObjList, const int cardinality);

PROJECTLIST rankedProjectList(const VECTORLIST &VecList, const int d, const PICTURELIST &ObjList, const int cardinality);

void freeData(VECTORLIST &VecList);
void freeData(PAIRLIST &PairList);
void freeData(PROJECTLIST &ProList, const int d);

#endif
