#ifndef PREPROCESSING_H
#define PREPROCESSING_H

// process the query set by projecting the query into <DIMENSION> randomvectors
PROJECTLIST queryPreprocess(
	const char *querySet,              // filename of query set
	const int querySize,               // cardinality of queries
	const int cardinality,                // cardinality of database
	const int dimension,               // dimension of object
	const VECTORLIST &RandomVectorList     // random vectors
);
// preprocessing the data
// read <cardinality> object from dataset with <dimension> lines
// create <DIMENSION> random vectors and project them on lines
// sort these project list
// return ranked projection list
PROJECTLIST dataPreprocess(
	const char *dataSet,				// dataset
    const int cardinality,				// cardinality of database
    const int dimension,				// dimension of object
    const VECTORLIST &RandomVectorList        // random vectors
);


#endif
