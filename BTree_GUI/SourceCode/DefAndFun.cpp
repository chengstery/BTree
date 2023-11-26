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
             {250,140,350,170}};//9����ť�Ķ�ά����

//��ť�жϺ���
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
    char name[500];
    char *bookName;

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


    data->currentStock = 1;
    data->totalStock = 1;
    data->borrowNum = 0;

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
    Bool tag = FALSE;
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
            sprintf(mes, "���Ϊ %d ������δԤԼ��֤���Ŵ���, ֤����Ϊ: %s", k, s);
            return 1;
        }
    }

    if(r.pt->data[r.i]->currentStock <= 0) return 2;
    else {
        InputBox(s, 500, "���������֤���š��黹���ڣ��ÿո�ָ���");
        sscanf(s, "%s%s", r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum],r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum]);

        r.pt->data[r.i]->currentStock--;
        r.pt->data[r.i]->borrowNum++;
        sprintf(mes, "���ı��Ϊ %d �����׳ɹ�, ����֤����: %s, �黹����: %s", k, r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum-1], r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum-1]);
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
                sprintf(mes, "�黹���Ϊ %d �����׳ɹ�, ����֤����: %s", k, idNumber);
                return 1;
            }
        }
    }
    sprintf(mes, "�黹���Ϊ %d ������ʧ��, δ���Ļ�֤���Ŵ���, ����֤����: %s", k, idNumber);
    return 2;
}

// ԤԼ����
int borrowByAppointment(BTree *t, KeyType k){
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        sprintf(mes, "ԤԼ���Ϊ %d ������ʧ��, �����ײ�����", k);
        return 0;
    }
    else {
        if (r.pt->data[r.i]->currentStock <= 0) {
            sprintf(mes, "ԤԼ���Ϊ %d ������ʧ��, �������ִ�������", k);
            return 1;
        }
        else {
            InputBox(r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum], 500, "������ԤԼ֤����");
            r.pt->data[r.i]->currentStock--;
            r.pt->data[r.i]->appointNum++;
            sprintf(mes, "ԤԼ���Ϊ %d �����׳ɹ�, ԤԼ֤����: %s", k, r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum-1]);
            return 2;
        }
    }
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