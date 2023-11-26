#ifndef BTREE_GUI_PROCESSDATA_H
#define BTREE_GUI_PROCESSDATA_H

#include "BTreeInsert.h"

Bool saveData(BTree t);
bool saveDataBinary(BTree t);
Bool loadData(BTree *t);
bool loadDataBinary(BTree *t);

#endif //BTREE_GUI_PROCESSDATA_H
