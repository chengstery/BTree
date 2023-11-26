#include "TreeVision.h"

int main(){
    BTree t;
    initRoot(&t);

//    loadData(&t);
    loadDataBinary(&t);
    int choice;

    while (1) {
        printMenu();
        printf("��ѡ����: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Liter data = createLiter();
            if (InsertBNode(&t, data)) {
                printf(ANSI_COLOR_GREEN "���Ϊ %d �����������ɹ�\n" ANSI_COLOR_RESET, data->literatureNumber);
                sprintf(str, "���Ϊ %d �����������ɹ�", data->literatureNumber);
            }
            else {
                printf(ANSI_COLOR_RED "�����Ѵ���, ���Ϊ %d �������ܿ���1����������1\n" ANSI_COLOR_RESET, data->literatureNumber);
                sprintf(str, "�����Ϊ %d ������, �����Ѵ���, �����ܿ���1����������1", data->literatureNumber);
            }
            writeLog(str);
            saveDataBinary(t);
        } else if (choice == 2) {
            KeyType literatureNumber;
            printf("������Ҫɾ�������ױ��: ");
            scanf("%d", &literatureNumber);
            if (DeleteBTree(t, literatureNumber)) {
                printf(ANSI_COLOR_GREEN "���Ϊ %d ������ɾ���ɹ�\n" ANSI_COLOR_RESET, literatureNumber);
                sprintf(str, "���Ϊ %d ������ɾ���ɹ�", literatureNumber);
            }
            else {
                printf(ANSI_COLOR_RED "���Ϊ %d �����ײ�����, ɾ��ʧ��\n" ANSI_COLOR_RESET, literatureNumber);
                sprintf(str, "ɾ�����Ϊ %d ������ʧ��, �����ײ�����", literatureNumber);
            }
            writeLog(str);
            saveDataBinary(t);
        } else if (choice == 3) {
            findLiter(t);
        }else if (choice == 4) {
            borrowBook(&t);
            saveDataBinary(t);
        }else if (choice == 5) {
            returnBooks(&t);
            saveDataBinary(t);
        }else if (choice == 6) {
            treePrint(t);
            printf(ANSI_COLOR_YELLOW "���ڵ�ǰ�ļ�������tree.png�ļ�\n" ANSI_COLOR_RESET);
            writeLog("�ڵ�ǰ�ļ�������tree.png�ļ�");
        }else if (choice == 7) {
            getAuthorBooks(t);
        } else if (choice == 8) {
            borrowByAppointment(&t);
            saveDataBinary(t);
        } else if (choice == 0) {
            printf(ANSI_COLOR_RED "�˳�����!\n" ANSI_COLOR_RESET);
            writeLog("�˳�����");
            break;
        } else {
            printf(ANSI_COLOR_RED "��Ч���֣���ѡ����Ч����!!!\n" ANSI_COLOR_RESET);
        }
    }

    return 0;

}
