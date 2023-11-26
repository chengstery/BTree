#include "TreeVision.h"

int main(){
    BTree t;
    initRoot(&t);

//    loadData(&t);
    loadDataBinary(&t);
    int choice;

    while (1) {
        printMenu();
        printf("请选择功能: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Liter data = createLiter();
            if (InsertBNode(&t, data)) {
                printf(ANSI_COLOR_GREEN "编号为 %d 的新文献入库成功\n" ANSI_COLOR_RESET, data->literatureNumber);
                sprintf(str, "编号为 %d 的新文献入库成功", data->literatureNumber);
            }
            else {
                printf(ANSI_COLOR_RED "文献已存在, 编号为 %d 的文献总库存加1和现有量加1\n" ANSI_COLOR_RESET, data->literatureNumber);
                sprintf(str, "入库编号为 %d 的文献, 文献已存在, 文献总库存加1和现有量加1", data->literatureNumber);
            }
            writeLog(str);
            saveDataBinary(t);
        } else if (choice == 2) {
            KeyType literatureNumber;
            printf("请输入要删除的文献编号: ");
            scanf("%d", &literatureNumber);
            if (DeleteBTree(t, literatureNumber)) {
                printf(ANSI_COLOR_GREEN "编号为 %d 的文献删除成功\n" ANSI_COLOR_RESET, literatureNumber);
                sprintf(str, "编号为 %d 的文献删除成功", literatureNumber);
            }
            else {
                printf(ANSI_COLOR_RED "编号为 %d 的文献不存在, 删除失败\n" ANSI_COLOR_RESET, literatureNumber);
                sprintf(str, "删除编号为 %d 的文献失败, 该文献不存在", literatureNumber);
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
            printf(ANSI_COLOR_YELLOW "已在当前文件夹生成tree.png文件\n" ANSI_COLOR_RESET);
            writeLog("在当前文件夹生成tree.png文件");
        }else if (choice == 7) {
            getAuthorBooks(t);
        } else if (choice == 8) {
            borrowByAppointment(&t);
            saveDataBinary(t);
        } else if (choice == 0) {
            printf(ANSI_COLOR_RED "退出程序!\n" ANSI_COLOR_RESET);
            writeLog("退出程序");
            break;
        } else {
            printf(ANSI_COLOR_RED "无效数字，请选择有效数字!!!\n" ANSI_COLOR_RESET);
        }
    }

    return 0;

}
