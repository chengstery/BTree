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
             {450,90,550,120}};//12����ť�Ķ�ά����

//��ť�жϺ���
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
    // ��ȡ��ǰʱ��
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);

    // ����־�ļ�����׷��ģʽд��
    FILE *logFile = fopen("./log.txt", "a");
    if (logFile == NULL) {
        perror("�޷�����־�ļ�");
        return;
    }

    // ��ʽ����ǰʱ��
    char buffer[26];
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    // д����־
    fprintf(logFile, "[%s] %s\n", buffer, message);

    // �ر��ļ�
    fclose(logFile);
}

int Search(BTree p,int k){   // ��p->key[1..p->keyNum]��k
    int i = 1;
    while (i <= p->keyNum && k > p->key[i]) i++;
    return i;
}

void SearchBTree(BTree t, KeyType k, result *r){
    // ��m��B��t�ϲ��ҹؼ���k����r����(pt, i, tag)
    // �����ҳɹ�������tag=1��ָ��pt��ָ���ĵ�i���ؼ��ֵ���k
    // ����tag=0����Ҫ����ؼ���Ϊk�ļ�¼��Ӧλ��pt����е�i-1���͵�i���ؼ���֮��
    int i = 0, found = FALSE;
    BTree p = t, q = NULL;  // ��ʼ��pָ����ڵ㣻p������ָ������㣬qָ����˫��
    while (p != NULL && FALSE == found){
        i = Search(p, k);  // ��p->key[1..p->keyNum]�в���p->key[i-1]<=p->key[i]
        if (i <= p->keyNum && p->key[i] == k) found = TRUE;  // �ҵ�����ؼ���
        else {
            q = p;
            p = p->ptr[i - 1];  // ָ������
        }
    }

    // ���ҳɹ�������k��λ��p��i
    if(TRUE == found) {
        (*r).pt = p;
        (*r).i = i;
        (*r).tag = TRUE;
    }else{ // ���Ҳ��ɹ�������k�Ĳ���λ��q��i
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

// ������ȱ���B��
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
    char name[500];  // װ������
    char *bookName;  // װ��������

    bookName = (char *) malloc(sizeof(char)*500);

    InputBox(name, 500, "������Ҫ�����ĸ����ߵ����ף������������֣�");

    strcpy(bookName,name);
    strcat(bookName, "������: ");
    Traversal(t, name, bookName);

    sprintf(mes, "���� %s �����ף����Ϊ:\n%s", name, bookName);
    writeLog(mes);

    return bookName;
}

// д��������Ϣ���ļ�
void writeLiteratureToFile(FILE *file, Liter data) {
    fprintf(file, "%d,%s,%s,%d,%d,%d\n", data->literatureNumber, data->title, data->author, data->currentStock, data->totalStock,data->borrowNum);
}

void writeLiteratureToFileBinary(FILE *file, Liter data) {
    fwrite(data, sizeof(Literature), 1, file);
}

// ����д��������Ϣ
void Traversal_writeData(BTree t, FILE *file, void (*visit)(FILE *file, Liter data)) {
    if (t != NULL) {
        Traversal_writeData(t->ptr[0], file, visit);
        for (int i = 1; i <= t->keyNum; i++) {
            visit(file, t->data[i]);
            Traversal_writeData(t->ptr[i], file, visit);
        }
    }
}


// ����������Ϣ
Liter createLiter(){
    Liter data;
    data = (Literature*)malloc(sizeof(Literature));
    char s[500];

    InputBox(s, 500, "���������ױ�š����������������ߣ��ÿո�ָ���");
    sscanf(s, "%d%s%s", &data->literatureNumber, data->title, data->author);


    // ��ʼ�����������ܿ�桢�ѽ�������ԤԼ��
    data->currentStock = 1;
    data->totalStock = 1;
    data->borrowNum = 0;
    data->appointNum = 0;

    return data;
}

// ����
Liter findLiter(BTree t, KeyType k){
    result r;
    SearchBTree(t, k, &r);
    if (r.tag) return r.pt->data[r.i];
    else return NULL;
}

// ����
int borrowBook(BTree *t, KeyType k, HWND hnd){
    char s[500];
    Bool tag = FALSE;  // ԤԼ��־
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) return 0;

    int isOk;
    isOk = MessageBox(hnd, "�����Ƿ���ԤԼ��", "��ʾ",MB_YESNO);
    if (isOk == IDYES){
        InputBox(s, 500, "������ҪԤԼʱ��֤����");
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
            sprintf(mes, "%s ���Ϊ %d ������δԤԼ��֤���Ŵ���, ֤����Ϊ: %s",userName, k, s);
            return 1;
        }
    }

    if(r.pt->data[r.i]->currentStock <= 0) return 2;
    else {
        InputBox(s, 500, "���������֤���š��黹���ڣ��ÿո�ָ���");
        sscanf(s, "%s%s", r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum],r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum]);

        r.pt->data[r.i]->currentStock--;
        r.pt->data[r.i]->borrowNum++;
        sprintf(mes, "%s ���ı��Ϊ %d �����׳ɹ�, ����֤����: %s, �黹����: %s", userName, k, r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum-1], r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum-1]);
        return 3;
    }
}

// �黹����
int returnBooks(BTree *t, KeyType k){
    char idNumber[500];
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) return 0;
    else {
        InputBox(idNumber, 500, "���������ʱ��֤����");
        for (int j = 0; j < r.pt->data[r.i]->borrowNum; j++){
            if(!strcmp(r.pt->data[r.i]->borIdNumber[j], idNumber)){
                for (int x = j; x < r.pt->data[r.i]->borrowNum - 1; x++)
                    strcpy(r.pt->data[r.i]->borIdNumber[x], r.pt->data[r.i]->borIdNumber[x+1]);

                r.pt->data[r.i]->currentStock++;
                r.pt->data[r.i]->borrowNum--;
                sprintf(mes, "%s �黹���Ϊ %d �����׳ɹ�, ����֤����: %s",userName, k, idNumber);
                return 1;
            }
        }
    }
    sprintf(mes, "%s �黹���Ϊ %d ������ʧ��, δ���Ļ�֤���Ŵ���, ����֤����: %s", userName, k, idNumber);
    return 2;
}

// ԤԼ����
int borrowByAppointment(BTree *t, KeyType k){
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        sprintf(mes, "%s ԤԼ���Ϊ %d ������ʧ��, �����ײ�����", userName, k);
        return 0;
    }
    else {
        if (r.pt->data[r.i]->currentStock <= 0) {
            sprintf(mes, "%s ԤԼ���Ϊ %d ������ʧ��, �������ִ�������", userName, k);
            return 1;
        }
        else {
            InputBox(r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum], 500, "������ԤԼ֤����");
            r.pt->data[r.i]->currentStock--;
            r.pt->data[r.i]->appointNum++;
            sprintf(mes, "%s ԤԼ���Ϊ %d �����׳ɹ�, ԤԼ֤����: %s", userName, k, r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum-1]);
            return 2;
        }
    }
}

// ע���û�
Bool registerUser() {
    User user;

    // ��ʾ�û�����ע����Ϣ
    InputBox(user.username, 200, "������ע���û���");
    InputBox(user.account, 200, "������ע���˺�");
    InputBox(user.password, 200, "������ע������");

    // ���ļ���д��ģʽ׷������
    FILE *file = fopen(".\\user_data.txt", "a");
    if (file == NULL) {
        sprintf(mes, "�û�ע��ʧ��");
        return FALSE;
    }

    // ���û���Ϣд���ļ�
    fprintf(file, "%s %s %s\n", user.username, user.account, user.password);

    // �ر��ļ�
    fclose(file);

    sprintf(mes, "�û� %s ע��ɹ�", user.username);
    return TRUE;
}

// ��¼�û�
Bool loginUser() {
    char inputAccount[200];
    char inputPassword[200];

    // ��ʾ�û������¼��Ϣ
    InputBox(inputAccount, 200, "�������¼�˺�");
    InputBox(inputPassword, 200, "�������¼����");

    // ���ļ��Զ�ȡ����
    FILE *file = fopen(".\\user_data.txt", "r");
    if (file == NULL) {
        return FALSE;
    }

    // ���ж�ȡ�ļ��������û��������Ϣ����ƥ��
    User user;
    while (fscanf(file, "%s %s %s", user.username, user.account, user.password) == 3) {
        if (!strcmp(user.account, inputAccount) && !strcmp(user.password, inputPassword)) {
            strcpy(userName,user.username);
            sprintf(mes, "�û� %s ��¼�ɹ�", userName);

            // �ر��ļ�
            fclose(file);
            return TRUE;
        }
    }

    sprintf(mes, "�˺� %s ��¼ʧ��", inputAccount);
    return FALSE;

}

// ��¼����Ա
Bool loginCaretakers(){
    char inputPassword[200];
    InputBox(inputPassword, 200, "���������Ա����");
    if (!strcmp(inputPassword,caretakersPassword)){
        login = TRUE;
        initFace = TRUE;
        caretakers = TRUE;
        strcpy(userName,"����Ա");
        return TRUE;
    }
    return FALSE;
};

// ���ӻ�����
void interfaces(){
    int i;
    short win_width,win_height;//���崰�ڵĿ�Ⱥ͸߶�
    win_width = 600;win_height = 400;
    initgraph(win_width,win_height);//��ʼ�����ڣ�������

    HWND hnd = GetHWnd();
    SetWindowText(hnd, "���׹���ϵͳ");
    setbkcolor(RGB(255,255,255));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
    cleardevice();//������ȡ���ڱ���ɫ��

    IMAGE background;//����һ��ͼƬ��.
    loadimage(&background,".\\bg.png",600,400,1);//��ͼƬ�ļ���ȡͼ��
    setbkmode(TRANSPARENT);
    putimage(0, 0, &background);//����ͼ����Ļ��ͼƬ���Ͻ�����Ϊ(0,0)

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
    LOGFONT f;//������ʽָ��
    gettextstyle(&f);					//��ȡ������ʽ
    _tcscpy(f.lfFaceName,_T("����"));	//��������Ϊ����
    f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����
    settextstyle(&f);                     // ����������ʽ
    settextcolor(GREEN);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����

    if(caretakers){
        drawtext("�������",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("ɾ������",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("��ʾB��ͼ",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R8���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("��������",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("��������",&R5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R4���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("�黹����",&R6,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R5���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("����������",&R7,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R6���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("ԤԼ��������",&R8,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R7���������֣�ˮƽ���У���ֱ���У�������ʾ
    } else{
        drawtext("��������",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("��������",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R4���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("�黹����",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R5���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("����������",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R6���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("ԤԼ��������",&R5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R7���������֣�ˮƽ���У���ֱ���У�������ʾ
    }

    if (login){
        drawtext(userName,&R12,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R12���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("�˳���¼",&R13,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R13���������֣�ˮƽ���У���ֱ���У�������ʾ
    }else{
        drawtext("ע��",&R10,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R10���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("��¼",&R11,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R11���������֣�ˮƽ���У���ֱ���У�������ʾ
        drawtext("����Ա��¼",&R14,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R14���������֣�ˮƽ���У���ֱ���У�������ʾ
    }
    drawtext("�˳�",&R9,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R9���������֣�ˮƽ���У���ֱ���У�������ʾ

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


    char title[] = "���׹���ϵͳ";
    outtextxy(80, 10, title);

    char carepwd[] = "����Ա���룺fjc666 (����ԭ��ֱ�Ӹ���)";
    settextcolor(RED);
    outtextxy(10, 370, carepwd);
}

/*
1,�������ѧ����,����,10,10,0,0
2,���ݽṹ���㷨,��С��,15,15,0,0
3,�˹�����: �ִ�����,����,8,8,0,0
4,���ݿ����ϵͳ,Emily Williams,5,5,0,0
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
15,Web��������,Michael Brown,12,12,0,0
16,�������ԭ��,Lisa Taylor,7,7,0,0
17,���������: �Զ����·���,Robert Davis,20,20,0,0
18,����ϵͳ����,Emma Johnson,6,6,0,0
19,��̵���,Cameron White,18,18,0,0
20,�����ͼ��ѧ����ӻ�,Ava Robinson,15,15,0,0
 * */