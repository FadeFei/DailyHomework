#ifndef L2NN_H
#define L2NN_H

class BlockFile;

int *searchByL2NN(const char* dataSet, const int cardinality,
    const char* querySet, const int querySize);

void countDistance(picture &object,picture &query,float &sumOfDistance);

#endif
