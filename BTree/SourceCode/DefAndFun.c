#include "DefAndFun.h"

char str[500];

void writeLog(char *message) {
    // ��ȡ��ǰʱ��
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);

    // ����־�ļ�����׷��ģʽд��
    FILE *logFile = fopen("../log.txt", "a");
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

// ������ȱ�����ӡB���Ĺؼ���
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
    printf("������Ҫ�����ĸ����ߵ����ף������������֣�:  ");
    char name[50];
    char bookName[500];
    scanf("%s", name);
    strcpy(bookName,name);
    strcat(bookName, "������: ");
    Traversal(t, name, bookName);
    printf("%s\n", bookName);
    sprintf(str, "���� %s �����ף����Ϊ:\n%s", name, bookName);
    writeLog(str);
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

Liter createLiter(){
    Liter data;
    data = (Literature*)malloc(sizeof(Literature));

    // ��ȡ�û�����
    printf("������������׵����ױ��: ");
    scanf("%d", &data->literatureNumber);

    // ������뻺����
    while (getchar() != '\n');

    printf("������������׵�������: ");
    fgets(data->title, MAX_LEN_TITLE, stdin);
    data->title[strcspn(data->title, "\n")] = '\0'; // ȥ�����з�

    printf("������������׵�����: ");
    fgets(data->author, MAX_LEN_AUTHOR, stdin);
    data->author[strcspn(data->author, "\n")] = '\0'; // ȥ�����з�


    data->currentStock = 1;
    data->totalStock = 1;
    data->borrowNum = 0;
    data->appointNum = 0;

    return data;
}

// ��������
void findLiter(BTree t){
    printf("������Ҫ���������ױ��:  ");
    KeyType k;
    scanf("%d", &k);
    result r;
    SearchBTree(t, k, &r);
    if (r.tag){
        printf(ANSI_COLOR_GREEN "���׺�: %d   ������: %s   ����: %s   �ִ���: %d   �ܿ��:%d   �ѽ�����: %d   ��ԤԼ��: %d\n" ANSI_COLOR_RESET,
               r.pt->data[r.i]->literatureNumber, r.pt->data[r.i]->title, r.pt->data[r.i]->author, r.pt->data[r.i]->currentStock, r.pt->data[r.i]->totalStock, r.pt->data[r.i]->borrowNum, r.pt->data[r.i]->appointNum);
        sprintf(str, "�������Ϊ %d ������,���Ϊ:\n���׺�: %d   ������: %s   ����: %s   �ִ���: %d   �ܿ��:%d   �ѽ�����: %d   ��ԤԼ��: %d",
                k,r.pt->data[r.i]->literatureNumber, r.pt->data[r.i]->title, r.pt->data[r.i]->author, r.pt->data[r.i]->currentStock, r.pt->data[r.i]->totalStock, r.pt->data[r.i]->borrowNum, r.pt->data[r.i]->appointNum);
    }else{
        printf(ANSI_COLOR_RED "���Ϊ %d �����ײ�����\n" ANSI_COLOR_RESET, k);
        sprintf(str, "�������Ϊ %d ������, �����ײ�����", k);
    }
    writeLog(str);
}

void borrowBook(BTree *t){
    KeyType k, x , tag = 0;
    printf("������Ҫ���ĵ����ױ��:  ");
    scanf("%d", &k);
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        printf(ANSI_COLOR_RED "���Ϊ %d �����ײ�����, �޷�����\n" ANSI_COLOR_RESET, k);
        sprintf(str, "���ı��Ϊ %d ������ʧ��, �����ײ�����", k);
        writeLog(str);
        return;
    }
    printf("�Ƿ���ԤԼ�������ױ��:\n1. ��ԤԼ\n2. ��ԤԼ\n");
    scanf("%d", &x);
    if (x == 1){
        char appIdNum[50];
        printf("������ҪԤԼʱ��֤����:  ");
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
            printf("δԤԼ��֤���Ŵ���, ֤����Ϊ: %s\n", appIdNum);
            sprintf(str, "δԤԼ��֤���Ŵ���, ֤����Ϊ: %s", appIdNum);
            writeLog(str);
            return;
        }
    }

    if (r.pt->data[r.i]->currentStock <= 0) {
        printf(ANSI_COLOR_RED "���Ϊ %d �������ִ�������, �޷�����\n" ANSI_COLOR_RESET, k);
        sprintf(str, "���ı��Ϊ %d ������ʧ��, �������ִ�������", k);
    }
    else {
        printf("���������֤����: ");
        scanf("%s", r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum]);
        printf("������黹����: ");
        scanf("%s", r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum]);

        r.pt->data[r.i]->currentStock--;
        r.pt->data[r.i]->borrowNum++;
        printf(ANSI_COLOR_GREEN "���Ϊ %d �����׽��ĳɹ�\n" ANSI_COLOR_RESET, k);
        sprintf(str, "���ı��Ϊ %d �����׳ɹ�, ����֤����: %s, �黹����: %s",
                k, r.pt->data[r.i]->borIdNumber[r.pt->data[r.i]->borrowNum-1], r.pt->data[r.i]->returnDate[r.pt->data[r.i]->borrowNum-1]);
    }

    writeLog(str);
}

void returnBooks(BTree *t){
    printf("������Ҫ�黹�����ױ��:  ");
    KeyType k;
    char idNumber[50];
    scanf("%d", &k);
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        printf(ANSI_COLOR_RED "���Ϊ %d �����ײ�����, �޷��黹\n" ANSI_COLOR_RESET, k);
        sprintf(str, "�黹���Ϊ %d ������ʧ��, �����ײ�����", k);
        writeLog(str);
        return;
    }
    else {
        printf("���������֤����: ");
        scanf("%s", idNumber);

        for (int j = 0; j < r.pt->data[r.i]->borrowNum; j++){
            if(!strcmp(r.pt->data[r.i]->borIdNumber[j], idNumber)){
                for (int x = j; x < r.pt->data[r.i]->borrowNum - 1; x++)
                    strcpy(r.pt->data[r.i]->borIdNumber[x], r.pt->data[r.i]->borIdNumber[x+1]);

                r.pt->data[r.i]->currentStock++;
                r.pt->data[r.i]->borrowNum--;
                printf(ANSI_COLOR_GREEN "���Ϊ %d �����׹黹�ɹ�\n" ANSI_COLOR_RESET, k);
                sprintf(str, "�黹���Ϊ %d �����׳ɹ�, ����֤����: %s", k, idNumber);
                writeLog(str);
                return;
            }
        }
    }
    printf(ANSI_COLOR_RED "���Ϊ %d �����׹黹ʧ�ܣ�δ���Ļ�֤���Ŵ���\n" ANSI_COLOR_RESET, k);
    sprintf(str, "�黹���Ϊ %d ������ʧ��, δ���Ļ�֤���Ŵ���, ����֤����: %s", k, idNumber);
    writeLog(str);
}

void borrowByAppointment(BTree *t){
    printf("������ҪԤԼ���ĵ����ױ��:  ");
    KeyType k;
    scanf("%d", &k);
    result r;
    SearchBTree(*t, k, &r);
    if (!r.tag) {
        printf(ANSI_COLOR_RED "���Ϊ %d �����ײ�����, �޷�ԤԼ\n" ANSI_COLOR_RESET, k);
        sprintf(str, "ԤԼ���Ϊ %d ������ʧ��, �����ײ�����", k);
    }
    else {
        if (r.pt->data[r.i]->currentStock <= 0) {
            printf(ANSI_COLOR_RED "���Ϊ %d �������ִ�������, �޷�ԤԼ\n" ANSI_COLOR_RESET, k);
            sprintf(str, "ԤԼ���Ϊ %d ������ʧ��, �������ִ�������", k);
        }
        else {
            printf("������ԤԼ֤����: ");
            scanf("%s", r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum]);

            r.pt->data[r.i]->currentStock--;
            r.pt->data[r.i]->appointNum++;
            printf(ANSI_COLOR_GREEN "���Ϊ %d ������ԤԼ�ɹ�\n" ANSI_COLOR_RESET, k);
            sprintf(str, "ԤԼ���Ϊ %d �����׳ɹ�, ԤԼ֤����: %s", k, r.pt->data[r.i]->appIdNumber[r.pt->data[r.i]->appointNum-1]);
        }
    }
    writeLog(str);
}

void printMenu() {
    printf("%s==================== ���׹���ϵͳ ======================%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
    printf("1. %s�������%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("2. %s�������%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("3. %s��������%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("4. %s��������%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("5. %s�黹����%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("6. %s��ʾ%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("7. %s����ĳ��������%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("8. %sԤԼ��������%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("0. %s�˳�%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s======================================================%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
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