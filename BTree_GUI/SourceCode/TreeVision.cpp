#include "TreeVision.h"

// �����������ݹ��ӡB���Ľ��
void printNode(BTree node, FILE *out) {
    if (node != NULL) {
        fprintf(out, "%d [label=\"", node->key[1]);

        for (int i = 1; i <= node->keyNum; ++i) {
            fprintf(out, "%d", node->key[i]);
            if (i < node->keyNum) {
                fprintf(out, ",");
            }
        }

        fprintf(out, "\"];\n");

        for (int i = 0; i <= node->keyNum; ++i) {
            if (node->ptr[i] != NULL) {
                fprintf(out, "%d -> %d;\n", node->key[1], node->ptr[i]->key[1]);
            }
        }

        for (int i = 0; i <= node->keyNum; ++i) {
            printNode(node->ptr[i], out);
        }
    }
}

// ���ļ���д��B����DOT��ʽ
void treePrint(BTree root) {
    FILE *out = fopen("../Btree.dot", "w");
    if (out == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "digraph {\nnode[shape=record];\n");
    printNode(root, out);
    fprintf(out, "}\n");

    fclose(out);

    // ִ�� dot ����������ͼ��
    system("E:\\App\\Graphviz\\bin\\dot -Tpng ../Btree.dot -o ../Btree.png");
    sprintf(mes, "�ڵ�ǰ�ļ�������tree.png�ļ�");
}