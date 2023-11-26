#include "BTreeDelete.h"

/*
* �ҵ�����ײ���ն˽ڵ�ڵ��ǰ���ڵ�
* ������� node ����ǰ�����
* ��λ�� i ����ǰ���ڵ���Ҫɾ���Ĺؼ��ֵ�λ��
*/
void Successor(BTree *node, int *i) {
    // �зǷ����루���Ϊ�ջ�Ϊ��ײ���ն˽�g�㣩
    if (*node == NULL) return;
    if ((*node)->ptr[*i - 1] == NULL) return;

    // �ҵ����������ұߵ�ֵ
    BTree search = (*node)->ptr[*i - 1];
    while (search->ptr[search->keyNum] != NULL) search = search->ptr[search->keyNum];

    // �滻��ԭ���ĵļ�¼ֵ
    (*node)->key[*i] = search->key[search->keyNum];
    (*node)->data[*i] = search->data[search->keyNum];

    // ����޸Ľ���λ����ϢΪǰ��������Ϣ
    *node = search;
    *i = search->keyNum;
}


/* ��ָ������е� i ����¼�Ƴ� */
Status RemoveRecord(BTree *node, int i) {
    // �п�
    if (*node == NULL) return FALSE;

    // �����м�¼ǰ��
    for (; i < (*node)->keyNum; i++) {
        (*node)->key[i] = (*node)->key[i + 1];
        (*node)->data[i] = (*node)->data[i + 1];
    }

    (*node)->keyNum--;
    (*node)->data[i] = NULL;

    return TRUE;
}

/* �� data ���뵽ָ�����ĵ� i ��λ�� */
Status InsertRecord(BTree *node, int i, Liter data) {
    // �п�
    if (*node == NULL) return FALSE;

    // ������濪ʼ�����ν���¼�����ƶ�
    for (int j = (*node)->keyNum; j >= i; j--) {
        (*node)->key[j + 1] = (*node)->key[j];
        (*node)->data[j + 1] = (*node)->data[j];
    }

    // �ճ�һ��λ�ø��¼�¼
    (*node)->key[i] = data->literatureNumber;
    (*node)->data[i] = data;
    (*node)->keyNum++;

    return TRUE;
}

/* ���ҽ��ϲ������㣬����������� left �У��ҽ�� right �����ͷ� */
void CombineBTNode(BTree *left, BTree *right) {
    // ���쳣����
    if (*left == NULL) return;

    // ���ҽڵ�ļ�¼�ͺ������β��뵽��ڵ�����ұ�
    for (int i = 1; i <= (*right)->keyNum; i++) {
        Insert(left, (*left)->keyNum + 1, (*right)->data[i], (*right)->ptr[i]);
    }
    // �ͷ��ҽ��
    free(*right);
}

/* ɾ��һ���ո� */
void DeleteRoot(BTree *root) {
    // �ո�ֻ��һ������
    BTree child = (*root)->ptr[0];

    // ���ú��ӵ�����ȫ���ᵽ�¸������ͷź��Ӿ���
    // ������Ҫ���⽫�� 0 ������ָ���ƶ�������㣨ע���ˣ����ӵ�˫����Ҫ�ֶ��ģ���
    (*root)->ptr[0] = child->ptr[0];
    if (child->ptr[0] != NULL) child->ptr[0]->parent = *root;
    for (int i = 1; i <= child->keyNum; i++) Insert(root, i, child->data[i], child->ptr[i]);
}

/*
* ���ĳ��������һ�� B ��
* node	���ܵ����Ľ��
* pi	���ܵ��������˫�׽���λ��
*/
void RestoreBTree(BTree *node, int pi) {
    // ˫�׺Ϳ��ܴ��ڵ������ֵ�
    BTree parent, brother;
    parent = (*node)->parent;

    // ���ڵݹ����˫�׵ļ�¼�洢
    KeyType key;

    // �ȿ������ֵ���û�п��Խ��
    if (pi > 0 && (brother = parent->ptr[pi - 1])->keyNum > MIN_KEY) {
        // �Ƚ���˫�׵ļ�¼������������˫���õļ�¼����Ϊ�ܵ�������¼����Сֵ��ֱ�Ӳ��뵽�ܵ����ĵ� 1 λ��������¼�¼���Һ���Ϊԭ�ȵĵ� 0 λ���ӣ�
        // �����ǽ��� 0 λ���Ӳ��뵽�� 1 λ���൱�ڵ� 0 �� 1 ����������һ���ģ�ֻ����Ϊ�˽� 0 ��λ���ڳ����������ֵ����ĺ��ӣ��������ֵܽ�������̫һ��
        Insert(node, 1, parent->data[pi], (*node)->ptr[0]);
        // Ȼ���޸��¼�¼�����ӣ�ӦΪ���ֵܵ����ĺ���
        (*node)->ptr[0] = brother->ptr[brother->keyNum];
        if (brother->ptr[brother->keyNum] != NULL) brother->ptr[brother->keyNum]->parent = *node;
        // Ȼ����˫�׼�¼ɾȥ���������ֻ��ɾ����¼������������ָ�룬��Ϊɾ���˸ü�¼�������������ֵܵļ�¼����ѽ��
        RemoveRecord(&parent, pi);
        // �ٽ����ֵܵ�ֵ������˫�ף��������õļ�¼����Ϊ���ֵ�����һλ���Ҳ��뵽˫�׵ĵ� pi λ����˫���Һ��Ӳ��ı䣬���ڵ� pi λ�Һ���λ��Ϊ pi��
        InsertRecord(&parent, pi, brother->data[brother->keyNum]);
        // ������ֵܶ�Ӧ��¼ɾȥ
        RemoveRecord(&brother, brother->keyNum);
    }
        // �ٿ������ֵܣ������˼·ͬ�����ֵܣ�ֻ����ϸ����΢��ͬ
    else if (pi < parent->keyNum && (brother = parent->ptr[pi + 1])->keyNum > MIN_KEY) {
        // ���Ƚ���˫�׵ļ�¼���������뵽���ұߣ����ܵ�������м�¼���󣩣����¼�¼���Һ���Ϊ���ֵ���С�ĺ��ӣ�����С�������ܵ���������ӣ�
        // ����ֱ�ӽ����ֵ���С���Ӳ��뼴�ɣ�����Ҫ��Ų������λ����
        Insert(node, (*node)->keyNum + 1, parent->data[pi + 1], brother->ptr[0]);
        // Ȼ�����ɾ����˫�׼�¼���������ֵܼ�¼����ɾ�����ֵܼ�¼
        RemoveRecord(&parent, pi + 1);
        InsertRecord(&parent, pi + 1, brother->data[1]);
        RemoveRecord(&brother, 1);
        // ������һ���������ֵ���С���ӵ�ָ��ɾȥ�����ｫ���ֵܵ� 1 ����¼ɾ���ˣ�����ߵļ�¼�Ѿ��������ˣ���ʱ��Ϊ���ڵ�һλ�Ժ����Ӱ�죬����Ҫɾ������ͬ���ϱߣ�
        for (int i=0; i <= brother->keyNum; i++) brother->ptr[i] = brother->ptr[i + 1];
    }
        // ��û�еĻ�ֱ����˫�׽裬����������˫�׽�
    else if (pi > 0) {
        brother = parent->ptr[pi - 1];
        // �Ƚ���˫�׵ļ�¼��������ͬ�����ܵ�������С��������Ų��һλ
        Insert(node, 1, parent->data[pi], (*node)->ptr[0]);
        // Ȼ����˫�׼�¼ɾȥ
        RemoveRecord(&parent, pi);
        // �ٽ��ܵ����ϲ������ֵܣ����ͷŵ��ܵ���㣨��ʱ��ԭ���ܵ����ճ�������С���ӣ��պ������ֵܵ��������ˣ�
        CombineBTNode(&brother, node);
        // ��ʱ�ǵð� node ����������Ϊ���������Ĭ���Ǻϲ������ֵܣ������ֵܱ��ͷ�
        *node = brother;
        // �����˫�� pi ���ĺ���ָ��Ҳɾȥ����Ϊ��˫�׵ļ�¼�������ˣ�����û���¼�¼���䣩
        for (int i = pi; i <= parent->keyNum; i++) parent->ptr[i] = parent->ptr[i + 1];

        // ����֮���ٿ���˫���費��Ҫ����
        if (parent->keyNum < MIN_KEY) {
            // �����Ҫ�������Ǹ����Ļ�����ʱ�ĸ��ڵ��Ȼû�йؼ����ˣ���Ϊ���ڵ����ٵĹؼ������� 1��
            // ��ʱ���ڵ��Ȼֻ��һ�����ӣ�����ֱ�ӽ��ú��Ӵ�����ڵ㣬�ͽ����
            if (parent->parent == NULL) DeleteRoot(&parent);
                // ����Ļ���������˫�׽��
            else RestoreBTree(&parent, Search(parent->parent, (*node)->key[1]) - 1);
        }
    }
        // û����˫�׵Ļ����ܵ������������ˣ���������˫�׽裬����˼·ͬ������Ͳ�дע����
    else {
        brother = parent->ptr[pi + 1];
        Insert(node, (*node)->keyNum + 1, parent->data[pi + 1], brother->ptr[0]);
        RemoveRecord(&parent, pi + 1);
        CombineBTNode(node, &brother);
        // �����˫�� pi ���ĺ���ָ��Ҳɾȥ����Ϊ��˫�׵ļ�¼�������ˣ�����û���¼�¼���䣩
        for (int i = pi + 1; i <= parent->keyNum; i++) parent->ptr[i] = parent->ptr[i + 1];

        if (parent->keyNum < MIN_KEY) {
            if (parent->parent == NULL) DeleteRoot(&parent);
            else RestoreBTree(&parent, Search(parent->parent, (*node)->key[(*node)->keyNum + 1]) - 1);
        }
    }
}

/* �� B ��ִ��ɾ������ */
Status DeleteBTree(BTree tree, KeyType key) {
    // ���ҵ���Ҫɾ���Ľ�㣬�����ڸýڵ��򷵻�ʧ��
    result r;
    SearchBTree(tree, key, &r);
    if (r.tag == 0) return FALSE;

    // �ҵ��ý����������²���ն˽�㣬��������²���ն˽��
    // ��ǰ����¼�滻Ҫɾ���ļ�¼������ pt �� i ����ǰ����㼰���¼��λ�ã���ת��Ϊɾ�����²���ն˽��
    if (r.pt->ptr[0] != NULL) Successor(&(r.pt), &(r.i));

    // �Ƚ�Ҫɾ���� key ��������
    key = r.pt->key[r.i];
    // �ٽ�ָ���ļ�¼ɾ��
    RemoveRecord(&(r.pt), r.i);
    // Ȼ��Ϳ���ͨ�������� key �ҵ�Ҫɾ���ļ�¼��˫�׽���λ��
    // ��Ϊ key �Ѿ���ɾ�������Կ��Զ�λ���䱾Ӧ����˫�׽���λ�ã�Ϊ�������������׼��
    if (r.pt->parent == NULL) return TRUE;
    int pi = Search(r.pt->parent, key) - 1;

    // �ж�ɾ��֮�����ؼ�������С����С�����������⴦��
    // ����Ǹ�������Ҫ�����ˣ���Ϊ��Ȼɾ�������������˸���˵���Ѿ�û�������ֵܺ�˫����
    if (r.pt->parent != NULL && r.pt->keyNum < MIN_KEY) RestoreBTree(&(r.pt), pi);

    return TRUE;
}
