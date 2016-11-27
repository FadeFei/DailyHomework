#ifndef MEDRANK_H
#define MEDRANK_H

class BlockFile;

int searchKey(const bNode &data, float key);

float leftShift(BlockFile &searchData, bNode &data, cursor &point, int &IOcost);

float rightShift(BlockFile &searchData, bNode &data,cursor &point, int &IOcost);

void Place(const PROJECTLIST &projectList, BLOCKFILELIST &blockFileList,
	CURSORLIST &Li, CURSORLIST  Hi, const int query, int &IOcost);

int medrankforeachquery(const PROJECTLIST &projectList, BLOCKFILELIST &blockFileList,
	int* &frequence, CURSORLIST &Li, CURSORLIST &Hi, const int query, int &IOcost);

int *searchByMEDRANK(PROJECTLIST &Qlist, const int cardinality, const int qsize, int &IO);

#endif
