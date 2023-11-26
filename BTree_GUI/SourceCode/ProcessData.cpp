#include "ProcessData.h"

Bool saveData(BTree t) {
    // ��д��ģʽ���ļ�
    FILE *file = fopen("../data.csv", "w+");
    if (file == NULL) {
        perror("���ļ�ʱ��������\n");
        return FALSE;
    }

    // д��CSV����
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", "���׺�", "������", "����", "�ִ���", "�ܿ��","�ѽ�����","�ѽ�����");

    // ��CSV��ʽд������
    Traversal_writeData(t, file, writeLiteratureToFile);

    // �ر��ļ�
    fclose(file);

    sprintf(mes, "����������Ϣ���ļ�");
    writeLog(mes);
    return TRUE;
}

bool saveDataBinary(BTree t) {
    FILE *file = fopen("../data.dat", "wb"); // �Զ�����д�뷽ʽ���ļ�


    if (file == NULL) {
//        perror("���ļ�ʱ��������\n");
        return FALSE;
    }

    // �Զ����Ƹ�ʽд������
    Traversal_writeData(t, file, writeLiteratureToFileBinary);

    // �ر��ļ�
    fclose(file);

    sprintf(mes, "���������������Ϣ���ļ�");
    writeLog(mes);
    return TRUE;
}

Bool loadData(BTree *t){
    FILE *file = fopen("../data.csv", "r");
    if (file == NULL) {
//        perror("Error opening file");
        return FALSE;
    }

    // ��ȡ��������һ��
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        perror("Error reading file");
        return FALSE;
    }

    // ��ȡ������ʵ������
    Liter temp = (Liter)malloc(sizeof(Literature));
    if (temp == NULL) {
        fclose(file);
        perror("Error allocating memory");
        return FALSE;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%d,%d,%d,%d\n",
                  &temp->literatureNumber, temp->title, temp->author,
                  &temp->currentStock, &temp->totalStock,&temp->borrowNum,&temp->appointNum) == 7) {

        printf("%d,%s,%s,%d,%d,%d,%d\n", temp->literatureNumber, temp->title, temp->author, temp->currentStock, temp->totalStock,temp->borrowNum,temp->appointNum);

        // ���ò��� B ���ĺ���
        InsertBNode(t, temp);

        // Ϊ��һ��������Ϣ�����µ��ڴ�
        temp = (Liter)malloc(sizeof(Literature));
        if (temp == NULL) {
            fclose(file);
            perror("Error allocating memory");
            return FALSE;
        }
    }

    // �ͷ����һ�η�����ڴ�
    free(temp);

    // �ر��ļ�
    fclose(file);

    sprintf(mes, "����������Ϣ��B��");
    writeLog(mes);
    return TRUE;
}

bool loadDataBinary(BTree *t){
    FILE *file = fopen("../data.dat", "rb"); // �Զ����ƶ�ȡ��ʽ���ļ�
    if (file == NULL) {
//        perror("�޷����ļ�");
        return FALSE;
    }

    while (!feof(file)) {
        // �����ȡ������Ϣ
        Liter data;
        data = (Literature*) malloc(sizeof(Literature));
        size_t bytesRead = fread(data, sizeof(Literature), 1, file);

//        printf("%d,%s,%s,%d,%d,%d,%d\n", data->literatureNumber, data->title, data->author, data->currentStock, data->totalStock,data->borrowNum,data->appointNum);

        // �ɹ���ȡ��һ�� Literature �ṹ�������
        if (bytesRead == 1) {
            // ���ò��� B ���ĺ���
            InsertBNode(t, data);
        }
    }

    // �ر��ļ�
    fclose(file);

    sprintf(mes, "���ض�����������Ϣ��B��");
    writeLog(mes);
    return TRUE;
}
