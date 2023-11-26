#ifndef BTREE_GUI_DEFANDFUN_H
#define BTREE_GUI_DEFANDFUN_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include <windows.h>				//用到了定时函数sleep()

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
typedef int Status;     // 用作函数值类型，表示函数结果状态
typedef int Bool;       // 用布尔值类型
typedef int KeyType;    // 定义关键字类型为整型

#define m 3  // B树的阶，此处设为3

/* B 树关键最大最小值以及中间值 */
#define MIN_KEY ((m-1)/2)

#define MAX_LEN_TITLE 100
#define MAX_LEN_AUTHOR 100

// 装日志信息
extern char mes[500];

extern int reg[9][4];

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
    Bool tag;
} result;

int button_judge(int x,int y);
void writeLog(char *message);
int Search(BTree p,int k);
void SearchBTree(BTree t, KeyType k, result *r);
void initRoot(BTree *t);
void printKey(Liter data);
void Traversal(BTree t, char *name,char *bookName);
char *getAuthorBooks(BTree t);
void writeLiteratureToFile(FILE *file, Liter data);
void writeLiteratureToFileBinary(FILE *file, Liter data);
void Traversal_writeData(BTree t, FILE *file, void (*visit)(FILE *file, Liter data));
Liter createLiter();
Liter findLiter(BTree t, KeyType k);
int borrowBook(BTree *t, KeyType k, HWND hnd);
int returnBooks(BTree *t, KeyType k);
int borrowByAppointment(BTree *t, KeyType k);

#endif //BTREE_GUI_DEFANDFUN_H
