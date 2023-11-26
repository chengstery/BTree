#include "DefAndFun.h"

char str[500];

void writeLog(char *message) {
    // 获取当前时间
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);

    // 打开日志文件，以追加模式写入
    FILE *logFile = fopen("../log.txt", "a");
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

// 深度优先遍历打印B树的关键字
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

void getAuthorBooks(BTree t){
    printf("请输入要检索哪个作者的文献（输入作者名字）:  ");
    char name[50];
    char bookName[500];
    scanf("%s", name);
    strcpy(bookName,name);
    strcat(bookName, "的著作: ");
    Traversal(t, name, bookName);
    printf("%s\n", bookName);
    sprintf(str, "检索 %s 的文献，结果为:\n%s", name, bookName);
    writeLog(str);
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

Liter createLiter(){
    Liter data;
    data = (Literature*)malloc(sizeof(Literature));

    // 读取用户输入
    printf("请输入入库文献的文献编号: ");
    scanf("%d", &data->literatureNumber);

    // 清除输入缓冲区
    while (getchar() != '\n');

    printf("请输入入库文献的文献名: ");
    fgets(data->title, MAX_LEN_TITLE, stdin);
    data->title[strcspn(data->title, "\n")] = '\0'; // 去掉换行符

    printf("请输入入库文献的著者: ");
    fgets(data->author, MAX_LEN_AUTHOR, stdin);
    data->author[strcspn(data->author, "\n")] = '\0'; // 去掉换行符


    data->currentStock = 1;
    data->totalStock = 1;
    data->borrowNum = 0;
    data->appointNum = 0;

    return data;
}

// 检索文献
void findLiter(BTree t){
    printf("请输入要搜索的文献编号:  ");
    KeyType k;
    scanf("%d", &k);
    result r;
    SearchBTree(t, k, &r);
    if (r.tag){
        printf(ANSI_COLOR_GREEN "文献号: %d   文献名: %s   著者: %s   现存量: %d   总库存:%d   已借阅数: %d   已预约数: %d\n" ANSI_COLOR_RESET,
               r.pt->data[r.i]->literatureNumber, r.pt->data[r.i]->title, r.pt->data[r.i]->author, r.pt->data[r.i]->currentStock, r.pt->data[r.i]->totalStock, r.pt->data[r.i]->borrowNum, r.pt->data[r.i]->appointNum);
        sprintf(str, "检索编号为 %d 的文献,结果为:\n文献号: %d   文献名: %s   著者: %s   现存量: %d   总库存:%d   已借阅数: %d   已预约数: %d",
                k,r.pt->data[r.i]->literatureNumber, r.pt->data[r.i]->title, r.pt->data[r.i]->author, r.pt->data[r.i]->currentStock, r.pt->data[r.i]->totalStock, r.pt->data[r.i]->borrowNum, r.pt->data[r.i]->appointNum);
    }else{
        printf(ANSI_COLOR_RED "编号为 %d 的文献不存在\n" ANSI_COLOR_RESET, k);
        sprintf(str, "检索编号为 %d 的文献, 该文献不存在", k);
    }
    writeLog(str);
}

void borrowBook(BTree *t){
    KeyType k, x , tag = 0;
    printf("请输入要借阅的文献编号:  ");
    scanf("%d", &k);
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        printf(ANSI_COLOR_RED "编号为 %d 的文献不存在, 无法借阅\n" ANSI_COLOR_RESET, k);
        sprintf(str, "借阅编号为 %d 的文献失败, 该文献不存在", k);
        writeLog(str);
        return;
    }
    printf("是否有预约借阅文献编号:\n1. 有预约\n2. 无预约\n");
    scanf("%d", &x);
    if (x == 1){
        char appIdNum[50];
        printf("请输入要预约时的证件号:  ");
        scanf("%s", appIdNum);
        for(int j= 0; j < r.pt->data[r.i]->appointNum; j++){
            if(!strcmp(appIdNum,r.pt->data[r.i]->appIdNumber[j])){
                r.pt->data[r.i]->appointNum--;
                r.pt->data[r.i]->currentStock++;
                tag = 1;
                for (int y= j; y < r.pt->data[r.i]->appointNum; y++)
                    strcpy(r.pt->data[r.i]->appIdNumber[j], r.pt->data[r.i]->appIdNumber[j + 1]);
            }
        }
        if (!tag){
            printf("未预约或证件号错误, 证件号为: %s\n", appIdNum);
            sprintf(str, "未预约或证件号错误, 证件号为: %s", appIdNum);
            writeLog(str);
            return;
        }
    }

    if (r.pt->data[r.i]->currentStock <= 0) {
        printf(ANSI_COLOR_RED "编号为 %d 的文献现存量不足, 无法借阅\n" ANSI_COLOR_RESET, k);
        sprintf(str, "借阅编号为 %d 的文献失败, 该文献现存量不足", k);
    }
    else {
        printf("请输入借阅证件号: ");
        scanf("%s", r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum]);
        printf("请输入归还日期: ");
        scanf("%s", r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum]);

        r.pt->data[r.i]->currentStock--;
        r.pt->data[r.i]->borrowNum++;
        printf(ANSI_COLOR_GREEN "编号为 %d 的文献借阅成功\n" ANSI_COLOR_RESET, k);
        sprintf(str, "借阅编号为 %d 的文献成功, 借阅证件号: %s, 归还日期: %s",
                k, r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum-1], r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum-1]);
    }

    writeLog(str);
}

void returnBooks(BTree *t){
    printf("请输入要归还的文献编号:  ");
    KeyType k;
    char idNumber[50];
    scanf("%d", &k);
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        printf(ANSI_COLOR_RED "编号为 %d 的文献不存在, 无法归还\n" ANSI_COLOR_RESET, k);
        sprintf(str, "归还编号为 %d 的文献失败, 该文献不存在", k);
        writeLog(str);
        return;
    }
    else {
        printf("请输入借阅证件号: ");
        scanf("%s", idNumber);

        for (int j = 0; j < r.pt->data[r.i]->borrowNum; j++){
            if(!strcmp(r.pt->data[r.i]->borIdNumber[j], idNumber)){
                for (int x = j; x < r.pt->data[r.i]->borrowNum - 1; x++)
                    strcpy(r.pt->data[r.i]->borIdNumber[x], r.pt->data[r.i]->borIdNumber[x+1]);

                r.pt->data[r.i]->currentStock++;
                r.pt->data[r.i]->borrowNum--;
                printf(ANSI_COLOR_GREEN "编号为 %d 的文献归还成功\n" ANSI_COLOR_RESET, k);
                sprintf(str, "归还编号为 %d 的文献成功, 借阅证件号: %s", k, idNumber);
                writeLog(str);
                return;
            }
        }
    }
    printf(ANSI_COLOR_RED "编号为 %d 的文献归还失败，未借阅或证件号错误\n" ANSI_COLOR_RESET, k);
    sprintf(str, "归还编号为 %d 的文献失败, 未借阅或证件号错误, 借阅证件号: %s", k, idNumber);
    writeLog(str);
}

void borrowByAppointment(BTree *t){
    printf("请输入要预约借阅的文献编号:  ");
    KeyType k;
    scanf("%d", &k);
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        printf(ANSI_COLOR_RED "编号为 %d 的文献不存在, 无法预约\n" ANSI_COLOR_RESET, k);
        sprintf(str, "预约编号为 %d 的文献失败, 该文献不存在", k);
    }
    else {
        if (r.pt->data[r.i]->currentStock <= 0) {
            printf(ANSI_COLOR_RED "编号为 %d 的文献现存量不足, 无法预约\n" ANSI_COLOR_RESET, k);
            sprintf(str, "预约编号为 %d 的文献失败, 该文献现存量不足", k);
        }
        else {
            printf("请输入预约证件号: ");
            scanf("%s", r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum]);

            r.pt->data[r.i]->currentStock--;
            r.pt->data[r.i]->appointNum++;
            printf(ANSI_COLOR_GREEN "编号为 %d 的文献预约成功\n" ANSI_COLOR_RESET, k);
            sprintf(str, "预约编号为 %d 的文献成功, 预约证件号: %s", k, r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum-1]);
        }
    }
    writeLog(str);
}

void printMenu() {
    printf("%s==================== 文献管理系统 ======================%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
    printf("1. %s文献入库%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("2. %s清除文献%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("3. %s检索文献%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("4. %s借阅文献%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("5. %s归还文献%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("6. %s显示%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("7. %s检索某作者文献%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("8. %s预约借阅文献%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("0. %s退出%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s======================================================%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
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