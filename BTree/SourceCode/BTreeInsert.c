#include "BTreeInsert.h"

void Insert(BTree *q, int i, Liter data, BTree ap){
    // 关键字x和新结点指针ap分别插入到q->key[i]和q->ptr[i]
    int j, n = (*q)->keyNum;
    for(j=n; j>=i; j--){
        (*q)->key[j+1] = (*q)->key[j];
        (*q)->data[j+1] = (*q)->data[j];
        (*q)->ptr[j+1] = (*q)->ptr[j];
    }
    (*q)->key[i] = data->literatureNumber;
    (*q)->data[i] = data;
    (*q)->ptr[i] = ap;
    if(ap != NULL) ap->parent = *q;
    (*q)->keyNum++;
}

void newRoot(BTree *t, BTree p, Liter data, BTree ap){ // 生成新的根结点
    *t = (BTNode*)malloc(sizeof(BTNode));
    (*t)->keyNum = 1;
    (*t)->ptr[0] = p;
    (*t)->ptr[1] = ap;
    (*t)->key[1] = data->literatureNumber;
    (*t)->data[1] = data;

    if(p != NULL) p->parent = *t;
    if (ap!= NULL) ap->parent = *t;
    (*t)->parent = NULL;  // 新根的双亲结点是空指针
}

void split(BTree *q, int s, BTree *ap){
    // 将q结点分裂成两个结点，前一半保留在原结点，后一半移入ap所指新结点
    int i, j, n = (*q)->keyNum;
    *ap = (BTNode*)malloc(sizeof(BTNode)); // 生成新结点
    (*ap)->ptr[0] = (*q)->ptr[s];
    for (i=s+1, j=1; i<=n; i++, j++){   // 后一半移入ap结点
        (*ap)->key[j] = (*q)->key[i];
        (*ap)->data[j] = (*q)->data[i];
        (*ap)->ptr[j] = (*q)->ptr[i];
    }
    (*ap)->keyNum = n-s;
    (*ap)->parent = (*q)->parent;
    for (i=0; i<=n-s;i++)     // 修改新结点的子结点的parent域
        if ((*ap)->ptr[i] != NULL)
            (*ap)->ptr[i]->parent = (*ap);
    (*q)->keyNum =  s-1;  // q结点的前一半保留，修改keyNum
}

void InsertBTree(BTree *t, Liter data, BTree q, int i){
    // 在B树t中q结点的key[i-1]和key[i]之间插入关键字k
    // 若插入后结点关键字个数等于B树的阶，则沿双亲指针链进行节点分裂，使t仍是m阶B树
    Liter x;
    int s, finished = FALSE, needNewRoot = FALSE;
    BTree ap;
    if (NULL == q) newRoot(t, NULL, data, NULL);  // 生成新根结点
    else{
        x = data;
        ap = NULL;
        while (FALSE == needNewRoot && FALSE == finished){
            Insert(&q, i, x, ap);  // x和ap分别插入到q->key[i]和q->ptr[i]
            if (q->keyNum < m) finished = TRUE;   // 插入完成
            else {  // 分裂q结点
                s = (m+1)/2;
                split(&q, s, &ap);
                x = q->data[s];
                if (q->parent != NULL){
                    q = q->parent;
                    i = Search(q, x->literatureNumber); // 在双亲结点中查找x的插入位置
                }else needNewRoot = TRUE;
            }
        }
        if (TRUE == needNewRoot) // t 是空树，或者根节点已分裂为q和ap结点
            newRoot(t, q, x, ap);  // 生成含信息(q,x,ap)的新的根节点
    }
}

bool InsertBNode(BTree *t, Liter data){
    result r;
    SearchBTree(*t, data->literatureNumber, &r);
    if (!r.tag)
        InsertBTree(t, data, r.pt, r.i);
    else {
        r.pt->data[r.i]->currentStock++;
        r.pt->data[r.i]->totalStock++;
    }
    return !r.tag;
}