#include "TreeVision.h"

int main(){
    BTree t;
    initRoot(&t);

    // 加载信息到B树
    loadDataBinary(&t);
//    loadData(&t);

    int i, re, event=0;
    char s[500];//输入字符串变量
    char str[500];
    Liter d;
    KeyType literatureNumber;
    short win_width,win_height;//定义窗口的宽度和高度
    win_width = 360;win_height = 200;
    initgraph(win_width,win_height);//初始化窗口（黑屏）
    HWND hnd = GetHWnd();
    SetWindowText(hnd, "文献管理系统");
    for(i=0;i<256;i+=5)
    {
        setbkcolor(RGB(i,i,i));//设置背景色，原来默认黑色
        cleardevice();//清屏（取决于背景色）
        Sleep(30);//延时30ms
    }
    RECT R1={reg[0][0],reg[0][1],reg[0][2],reg[0][3]};
    RECT R2={reg[1][0],reg[1][1],reg[1][2],reg[1][3]};
    RECT R3={reg[2][0],reg[2][1],reg[2][2],reg[2][3]};
    RECT R4={reg[3][0],reg[3][1],reg[3][2],reg[3][3]};
    RECT R5={reg[4][0],reg[4][1],reg[4][2],reg[4][3]};
    RECT R6={reg[5][0],reg[5][1],reg[5][2],reg[5][3]};
    RECT R7={reg[6][0],reg[6][1],reg[6][2],reg[6][3]};
    RECT R8={reg[7][0],reg[7][1],reg[7][2],reg[7][3]};
    RECT R9={reg[8][0],reg[8][1],reg[8][2],reg[8][3]};
    LOGFONT f;//字体样式指针
    gettextstyle(&f);					//获取字体样式
    _tcscpy(f.lfFaceName,_T("宋体"));	//设置字体为宋体
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿
    settextstyle(&f);                     // 设置字体样式
    settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
    drawtext("入库文献",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
    drawtext("删除文献",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
    drawtext("检索文献",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
    drawtext("借阅文献",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R4内输入文字，水平居中，垂直居中，单行显示
    drawtext("归还文献",&R5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R5内输入文字，水平居中，垂直居中，单行显示
    drawtext("搜作者文献",&R6,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R6内输入文字，水平居中，垂直居中，单行显示
    drawtext("预约借阅文献",&R7,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R7内输入文字，水平居中，垂直居中，单行显示
    drawtext("显示B树图",&R8,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R8内输入文字，水平居中，垂直居中，单行显示
    drawtext("退出",&R9,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R9内输入文字，水平居中，垂直居中，单行显示
    setlinecolor(BLACK);
    rectangle(reg[0][0],reg[0][1],reg[0][2],reg[0][3]);
    rectangle(reg[1][0],reg[1][1],reg[1][2],reg[1][3]);
    rectangle(reg[2][0],reg[2][1],reg[2][2],reg[2][3]);
    rectangle(reg[3][0],reg[3][1],reg[3][2],reg[3][3]);
    rectangle(reg[4][0],reg[4][1],reg[4][2],reg[4][3]);
    rectangle(reg[5][0],reg[5][1],reg[5][2],reg[5][3]);
    rectangle(reg[6][0],reg[6][1],reg[6][2],reg[6][3]);
    rectangle(reg[7][0],reg[7][1],reg[7][2],reg[7][3]);
    rectangle(reg[8][0],reg[8][1],reg[8][2],reg[8][3]);
    MOUSEMSG M;//鼠标指针

    char title[] = "文献管理系统";
    outtextxy(130, 10, title);

    while(TRUE)
    {
        M = GetMouseMsg();//获取一条鼠标消息

        switch(M.uMsg)
        {
            case WM_MOUSEMOVE:
                setrop2(R2_XORPEN);
                setlinecolor(LIGHTCYAN);//线条颜色为亮青色
                setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
                setfillcolor(WHITE);//填充颜色为白色
                if(button_judge(M.x,M.y)!=0)
                {
                    if(event != button_judge(M.x,M.y))
                    {
                        event = button_judge(M.x,M.y);//记录这一次触发的按钮
                        fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//有框填充矩形（X1,Y1,X2,Y2）
                    }
                }
                else
                {
                    if(event!=0)//上次触发的按钮未被修正为原来的颜色
                    {
                        fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//两次同或为原来颜色
                        event = 0;
                    }
                }
                break;
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
                        InputBox(s, 500, "请输入要搜索的文献编号");
                        sscanf(s, "%d", &literatureNumber);
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
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 4:
                        InputBox(s, 500, "请输入要借阅的文献编号");
                        sscanf(s, "%d", &literatureNumber);
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
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 5:
                        InputBox(s, 500, "请输入要归还的文献编号");
                        sscanf(s, "%d", &literatureNumber);
                        re = returnBooks(&t, literatureNumber);
                        if (re == 0) {
                            sprintf(str, "编号为 %d 的文献不存在, 无法归还", literatureNumber);
                            sprintf(mes, "归还编号为 %d 的文献失败, 该文献不存在", literatureNumber);
                        }
                        else if(re == 1) sprintf(str, "编号为 %d 的文献归还成功", literatureNumber);
                        else sprintf(str, "编号为 %d 的文献归还失败，未借阅或证件号错误", literatureNumber);
                        writeLog(mes);
                        MessageBox(hnd, str, "提示", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 6:
                        MessageBox(hnd, getAuthorBooks(t), "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 7:
                        InputBox(s, 500, "请输入要预约借阅的文献编号");
                        sscanf(s, "%d", &literatureNumber);
                        re = borrowByAppointment(&t, literatureNumber);
                        if (re == 0)
                            sprintf(str, "编号为 %d 的文献不存在, 无法预约", literatureNumber);
                        else if(re == 1)
                            sprintf(str, "编号为 %d 的文献现存量不足, 无法预约", literatureNumber);
                        else
                            sprintf(str, "编号为 %d 的文献预约成功", literatureNumber);
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 8:
                        treePrint(t);
                        sprintf(str, "已在当前文件夹生成tree.png文件");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "提示", MB_OK);
                        FlushMouseMsgBuffer();//单击事件后清空鼠标消息
                        break;
                    case 9:
                        closegraph();//关闭绘图环境
                        sprintf(mes, "退出程序");
                        writeLog(mes);
                        exit(0);//正常退出
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
