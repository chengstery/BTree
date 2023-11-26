#ifndef BTREE_BTREEDELETE_H
#define BTREE_BTREEDELETE_H

#include "ProcessData.h"

void Successor(BTree *node, int *i);
Status RemoveRecord(BTree *node, int i);
Status InsertRecord(BTree *node, int i, Liter data);
void CombineBTNode(BTree *left, BTree *right);
void DeleteRoot(BTree *root);
void RestoreBTree(BTree *node, int pi);
Status DeleteBTree(BTree tree, KeyType key);

#endif //BTREE_BTREEDELETE_H
