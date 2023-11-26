#ifndef BTREE_BTREEINSERT_H
#define BTREE_BTREEINSERT_H

#include "DefAndFun.h"

void Insert(BTree *q, int i, Liter data, BTree ap);
void newRoot(BTree *t, BTree p, Liter data, BTree ap);
void split(BTree *q, int s, BTree *ap);
void InsertBTree(BTree *t, Liter data, BTree q, int i);
bool InsertBNode(BTree *t, Liter data);

#endif //BTREE_BTREEINSERT_H
