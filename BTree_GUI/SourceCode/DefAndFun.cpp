#include "DefAndFun.h"

char mes[500];

int reg[9][4]={{10,40,110,70},
             {130,40,230,70},
             {250,40,350,70},
             {10,90,110,120},
             {130,90,230,120},
             {250,90,350,120},
             {10,140,110,170},
             {130,140,230,170},
             {250,140,350,170}};//9个按钮的二维数组

//按钮判断函数
int button_judge(int x,int y)
{
    if(x>reg[0][0] && x<reg[0][2] && y>reg[0][1] && y<reg[0][3])return 1;
    if(x>reg[1][0] && x<reg[1][2] && y>reg[1][1] && y<reg[1][3])return 2;
    if(x>reg[2][0] && x<reg[2][2] && y>reg[2][1] && y<reg[2][3])return 3;
    if(x>reg[3][0] && x<reg[3][2] && y>reg[3][1] && y<reg[3][3])return 4;
    if(x>reg[4][0] && x<reg[4][2] && y>reg[4][1] && y<reg[4][3])return 5;
    if(x>reg[5][0] && x<reg[5][2] && y>reg[5][1] && y<reg[5][3])return 6;
    if(x>reg[6][0] && x<reg[6][2] && y>reg[6][1] && y<reg[6][3])return 7;
    if(x>reg[7][0] && x<reg[7][2] && y>reg[7][1] && y<reg[7][3])return 8;
    if(x>reg[8][0] && x<reg[8][2] && y>reg[8][1] && y<reg[8][3])return 9;
    return 0;
}

void writeLog(char *message) {
    // 获取当前时间
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);

    // 打开日志文件，以追加模式写入
    FILE *logFile = fopen("./log.txt", "a");
    if (logFile == NULL) {
        perror("无法打开日志文件");
        return;
    }

    // 格式化当前时间
    char buffer[26];
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    // 写入日志
    fprintf(logFile, "[%s] %s\n", buffer, message);

    // 关闭文件
    fclose(logFile);
}

int Search(BTree p,int k){   // 在p->key[1..p->keyNum]找k
    int i = 1;
    while (i <= p->keyNum && k > p->key[i]) i++;
    return i;
}

void SearchBTree(BTree t, KeyType k, result *r){
    // 在m阶B树t上查找关键字k，用r返回(pt, i, tag)
    // 若查找成功，则标记tag=1，指针pt所指结点的第i个关键字等于k
    // 否则tag=0，若要插入关键字为k的记录，应位于pt结点中第i-1个和第i个关键字之间
    int i = 0, found = FALSE;
    BTree p = t, q = NULL;  // 初始，p指向根节点；p将用于指向待查结点，q指向其双亲
    while (p != NULL && FALSE == found){
        i = Search(p, k);  // 在p->key[1..p->keyNum]中查找p->key[i-1]<=p->key[i]
        if (i <= p->keyNum && p->key[i] == k) found = TRUE;  // 找到待查关键字
        else {
            q = p;
            p = p->ptr[i - 1];  // 指针下移
        }
    }

    // 查找成功，返回k的位置p及i
    if(TRUE == found) {
        (*r).pt = p;
        (*r).i = i;
        (*r).tag = TRUE;
    }else{ // 查找不成功，返回k的插入位置q及i
        (*r).pt = q;
        (*r).i = i;
        (*r).tag = FALSE;
    }
}

void initRoot(BTree *t){
    *t = NULL;
}

void printKey(Liter data){
    printf("%d ",data->literatureNumber);
}

// 深度优先遍历B树
void Traversal(BTree t, char *name,char *bookName){
    if(t!=NULL){
        Traversal(t->ptr[0], name, bookName);
        for(int i =1;i<=t->keyNum;i++){
            if (!strcmp(name, t->data[i]->author)){
                strcat(bookName, t->data[i]->title);
                strcat(bookName, " | ");
            }
            Traversal(t->ptr[i], name, bookName);
        }
    }
}

char *getAuthorBooks(BTree t){
    char name[500];
    char *bookName;

    bookName = (char *) malloc(sizeof(char)*500);

    InputBox(name, 500, "请输入要检索哪个作者的文献（输入作者名字）");

    strcpy(bookName,name);
    strcat(bookName, "的著作: ");
    Traversal(t, name, bookName);

    sprintf(mes, "检索 %s 的文献，结果为:\n%s", name, bookName);
    writeLog(mes);

    return bookName;
}

// 写入文献信息到文件
void writeLiteratureToFile(FILE *file, Liter data) {
    fprintf(file, "%d,%s,%s,%d,%d,%d\n", data->literatureNumber, data->title, data->author, data->currentStock, data->totalStock,data->borrowNum);
}

void writeLiteratureToFileBinary(FILE *file, Liter data) {
    fwrite(data, sizeof(Literature), 1, file);
}

// 遍历写入文献信息
void Traversal_writeData(BTree t, FILE *file, void (*visit)(FILE *file, Liter data)) {
    if (t != NULL) {
        Traversal_writeData(t->ptr[0], file, visit);
        for (int i = 1; i <= t->keyNum; i++) {
            visit(file, t->data[i]);
            Traversal_writeData(t->ptr[i], file, visit);
        }
    }
}


// 创建文献信息
Liter createLiter(){
    Liter data;
    data = (Literature*)malloc(sizeof(Literature));
    char s[500];

    InputBox(s, 500, "请输入文献编号、文献名和文献著者（用空格分隔）");
    sscanf(s, "%d%s%s", &data->literatureNumber, data->title, data->author);


    data->currentStock = 1;
    data->totalStock = 1;
    data->borrowNum = 0;

    return data;
}

// 检索
Liter findLiter(BTree t, KeyType k){
    result r;
    SearchBTree(t, k, &r);
    if (r.tag) return r.pt->data[r.i];
    else return NULL;
}

// 借阅
int borrowBook(BTree *t, KeyType k, HWND hnd){
    char s[500];
    Bool tag = FALSE;
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) return 0;

    int isOk;
    isOk = MessageBox(hnd, "请问是否有预约！", "提示",MB_YESNO);
    if (isOk == IDYES){
        InputBox(s, 500, "请输入要预约时的证件号");
        for(int j= 0; j < r.pt->data[r.i]->appointNum; j++){
            if(!strcmp(s,r.pt->data[r.i]->appIdNumber[j])){
                r.pt->data[r.i]->appointNum--;
                r.pt->data[r.i]->currentStock++;
                tag = 1;
                for (int y= j; y < r.pt->data[r.i]->appointNum; y++)
                    strcpy(r.pt->data[r.i]->appIdNumber[j], r.pt->data[r.i]->appIdNumber[j + 1]);
            }
        }
        if (!tag){
            sprintf(mes, "编号为 %d 的文献未预约或证件号错误, 证件号为: %s", k, s);
            return 1;
        }
    }

    if(r.pt->data[r.i]->currentStock <= 0) return 2;
    else {
        InputBox(s, 500, "请输入借阅证件号、归还日期（用空格分隔）");
        sscanf(s, "%s%s", r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum],r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum]);

        r.pt->data[r.i]->currentStock--;
        r.pt->data[r.i]->borrowNum++;
        sprintf(mes, "借阅编号为 %d 的文献成功, 借阅证件号: %s, 归还日期: %s", k, r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum-1], r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum-1]);
        return 3;
    }
}

// 归还文献
int returnBooks(BTree *t, KeyType k){
    char idNumber[500];
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) return 0;
    else {
        InputBox(idNumber, 500, "请输入借阅时的证件号");
        for (int j = 0; j < r.pt->data[r.i]->borrowNum; j++){
            if(!strcmp(r.pt->data[r.i]->borIdNumber[j], idNumber)){
                for (int x = j; x < r.pt->data[r.i]->borrowNum - 1; x++)
                    strcpy(r.pt->data[r.i]->borIdNumber[x], r.pt->data[r.i]->borIdNumber[x+1]);

                r.pt->data[r.i]->currentStock++;
                r.pt->data[r.i]->borrowNum--;
                sprintf(mes, "归还编号为 %d 的文献成功, 借阅证件号: %s", k, idNumber);
                return 1;
            }
        }
    }
    sprintf(mes, "归还编号为 %d 的文献失败, 未借阅或证件号错误, 借阅证件号: %s", k, idNumber);
    return 2;
}

// 预约借阅
int borrowByAppointment(BTree *t, KeyType k){
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        sprintf(mes, "预约编号为 %d 的文献失败, 该文献不存在", k);
        return 0;
    }
    else {
        if (r.pt->data[r.i]->currentStock <= 0) {
            sprintf(mes, "预约编号为 %d 的文献失败, 该文献现存量不足", k);
            return 1;
        }
        else {
            InputBox(r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum], 500, "请输入预约证件号");
            r.pt->data[r.i]->currentStock--;
            r.pt->data[r.i]->appointNum++;
            sprintf(mes, "预约编号为 %d 的文献成功, 预约证件号: %s", k, r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum-1]);
            return 2;
        }
    }
}

/*
1,计算机科学导论,王明,10,10,0,0
2,数据结构与算法,张小红,15,15,0,0
3,人工智能: 现代方法,李林,8,8,0,0
4,数据库管理系统,Emily Williams,5,5,0,0
5,Introduction to Computer Science,John Smith,10,10,0,0
6,Data Structures and Algorithms,Jane Doe,15,15,0,0
7,Artificial Intelligence: A Modern Approach,David Johnson,8,8,0,0
8,Database Management Systems,Emily Williams,5,5,0,0
9,Web Development Basics,Michael Brown,12,12,0,0
10,Software Engineering Principles,Lisa Taylor,7,7,0,0
11,Computer Networks: A Top-Down Approach,Robert Davis,20,20,0,0
12,Operating System Concepts,Emma Johnson,6,6,0,0
13,Introduction to Programming,Cameron White,18,18,0,0
14,Computer Graphics and Visualization,Ava Robinson,15,15,0,0
15,Web开发基础,Michael Brown,12,12,0,0
16,软件工程原理,Lisa Taylor,7,7,0,0
17,计算机网络: 自顶向下方法,Robert Davis,20,20,0,0
18,操作系统概念,Emma Johnson,6,6,0,0
19,编程导论,Cameron White,18,18,0,0
20,计算机图形学与可视化,Ava Robinson,15,15,0,0
 * */