#include "TreeVision.h"

// 辅助函数：递归打印B树的结点
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

// 打开文件并写入B树的DOT格式
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

    // 执行 dot 命令来生成图像
    system("E:\\App\\Graphviz\\bin\\dot -Tpng ../Btree.dot -o ../Btree.png");
    sprintf(mes, "在当前文件夹生成tree.png文件");
}