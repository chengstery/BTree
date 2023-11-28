#include "TreeVision.h"

int main(){
    BTree t;
    initRoot(&t);

    // 加载信息到B树
    loadDataBinary(&t);
//    loadData(&t);

    caretakers = FALSE;
    login = FALSE;
    initFace = TRUE;
    int i, re, event=0;
    char s[500];//输入字符串变量
    char str[500];
    Liter d;
    KeyType literatureNumber;

    MOUSEMSG M;//鼠标指针

    while(TRUE)
    {
        if (initFace){
            interfaces();
            initFace = FALSE;
        }
        HWND hnd = GetHWnd();
        M = GetMouseMsg();//获取一条鼠标消息

        switch(M.uMsg)
        {
//            case WM_MOUSEMOVE:
//                setrop2(R2_XORPEN);
//                setlinecolor(LIGHTCYAN);//线条颜色为亮青色
//                setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
//                setfillcolor(WHITE);//填充颜色为白色
//                if(button_judge(M.x,M.y)!=0)
//                {
//                    if(event != button_judge(M.x,M.y))
//                    {
//                        event = button_judge(M.x,M.y);//记录这一次触发的按钮
//                        if (!caretakers && event <= 9)
//                            fillrectangle(reg[event-4][0],reg[event-4][1],reg[event-4][2],reg[event-4][3]);//有框填充矩形（X1,Y1,X2,Y2）
//                        else
//                            fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//有框填充矩形（X1,Y1,X2,Y2）
//                    }
//                }
//                else
//                {
//                    if(event!=0)//上次触发的按钮未被修正为原来的颜色
//                    {
//                        if (!caretakers && event <= 9)
//                            fillrectangle(reg[event-4][0],reg[event-4][1],reg[event-4][2],reg[event-4][3]);//两次同或为原来颜色
//                        else
//                            fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//两次同或为原来颜色
//                        event = 0;
//                    }
//                }
//                break;
            case WM_LBUTTONDOWN:
                setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
                for(i=0;i<=10;i++)
                {
                    setlinecolor(RGB(25*i,25*i,25*i));//设置圆颜色
                    circle(M.x,M.y,2*i);
                    Sleep(20);//停顿30ms
                    circle(M.x,M.y,2*i);//抹去刚刚画的圆
                }
                //按照按钮判断左键单击后的操作
                switch(button_judge(M.x,M.y))
                {
                    //复原按钮原型
                    case 1:
                        Liter data;
                        data = createLiter();
                        if (InsertBNode(&t, data)) {
                            sprintf(str, "编号为 %d 的新文献入库成功", data->literatureNumber);
                            sprintf(mes, "编号为 %d 的新文献入库成功", data->literatureNumber);
                        }
                        else {
                            sprintf(str, "文献已存在, 编号为 %d 的文献总库存加1和现有量加1", data->literatureNumber);
                            sprintf(mes, "入库编号为 %d 的文献, 文献已存在, 文献总库存加1和现有量加1", data->literatureNumber);
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        saveDataBinary(t);
                        break;
                    case 2:
                        InputBox(s, 500, "请输入要删除的文献编号");
                        sscanf(s, "%d", &literatureNumber);
                        if (DeleteBTree(t, literatureNumber)) {
                            sprintf(str, "编号为 %d 的文献删除成功", literatureNumber);
                            sprintf(mes, "编号为 %d 的文献删除成功", literatureNumber);
                        }
                        else {
                            sprintf(str, "编号为 %d 的文献不存在, 删除失败", literatureNumber);
                            sprintf(mes, "删除编号为 %d 的文献失败, 该文献不存在", literatureNumber);
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        saveDataBinary(t);
                        break;
                    case 3:
                        treePrint(t);
                        sprintf(str, "已在当前文件夹生成tree.png文件");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 4:
                        InputBox(s, 500, "请输入要搜索的文献编号");
                        if (sscanf(s, "%d", &literatureNumber) == 1){
                            d = findLiter(t, literatureNumber);
                            if (NULL != d){
                                sprintf(str, "文献号: %d   文献名: %s   著者: %s   现存量: %d   总库存: %d   已借阅数: %d   已预约数: %d",
                                        d->literatureNumber, d->title, d->author, d->currentStock, d->totalStock, d->borrowNum, d->appointNum);
                                sprintf(mes, "检索编号为 %d 的文献,结果为:\n文献号: %d   文献名: %s   著者: %s   现存量: %d   总库存:%d   已借阅数: %d   已预约数: %d",
                                        literatureNumber, d->literatureNumber, d->title, d->author, d->currentStock, d->totalStock, d->borrowNum, d->appointNum);
                            } else {
                                sprintf(str, "编号为 %d 的文献不存在", literatureNumber);
                                sprintf(mes, "检索编号为 %d 的文献, 该文献不存在", literatureNumber);
                            }
                        }else{
                            sprintf(str, "输入编号错误，请正确输入数字编号");
                            sprintf(mes, "输入非数字编号检索文献");
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 5:
                        if (!login){
                            sprintf(str, "请先登录再来借阅文献");
                            MessageBox(hnd, str, "提示", MB_OK);
                            break;
                        }
                        InputBox(s, 500, "请输入要借阅的文献编号");
                        if(sscanf(s, "%d", &literatureNumber) == 1){
                            re = borrowBook(&t, literatureNumber, hnd);
                            if (re == 0) {
                                sprintf(str, "编号为 %d 的文献不存在, 无法借阅", literatureNumber);
                                sprintf(mes, "借阅编号为 %d 的文献失败, 该文献不存在", literatureNumber);
                            }
                            else if(re == 1) {
                                sprintf(str,"编号为 %d 的文献未预约或证件号错误",literatureNumber);

                            } else if(re == 2){
                                sprintf(str, "编号为 %d 的文献现存量不足, 无法借阅", literatureNumber);
                                sprintf(mes, "借阅编号为 %d 的文献失败, 该文献现存量不足", literatureNumber);
                            }
                            else sprintf(str, "编号为 %d 的文献借阅成功", literatureNumber);
                        }else{
                            sprintf(str, "输入编号错误，请正确输入数字编号");
                            sprintf(mes, "输入非数字编号借阅文献");
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 6:
                        if (!login){
                            sprintf(str, "请先登录再来归还文献");
                            MessageBox(hnd, str, "提示", MB_OK);
                            break;
                        }
                        InputBox(s, 500, "请输入要归还的文献编号");
                        if(sscanf(s, "%d", &literatureNumber) == 1){
                            re = returnBooks(&t, literatureNumber);
                            if (re == 0) {
                                sprintf(str, "编号为 %d 的文献不存在, 无法归还", literatureNumber);
                                sprintf(mes, "归还编号为 %d 的文献失败, 该文献不存在", literatureNumber);
                            }
                            else if(re == 1) sprintf(str, "编号为 %d 的文献归还成功", literatureNumber);
                            else sprintf(str, "编号为 %d 的文献归还失败，未借阅或证件号错误", literatureNumber);
                        }else{
                            sprintf(str, "输入编号错误，请正确输入数字编号");
                            sprintf(mes, "输入非数字编号归还文献");
                        }

                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 7:
                        MessageBox(hnd, getAuthorBooks(t), "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 8:
                        if (!login){
                            sprintf(str, "请先登录再来预约借阅文献");
                            MessageBox(hnd, str, "提示", MB_OK);
                            break;
                        }
                        InputBox(s, 500, "请输入要预约借阅的文献编号");
                        if(sscanf(s, "%d", &literatureNumber) == 1){
                            re = borrowByAppointment(&t, literatureNumber);
                            if (re == 0)
                                sprintf(str, "编号为 %d 的文献不存在, 无法预约", literatureNumber);
                            else if(re == 1)
                                sprintf(str, "编号为 %d 的文献现存量不足, 无法预约", literatureNumber);
                            else
                                sprintf(str, "编号为 %d 的文献预约成功", literatureNumber);
                        }else{
                            sprintf(str, "输入编号错误，请正确输入数字编号");
                            sprintf(mes, "输入非数字编号预约文献");
                        }
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 9:
                        closegraph();//关闭绘图环境
                        sprintf(mes, "退出程序");
                        writeLog(mes);
                        exit(0);//正常退出
                    case 10:
                        re = registerUser();
                        if (re)
                            sprintf(str, "注册成功");
                        else
                            sprintf(str, "注册失败");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 11:
                        re = loginUser();
                        if (re){
                            login = TRUE;
                            initFace = TRUE;
                            sprintf(str, "登录成功");
                        }
                        else
                            sprintf(str, "账号或密码错误,登录失败");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 13:
                        login = FALSE;
                        initFace = TRUE;
                        caretakers = FALSE;
                        sprintf(str, "退出登录成功");
                        sprintf(mes, "%s 退出登录", userName);
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 14:
                        re = loginCaretakers();
                        if (re){
                            sprintf(str, "登录成功");
                            sprintf(mes, "管理员登录");
                        }else{
                            sprintf(str, "密码错误, 登录失败");
                            sprintf(mes, "管理员登录失败");
                        }
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    default:
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
//                        printf("\r\n(%d,%d)",M.x,M.y);//打印鼠标坐标，方便调试时确定区域
                        break;
                }
                break;
        }
    }

    return 0;

}
