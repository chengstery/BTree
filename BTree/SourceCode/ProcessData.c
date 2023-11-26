#include "ProcessData.h"

bool saveData(BTree t) {
    // 以写入模式打开文件
    FILE *file = fopen("../data.csv", "w+");
    if (file == NULL) {
        perror("打开文件时发生错误\n");
        return FALSE;
    }

    // 写入CSV标题
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", "文献号", "文献名", "著者", "现存量", "总库存","已借出数量","已预约数量");

    // 以CSV格式写入数据
    Traversal_writeData(t, file, writeLiteratureToFile);

    // 关闭文件
    fclose(file);

    writeLog("保存文献信息到文件");
    return TRUE;
}

bool saveDataBinary(BTree t) {
    FILE *file = fopen("../data.dat", "wb"); // 以二进制写入方式打开文件


    if (file == NULL) {
        perror("打开文件时发生错误\n");
        return FALSE;
    }

    // 以二进制格式写入数据
    Traversal_writeData(t, file, writeLiteratureToFileBinary);

    // 关闭文件
    fclose(file);

    writeLog("保存二进制文献信息到文件");
    return TRUE;
}

bool loadData(BTree *t){
    FILE *file = fopen("../data.csv", "r");
    if (file == NULL) {
//        perror("Error opening file");
        return FALSE;
    }

    // 读取并丢弃第一行
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        perror("Error reading file");
        return FALSE;
    }

    // 读取并插入实际数据
    Liter temp;
    temp = (Liter)malloc(sizeof(Literature));
    if (temp == NULL) {
        fclose(file);
        perror("无法打开文件");
        return FALSE;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%d,%d,%d,%d\n",
                  &temp->literatureNumber, temp->title, temp->author,
                  &temp->currentStock, &temp->totalStock, &temp->borrowNum, &temp->appointNum) == 7) {

        printf("%d,%s,%s,%d,%d,%d,%d\n", temp->literatureNumber, temp->title, temp->author, temp->currentStock, temp->totalStock,temp->borrowNum,temp->appointNum);

        // 调用插入 B 树的函数
        InsertBNode(t, temp);

        // 为下一个文献信息分配新的内存
        temp = (Liter)malloc(sizeof(Literature));
        if (temp == NULL) {
            fclose(file);
            perror("Error allocating memory");
            return FALSE;
        }
    }

    // 释放最后一次分配的内存
    free(temp);

    // 关闭文件
    fclose(file);

    writeLog("加载文献信息到B树");
    return TRUE;
}

bool loadDataBinary(BTree *t){
    FILE *file = fopen("../data.dat", "rb"); // 以二进制读取方式打开文件
    if (file == NULL) {
//        perror("无法打开文件");
        return FALSE;
    }

    while (!feof(file)) {
        // 逐个读取文献信息
        Liter data;
        data = (Literature*) malloc(sizeof(Literature));
        size_t bytesRead = fread(data, sizeof(Literature), 1, file);

//        printf("%d,%s,%s,%d,%d,%d,%d\n", data->literatureNumber, data->title, data->author, data->currentStock, data->totalStock,data->borrowNum,data->appointNum);

        // 成功读取了一个 Literature 结构体的内容
        if (bytesRead == 1) {
            // 调用插入 B 树的函数
            InsertBNode(t, data);
        }
    }

    // 关闭文件
    fclose(file);

    writeLog("加载二进制文献信息到B树");
    return TRUE;
}
