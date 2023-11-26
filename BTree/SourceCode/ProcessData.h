#ifndef BTREE_PROCESSDATA_H
#define BTREE_PROCESSDATA_H

#include "BTreeInsert.h"

bool saveData(BTree t);
bool saveDataBinary(BTree t);
bool loadData(BTree *t);
bool loadDataBinary(BTree *t);

#endif //BTREE_PROCESSDATA_H
