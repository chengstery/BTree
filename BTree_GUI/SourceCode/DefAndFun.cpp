#include "DefAndFun.h"

char mes[500];
char userName[200];
char caretakersPassword[200] = "fjc666";

Bool caretakers;
Bool initFace;
Bool login;

int reg[14][4]={{20,80,120,110},
             {140,80,240,110},
             {20,130,120,160},
             {140,130,240,160},
             {20,180,120,210},
             {140,180,240,210},
             {20,230,120,260},
             {140,230,240,260},
             {500,350,560,380},
             {450,10,550,40},
             {450,50,550,80},
             {450,10,550,40},
             {450,50,550,80},
             {450,90,550,120}};//12个按钮的二维数组

//按钮判断函数
int button_judge(int x,int y)
{
    if (caretakers){
        if(x>reg[0][0] && x<reg[0][2] && y>reg[0][1] && y<reg[0][3])return 1;
        if(x>reg[1][0] && x<reg[1][2] && y>reg[1][1] && y<reg[1][3])return 2;
        if(x>reg[2][0] && x<reg[2][2] && y>reg[2][1] && y<reg[2][3])return 3;
        if(x>reg[3][0] && x<reg[3][2] && y>reg[3][1] && y<reg[3][3])return 4;
        if(x>reg[4][0] && x<reg[4][2] && y>reg[4][1] && y<reg[4][3])return 5;
        if(x>reg[5][0] && x<reg[5][2] && y>reg[5][1] && y<reg[5][3])return 6;
        if(x>reg[6][0] && x<reg[6][2] && y>reg[6][1] && y<reg[6][3])return 7;
        if(x>reg[7][0] && x<reg[7][2] && y>reg[7][1] && y<reg[7][3])return 8;
    }else{
        if(x>reg[0][0] && x<reg[0][2] && y>reg[0][1] && y<reg[0][3])return 4;
        if(x>reg[1][0] && x<reg[1][2] && y>reg[1][1] && y<reg[1][3])return 5;
        if(x>reg[2][0] && x<reg[2][2] && y>reg[2][1] && y<reg[2][3])return 6;
        if(x>reg[3][0] && x<reg[3][2] && y>reg[3][1] && y<reg[3][3])return 7;
        if(x>reg[4][0] && x<reg[4][2] && y>reg[4][1] && y<reg[4][3])return 8;
    }

    if (login){
        if(x>reg[11][0] && x<reg[11][2] && y>reg[11][1] && y<reg[11][3])return 12;
        if(x>reg[12][0] && x<reg[12][2] && y>reg[12][1] && y<reg[12][3])return 13;
    }else{
        if(x>reg[9][0] && x<reg[9][2] && y>reg[9][1] && y<reg[9][3])return 10;
        if(x>reg[10][0] && x<reg[10][2] && y>reg[10][1] && y<reg[10][3])return 11;
        if(x>reg[13][0] && x<reg[13][2] && y>reg[13][1] && y<reg[13][3])return 14;
    }
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
    char name[500];  // 装作者名
    char *bookName;  // 装所有书名

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


    // 初始化现有量、总库存、已借数、已预约数
    data->currentStock = 1;
    data->totalStock = 1;
    data->borrowNum = 0;
    data->appointNum = 0;

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
    Bool tag = FALSE;  // 预约标志
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
            sprintf(mes, "%s 编号为 %d 的文献未预约或证件号错误, 证件号为: %s",userName, k, s);
            return 1;
        }
    }

    if(r.pt->data[r.i]->currentStock <= 0) return 2;
    else {
        InputBox(s, 500, "请输入借阅证件号、归还日期（用空格分隔）");
        sscanf(s, "%s%s", r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum],r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum]);

        r.pt->data[r.i]->currentStock--;
        r.pt->data[r.i]->borrowNum++;
        sprintf(mes, "%s 借阅编号为 %d 的文献成功, 借阅证件号: %s, 归还日期: %s", userName, k, r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum-1], r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum-1]);
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
                sprintf(mes, "%s 归还编号为 %d 的文献成功, 借阅证件号: %s",userName, k, idNumber);
                return 1;
            }
        }
    }
    sprintf(mes, "%s 归还编号为 %d 的文献失败, 未借阅或证件号错误, 借阅证件号: %s", userName, k, idNumber);
    return 2;
}

// 预约借阅
int borrowByAppointment(BTree *t, KeyType k){
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        sprintf(mes, "%s 预约编号为 %d 的文献失败, 该文献不存在", userName, k);
        return 0;
    }
    else {
        if (r.pt->data[r.i]->currentStock <= 0) {
            sprintf(mes, "%s 预约编号为 %d 的文献失败, 该文献现存量不足", userName, k);
            return 1;
        }
        else {
            InputBox(r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum], 500, "请输入预约证件号");
            r.pt->data[r.i]->currentStock--;
            r.pt->data[r.i]->appointNum++;
            sprintf(mes, "%s 预约编号为 %d 的文献成功, 预约证件号: %s", userName, k, r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum-1]);
            return 2;
        }
    }
}

// 注册用户
Bool registerUser() {
    User user;

    // 提示用户输入注册信息
    InputBox(user.username, 200, "请输入注册用户名");
    InputBox(user.account, 200, "请输入注册账号");
    InputBox(user.password, 200, "请输入注册密码");

    // 打开文件以写入模式追加数据
    FILE *file = fopen(".\\user_data.txt", "a");
    if (file == NULL) {
        sprintf(mes, "用户注册失败");
        return FALSE;
    }

    // 将用户信息写入文件
    fprintf(file, "%s %s %s\n", user.username, user.account, user.password);

    // 关闭文件
    fclose(file);

    sprintf(mes, "用户 %s 注册成功", user.username);
    return TRUE;
}

// 登录用户
Bool loginUser() {
    char inputAccount[200];
    char inputPassword[200];

    // 提示用户输入登录信息
    InputBox(inputAccount, 200, "请输入登录账号");
    InputBox(inputPassword, 200, "请输入登录密码");

    // 打开文件以读取数据
    FILE *file = fopen(".\\user_data.txt", "r");
    if (file == NULL) {
        return FALSE;
    }

    // 逐行读取文件，并与用户输入的信息进行匹配
    User user;
    while (fscanf(file, "%s %s %s", user.username, user.account, user.password) == 3) {
        if (!strcmp(user.account, inputAccount) && !strcmp(user.password, inputPassword)) {
            strcpy(userName,user.username);
            sprintf(mes, "用户 %s 登录成功", userName);

            // 关闭文件
            fclose(file);
            return TRUE;
        }
    }

    sprintf(mes, "账号 %s 登录失败", inputAccount);
    return FALSE;

}

// 登录管理员
Bool loginCaretakers(){
    char inputPassword[200];
    InputBox(inputPassword, 200, "请输入管理员密码");
    if (!strcmp(inputPassword,caretakersPassword)){
        login = TRUE;
        initFace = TRUE;
        caretakers = TRUE;
        strcpy(userName,"管理员");
        return TRUE;
    }
    return FALSE;
};

// 可视化界面
void interfaces(){
    int i;
    short win_width,win_height;//定义窗口的宽度和高度
    win_width = 600;win_height = 400;
    initgraph(win_width,win_height);//初始化窗口（黑屏）

    HWND hnd = GetHWnd();
    SetWindowText(hnd, "文献管理系统");
    setbkcolor(RGB(255,255,255));//设置背景色，原来默认黑色
    cleardevice();//清屏（取决于背景色）

    IMAGE background;//定义一个图片名.
    loadimage(&background,".\\bg.png",600,400,1);//从图片文件获取图像
    setbkmode(TRANSPARENT);
    putimage(0, 0, &background);//绘制图像到屏幕，图片左上角坐标为(0,0)

    RECT R1={reg[0][0],reg[0][1],reg[0][2],reg[0][3]};
    RECT R2={reg[1][0],reg[1][1],reg[1][2],reg[1][3]};
    RECT R3={reg[2][0],reg[2][1],reg[2][2],reg[2][3]};
    RECT R4={reg[3][0],reg[3][1],reg[3][2],reg[3][3]};
    RECT R5={reg[4][0],reg[4][1],reg[4][2],reg[4][3]};
    RECT R6={reg[5][0],reg[5][1],reg[5][2],reg[5][3]};
    RECT R7={reg[6][0],reg[6][1],reg[6][2],reg[6][3]};
    RECT R8={reg[7][0],reg[7][1],reg[7][2],reg[7][3]};
    RECT R9={reg[8][0],reg[8][1],reg[8][2],reg[8][3]};
    RECT R10={reg[9][0],reg[9][1],reg[9][2],reg[9][3]};
    RECT R11={reg[10][0],reg[10][1],reg[10][2],reg[10][3]};
    RECT R12={reg[11][0],reg[11][1],reg[11][2],reg[11][3]};
    RECT R13={reg[12][0],reg[12][1],reg[12][2],reg[12][3]};
    RECT R14={reg[13][0],reg[13][1],reg[13][2],reg[13][3]};
    LOGFONT f;//字体样式指针
    gettextstyle(&f);					//获取字体样式
    _tcscpy(f.lfFaceName,_T("宋体"));	//设置字体为宋体
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿
    settextstyle(&f);                     // 设置字体样式
    settextcolor(GREEN);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量

    if(caretakers){
        drawtext("入库文献",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
        drawtext("删除文献",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
        drawtext("显示B树图",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R8内输入文字，水平居中，垂直居中，单行显示
        drawtext("检索文献",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
        drawtext("借阅文献",&R5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R4内输入文字，水平居中，垂直居中，单行显示
        drawtext("归还文献",&R6,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R5内输入文字，水平居中，垂直居中，单行显示
        drawtext("搜作者文献",&R7,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R6内输入文字，水平居中，垂直居中，单行显示
        drawtext("预约借阅文献",&R8,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R7内输入文字，水平居中，垂直居中，单行显示
    } else{
        drawtext("检索文献",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
        drawtext("借阅文献",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R4内输入文字，水平居中，垂直居中，单行显示
        drawtext("归还文献",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R5内输入文字，水平居中，垂直居中，单行显示
        drawtext("搜作者文献",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R6内输入文字，水平居中，垂直居中，单行显示
        drawtext("预约借阅文献",&R5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R7内输入文字，水平居中，垂直居中，单行显示
    }

    if (login){
        drawtext(userName,&R12,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R12内输入文字，水平居中，垂直居中，单行显示
        drawtext("退出登录",&R13,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R13内输入文字，水平居中，垂直居中，单行显示
    }else{
        drawtext("注册",&R10,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R10内输入文字，水平居中，垂直居中，单行显示
        drawtext("登录",&R11,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R11内输入文字，水平居中，垂直居中，单行显示
        drawtext("管理员登录",&R14,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R14内输入文字，水平居中，垂直居中，单行显示
    }
    drawtext("退出",&R9,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R9内输入文字，水平居中，垂直居中，单行显示

    setlinecolor(RED);

    if(caretakers){
        rectangle(reg[0][0],reg[0][1],reg[0][2],reg[0][3]);
        rectangle(reg[1][0],reg[1][1],reg[1][2],reg[1][3]);
        rectangle(reg[2][0],reg[2][1],reg[2][2],reg[2][3]);
        rectangle(reg[3][0],reg[3][1],reg[3][2],reg[3][3]);
        rectangle(reg[4][0],reg[4][1],reg[4][2],reg[4][3]);
        rectangle(reg[5][0],reg[5][1],reg[5][2],reg[5][3]);
        rectangle(reg[6][0],reg[6][1],reg[6][2],reg[6][3]);
        rectangle(reg[7][0],reg[7][1],reg[7][2],reg[7][3]);
    }else{
        rectangle(reg[0][0],reg[0][1],reg[0][2],reg[0][3]);
        rectangle(reg[1][0],reg[1][1],reg[1][2],reg[1][3]);
        rectangle(reg[2][0],reg[2][1],reg[2][2],reg[2][3]);
        rectangle(reg[3][0],reg[3][1],reg[3][2],reg[3][3]);
        rectangle(reg[4][0],reg[4][1],reg[4][2],reg[4][3]);
    }

    if (login){
        rectangle(reg[11][0],reg[11][1],reg[11][2],reg[11][3]);
        rectangle(reg[12][0],reg[12][1],reg[12][2],reg[12][3]);
    }else{
        rectangle(reg[9][0],reg[9][1],reg[9][2],reg[9][3]);
        rectangle(reg[10][0],reg[10][1],reg[10][2],reg[10][3]);
        rectangle(reg[13][0],reg[13][1],reg[13][2],reg[13][3]);
    }

    rectangle(reg[8][0],reg[8][1],reg[8][2],reg[8][3]);


    char title[] = "文献管理系统";
    outtextxy(80, 10, title);

    char carepwd[] = "管理员密码：fjc666 (课设原因直接给出)";
    settextcolor(RED);
    outtextxy(10, 370, carepwd);
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