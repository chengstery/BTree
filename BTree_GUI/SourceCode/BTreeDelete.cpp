#include "BTreeDelete.h"

/*
* 找到非最底层非终端节点节点的前驱节点
* 并将结点 node 换成前驱结点
* 将位置 i 换成前驱节点需要删除的关键字的位置
*/
void Successor(BTree *node, int *i) {
    // 判非法输入（结点为空或为最底层非终端结g点）
    if (*node == NULL) return;
    if ((*node)->ptr[*i - 1] == NULL) return;

    // 找到左子树最右边的值
    BTree search = (*node)->ptr[*i - 1];
    while (search->ptr[search->keyNum] != NULL) search = search->ptr[search->keyNum];

    // 替换掉原结点的的记录值
    (*node)->key[*i] = search->key[search->keyNum];
    (*node)->data[*i] = search->data[search->keyNum];

    // 最后修改结点和位置信息为前驱结点的信息
    *node = search;
    *i = search->keyNum;
}


/* 将指定结点中第 i 个记录移除 */
Status RemoveRecord(BTree *node, int i) {
    // 判空
    if (*node == NULL) return FALSE;

    // 将所有记录前移
    for (; i < (*node)->keyNum; i++) {
        (*node)->key[i] = (*node)->key[i + 1];
        (*node)->data[i] = (*node)->data[i + 1];
    }

    (*node)->keyNum--;
    (*node)->data[i] = NULL;

    return TRUE;
}

/* 将 data 插入到指定结点的第 i 个位置 */
Status InsertRecord(BTree *node, int i, Liter data) {
    // 判空
    if (*node == NULL) return FALSE;

    // 从最后面开始，依次将记录往后移动
    for (int j = (*node)->keyNum; j >= i; j--) {
        (*node)->key[j + 1] = (*node)->key[j];
        (*node)->data[j + 1] = (*node)->data[j];
    }

    // 空出一个位置给新记录
    (*node)->key[i] = data->literatureNumber;
    (*node)->data[i] = data;
    (*node)->keyNum++;

    return TRUE;
}

/* 将右结点合并到左结点，结果放在左结点 left 中，右结点 right 将被释放 */
void CombineBTNode(BTree *left, BTree *right) {
    // 判异常操作
    if (*left == NULL) return;

    // 将右节点的记录和孩子依次插入到左节点的最右边
    for (int i = 1; i <= (*right)->keyNum; i++) {
        Insert(left, (*left)->keyNum + 1, (*right)->data[i], (*right)->ptr[i]);
    }
    // 释放右结点
    free(*right);
}

/* 删除一个空根 */
void DeleteRoot(BTree *root) {
    // 空根只有一个孩子
    BTree child = (*root)->ptr[0];

    // 将该孩子的数据全都搬到新根，再释放孩子就行
    // 这里需要额外将第 0 个孩子指针移动到根结点（注意了，孩子的双亲需要手动改！）
    (*root)->ptr[0] = child->ptr[0];
    if (child->ptr[0] != NULL) child->ptr[0]->parent = *root;
    for (int i = 1; i <= child->keyNum; i++) Insert(root, i, child->data[i], child->ptr[i]);
}

/*
* 针对某个结点调整一颗 B 树
* node	：受调整的结点
* pi	：受调整结点在双亲结点的位置
*/
void RestoreBTree(BTree *node, int pi) {
    // 双亲和可能存在的左右兄弟
    BTree parent, brother;
    parent = (*node)->parent;

    // 用于递归调整双亲的记录存储
    KeyType key;

    // 先看看左兄弟有没有可以借的
    if (pi > 0 && (brother = parent->ptr[pi - 1])->keyNum > MIN_KEY) {
        // 先将左双亲的记录拿下来（从左双亲拿的记录，必为受调整结点记录的最小值，直接插入到受调结点的第 1 位，插入后新记录的右孩子为原先的第 0 位孩子）
        // 这里是将第 0 位孩子插入到第 1 位，相当于第 0 和 1 俩个孩子是一样的，只不过为了将 0 好位置腾出来接纳左兄弟最大的孩子，和向右兄弟借的情况不太一样
        Insert(node, 1, parent->data[pi], (*node)->ptr[0]);
        // 然后修改新记录的左孩子，应为左兄弟的最大的孩子
        (*node)->ptr[0] = brother->ptr[brother->keyNum];
        if (brother->ptr[brother->keyNum] != NULL) brother->ptr[brother->keyNum]->parent = *node;
        // 然后将左双亲记录删去（这里仅仅只是删除记录，而不动孩子指针，因为删除了该记录，还有来自左兄弟的记录补给呀）
        RemoveRecord(&parent, pi);
        // 再将左兄弟的值补回左双亲（从左孩子拿的记录，必为左兄弟最大的一位，且插入到双亲的第 pi 位，做双亲右孩子不改变，插在第 pi 位右孩子位置为 pi）
        InsertRecord(&parent, pi, brother->data[brother->keyNum]);
        // 最后将左兄弟对应记录删去
        RemoveRecord(&brother, brother->keyNum);
    }
        // 再看看右兄弟，其操作思路同理左兄弟，只不过细节略微不同
    else if (pi < parent->keyNum && (brother = parent->ptr[pi + 1])->keyNum > MIN_KEY) {
        // 首先将右双亲的记录拿下来插入到最右边（比受调结点所有记录都大），且新记录的右孩子为右兄弟最小的孩子（该最小孩子是受调结点的最大孩子）
        // 这里直接将右兄弟最小孩子插入即可，不需要再挪动孩子位置了
        Insert(node, (*node)->keyNum + 1, parent->data[pi + 1], brother->ptr[0]);
        // 然后继续删除右双亲记录，插入右兄弟记录，再删除右兄弟记录
        RemoveRecord(&parent, pi + 1);
        InsertRecord(&parent, pi + 1, brother->data[1]);
        RemoveRecord(&brother, 1);
        // 最后多了一步，将左兄弟最小孩子的指针删去（这里将右兄弟第 1 条记录删除了，最左边的记录已经被拿走了，此时因为是在第一位对后边有影响，故需要删掉，不同于上边）
        for (int i=0; i <= brother->keyNum; i++) brother->ptr[i] = brother->ptr[i + 1];
    }
        // 都没有的话直接向双亲借，这里先向左双亲借
    else if (pi > 0) {
        brother = parent->ptr[pi - 1];
        // 先将左双亲的记录拿下来，同样将受调结点的最小孩子向右挪动一位
        Insert(node, 1, parent->data[pi], (*node)->ptr[0]);
        // 然后将左双亲记录删去
        RemoveRecord(&parent, pi);
        // 再将受调结点合并到左兄弟，并释放掉受调结点（这时候原本受调结点空出来的最小孩子，刚好由左兄弟的最大孩子填补了）
        CombineBTNode(&brother, node);
        // 这时记得把 node 补回来，因为函数的设计默认是合并到左兄弟，而右兄弟被释放
        *node = brother;
        // 最后将左双亲 pi 处的孩子指针也删去（因为左双亲的记录被拿走了，而且没有新记录补充）
        for (int i = pi; i <= parent->keyNum; i++) parent->ptr[i] = parent->ptr[i + 1];

        // 借完之后再看看双亲需不需要调整
        if (parent->keyNum < MIN_KEY) {
            // 如果需要调整的是根结点的话，此时的根节点必然没有关键字了（因为根节点最少的关键字数是 1）
            // 此时根节点必然只有一个孩子，所以直接将该孩子代替根节点，就解决了
            if (parent->parent == NULL) DeleteRoot(&parent);
                // 否则的话继续调整双亲结点
            else RestoreBTree(&parent, Search(parent->parent, (*node)->key[1]) - 1);
        }
    }
        // 没有左双亲的话（受调结点在最左边了），则向右双亲借，操作思路同理，这里就不写注释了
    else {
        brother = parent->ptr[pi + 1];
        Insert(node, (*node)->keyNum + 1, parent->data[pi + 1], brother->ptr[0]);
        RemoveRecord(&parent, pi + 1);
        CombineBTNode(node, &brother);
        // 最后将左双亲 pi 处的孩子指针也删去（因为左双亲的记录被拿走了，而且没有新记录补充）
        for (int i = pi + 1; i <= parent->keyNum; i++) parent->ptr[i] = parent->ptr[i + 1];

        if (parent->keyNum < MIN_KEY) {
            if (parent->parent == NULL) DeleteRoot(&parent);
            else RestoreBTree(&parent, Search(parent->parent, (*node)->key[(*node)->keyNum + 1]) - 1);
        }
    }
}

/* 对 B 树执行删除操作 */
Status DeleteBTree(BTree tree, KeyType key) {
    // 先找到需要删除的结点，不存在该节点则返回失败
    result r;
    SearchBTree(tree, key, &r);
    if (r.tag == 0) return FALSE;

    // 找到该结点后，若非最下层非终端结点，则处理成最下层非终端结点
    // 将前驱记录替换要删除的记录，并且 pt 和 i 换成前驱结点及其记录的位置，即转化为删除最下层非终端结点
    if (r.pt->ptr[0] != NULL) Successor(&(r.pt), &(r.i));

    // 先将要删除的 key 保留下来
    key = r.pt->key[r.i];
    // 再将指定的记录删除
    RemoveRecord(&(r.pt), r.i);
    // 然后就可以通过保留的 key 找到要删除的记录在双亲结点的位置
    // 因为 key 已经被删除，所以可以定位到其本应该再双亲结点的位置，为下面调整树形做准备
    if (r.pt->parent == NULL) return TRUE;
    int pi = Search(r.pt->parent, key) - 1;

    // 判断删除之后，若关键字数量小于最小数量，需另外处理
    // 如果是根，则不需要调整了，因为既然删除操作发生在了根，说明已经没有左右兄弟和双亲了
    if (r.pt->parent != NULL && r.pt->keyNum < MIN_KEY) RestoreBTree(&(r.pt), pi);

    return TRUE;
}
