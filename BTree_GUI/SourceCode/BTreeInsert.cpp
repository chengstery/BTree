#include "BTreeInsert.h"

void Insert(BTree *q, int i, Liter data, BTree ap){
    // �ؼ���x���½��ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
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

void newRoot(BTree *t, BTree p, Liter data, BTree ap){ // �����µĸ����
    *t = (BTNode*)malloc(sizeof(BTNode));
    (*t)->keyNum = 1;
    (*t)->ptr[0] = p;
    (*t)->ptr[1] = ap;
    (*t)->key[1] = data->literatureNumber;
    (*t)->data[1] = data;

    if(p != NULL) p->parent = *t;
    if (ap!= NULL) ap->parent = *t;
    (*t)->parent = NULL;  // �¸���˫�׽���ǿ�ָ��
}

void split(BTree *q, int s, BTree *ap){
    // ��q�����ѳ�������㣬ǰһ�뱣����ԭ��㣬��һ������ap��ָ�½��
    int i, j, n = (*q)->keyNum;
    *ap = (BTNode*)malloc(sizeof(BTNode)); // �����½��
    (*ap)->ptr[0] = (*q)->ptr[s];
    for (i=s+1, j=1; i<=n; i++, j++){   // ��һ������ap���
        (*ap)->key[j] = (*q)->key[i];
        (*ap)->data[j] = (*q)->data[i];
        (*ap)->ptr[j] = (*q)->ptr[i];
    }
    (*ap)->keyNum = n-s;
    (*ap)->parent = (*q)->parent;
    for (i=0; i<=n-s;i++)     // �޸��½����ӽ���parent��
        if ((*ap)->ptr[i] != NULL)
            (*ap)->ptr[i]->parent = (*ap);
    (*q)->keyNum =  s-1;  // q����ǰһ�뱣�����޸�keyNum
}

void InsertBTree(BTree *t, Liter data, BTree q, int i){
    // ��B��t��q����key[i-1]��key[i]֮�����ؼ���k
    // ���������ؼ��ָ�������B���Ľף�����˫��ָ�������нڵ���ѣ�ʹt����m��B��
    Liter x;
    int s, finished = FALSE, needNewRoot = FALSE;
    BTree ap;
    if (NULL == q) newRoot(t, NULL, data, NULL);  // �����¸����
    else{
        x = data;
        ap = NULL;
        while (FALSE == needNewRoot && FALSE == finished){
            Insert(&q, i, x, ap);  // x��ap�ֱ���뵽q->key[i]��q->ptr[i]
            if (q->keyNum < m) finished = TRUE;   // �������
            else {  // ����q���
                s = (m+1)/2;
                split(&q, s, &ap);
                x = q->data[s];
                if (q->parent != NULL){
                    q = q->parent;
                    i = Search(q, x->literatureNumber); // ��˫�׽���в���x�Ĳ���λ��
                }else needNewRoot = TRUE;
            }
        }
        if (TRUE == needNewRoot) // t �ǿ��������߸��ڵ��ѷ���Ϊq��ap���
            newRoot(t, q, x, ap);  // ���ɺ���Ϣ(q,x,ap)���µĸ��ڵ�
    }
}

Bool InsertBNode(BTree *t, Liter data){
    result r;
    SearchBTree(*t, data->literatureNumber, &r);
    if (!r.tag)
        InsertBTree(t, data, r.pt, r.i);
    else{
        r.pt->data[r.i]->currentStock++;
        r.pt->data[r.i]->totalStock++;
    }

    return !r.tag;
}