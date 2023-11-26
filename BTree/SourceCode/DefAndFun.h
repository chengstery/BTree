#ifndef BTREE_DEFANDFUN_H
#define BTREE_DEFANDFUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ANSI颜色码
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
typedef int Status;     // 用作函数值类型，表示函数结果状态
typedef int bool;       // 用布尔值类型
typedef int KeyType;    // 定义关键字类型为整型

#define m 3  // B树的阶，此处设为3

/* B 树关键最大最小值以及中间值 */
#define MIN_KEY ((m-1)/2)

#define MAX_LEN_TITLE 100
#define MAX_LEN_AUTHOR 100

// 装日志信息
extern char str[500];

// 文献信息
typedef struct Literature {
    int literatureNumber;         // 文献编号
    char title[MAX_LEN_TITLE];    // 文献名
    char author[MAX_LEN_AUTHOR];  // 著者
    int currentStock;             // 现存量
    int totalStock;               // 总库存
    int appointNum;         // 已预约数量
    int borrowNum;         // 已借出数量
    char borIdNumber[50][50];  // 证件号，假设最大长度为50
    char appIdNumber[50][50];  // 证件号，假设最大长度为50
    char returnDate[50][50];  // 归还日期，假设最大长度为50
} Literature, *Liter;

// B树结点
typedef struct BTNode{
    int keyNum;             // 结点当前关键字个数
    KeyType key[m + 1];     // 关键字数组，key[0]未用
    struct BTNode *parent;  // 双亲结点
    struct BTNode *ptr[m + 1];     // 孩子结点指针数组, 0 号有使用
    Liter data[m + 1];     // 数据数组，data[0]未用
} BTNode, *BTree;

// 搜索结果
typedef struct {
    BTree pt;
    int i;
    bool tag;
} result;

void writeLog(char *message);
int Search(BTree p,int k);
void SearchBTree(BTree t, KeyType k, result *r);
void initRoot(BTree *t);
void Traversal(BTree t, char *name,char *bookName);
void getAuthorBooks(BTree t);
void writeLiteratureToFile(FILE *file, Liter data);
void writeLiteratureToFileBinary(FILE *file, Liter data);
void Traversal_writeData(BTree t, FILE *file, void (*visit)(FILE *file, Liter data));
Liter createLiter();
void findLiter(BTree t);
void borrowBook(BTree *t);
void returnBooks(BTree *t);
void borrowByAppointment(BTree *t);
void printMenu();

#endif //BTREE_DEFANDFUN_H
