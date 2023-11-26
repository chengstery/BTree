#include "TreeVision.h"

int main(){
    BTree t;
    initRoot(&t);

    // ������Ϣ��B��
    loadDataBinary(&t);
//    loadData(&t);

    int i, re, event=0;
    char s[500];//�����ַ�������
    char str[500];
    Liter d;
    KeyType literatureNumber;
    short win_width,win_height;//���崰�ڵĿ�Ⱥ͸߶�
    win_width = 360;win_height = 200;
    initgraph(win_width,win_height);//��ʼ�����ڣ�������
    HWND hnd = GetHWnd();
    SetWindowText(hnd, "���׹���ϵͳ");
    for(i=0;i<256;i+=5)
    {
        setbkcolor(RGB(i,i,i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
        cleardevice();//������ȡ���ڱ���ɫ��
        Sleep(30);//��ʱ30ms
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
    LOGFONT f;//������ʽָ��
    gettextstyle(&f);					//��ȡ������ʽ
    _tcscpy(f.lfFaceName,_T("����"));	//��������Ϊ����
    f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����
    settextstyle(&f);                     // ����������ʽ
    settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
    drawtext("�������",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("ɾ������",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("��������",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("��������",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R4���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("�黹����",&R5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R5���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("����������",&R6,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R6���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("ԤԼ��������",&R7,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R7���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("��ʾB��ͼ",&R8,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R8���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("�˳�",&R9,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R9���������֣�ˮƽ���У���ֱ���У�������ʾ
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
    MOUSEMSG M;//���ָ��

    char title[] = "���׹���ϵͳ";
    outtextxy(130, 10, title);

    while(TRUE)
    {
        M = GetMouseMsg();//��ȡһ�������Ϣ

        switch(M.uMsg)
        {
            case WM_MOUSEMOVE:
                setrop2(R2_XORPEN);
                setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
                setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
                setfillcolor(WHITE);//�����ɫΪ��ɫ
                if(button_judge(M.x,M.y)!=0)
                {
                    if(event != button_judge(M.x,M.y))
                    {
                        event = button_judge(M.x,M.y);//��¼��һ�δ����İ�ť
                        fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//�п������Σ�X1,Y1,X2,Y2��
                    }
                }
                else
                {
                    if(event!=0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
                    {
                        fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//����ͬ��Ϊԭ����ɫ
                        event = 0;
                    }
                }
                break;
            case WM_LBUTTONDOWN:
                setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
                for(i=0;i<=10;i++)
                {
                    setlinecolor(RGB(25*i,25*i,25*i));//����Բ��ɫ
                    circle(M.x,M.y,2*i);
                    Sleep(20);//ͣ��30ms
                    circle(M.x,M.y,2*i);//Ĩȥ�ոջ���Բ
                }
                //���հ�ť�ж����������Ĳ���
                switch(button_judge(M.x,M.y))
                {
                    //��ԭ��ťԭ��
                    case 1:
                        Liter data;
                        data = createLiter();
                        if (InsertBNode(&t, data)) {
                            sprintf(str, "���Ϊ %d �����������ɹ�", data->literatureNumber);
                            sprintf(mes, "���Ϊ %d �����������ɹ�", data->literatureNumber);
                        }
                        else {
                            sprintf(str, "�����Ѵ���, ���Ϊ %d �������ܿ���1����������1", data->literatureNumber);
                            sprintf(mes, "�����Ϊ %d ������, �����Ѵ���, �����ܿ���1����������1", data->literatureNumber);
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        saveDataBinary(t);
                        break;
                    case 2:
                        InputBox(s, 500, "������Ҫɾ�������ױ��");
                        sscanf(s, "%d", &literatureNumber);
                        if (DeleteBTree(t, literatureNumber)) {
                            sprintf(str, "���Ϊ %d ������ɾ���ɹ�", literatureNumber);
                            sprintf(mes, "���Ϊ %d ������ɾ���ɹ�", literatureNumber);
                        }
                        else {
                            sprintf(str, "���Ϊ %d �����ײ�����, ɾ��ʧ��", literatureNumber);
                            sprintf(mes, "ɾ�����Ϊ %d ������ʧ��, �����ײ�����", literatureNumber);
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        saveDataBinary(t);
                        break;
                    case 3:
                        InputBox(s, 500, "������Ҫ���������ױ��");
                        sscanf(s, "%d", &literatureNumber);
                        d = findLiter(t, literatureNumber);
                        if (NULL != d){
                            sprintf(str, "���׺�: %d   ������: %s   ����: %s   �ִ���: %d   �ܿ��: %d   �ѽ�����: %d   ��ԤԼ��: %d",
                                    d->literatureNumber, d->title, d->author, d->currentStock, d->totalStock, d->borrowNum, d->appointNum);
                            sprintf(mes, "�������Ϊ %d ������,���Ϊ:\n���׺�: %d   ������: %s   ����: %s   �ִ���: %d   �ܿ��:%d   �ѽ�����: %d   ��ԤԼ��: %d",
                                    literatureNumber, d->literatureNumber, d->title, d->author, d->currentStock, d->totalStock, d->borrowNum, d->appointNum);
                        } else {
                            sprintf(str, "���Ϊ %d �����ײ�����", literatureNumber);
                            sprintf(mes, "�������Ϊ %d ������, �����ײ�����", literatureNumber);
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 4:
                        InputBox(s, 500, "������Ҫ���ĵ����ױ��");
                        sscanf(s, "%d", &literatureNumber);
                        re = borrowBook(&t, literatureNumber, hnd);
                        if (re == 0) {
                            sprintf(str, "���Ϊ %d �����ײ�����, �޷�����", literatureNumber);
                            sprintf(mes, "���ı��Ϊ %d ������ʧ��, �����ײ�����", literatureNumber);
                        }
                        else if(re == 1) {
                            sprintf(str,"���Ϊ %d ������δԤԼ��֤���Ŵ���",literatureNumber);

                        } else if(re == 2){
                            sprintf(str, "���Ϊ %d �������ִ�������, �޷�����", literatureNumber);
                            sprintf(mes, "���ı��Ϊ %d ������ʧ��, �������ִ�������", literatureNumber);
                        }
                        else sprintf(str, "���Ϊ %d �����׽��ĳɹ�", literatureNumber);
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 5:
                        InputBox(s, 500, "������Ҫ�黹�����ױ��");
                        sscanf(s, "%d", &literatureNumber);
                        re = returnBooks(&t, literatureNumber);
                        if (re == 0) {
                            sprintf(str, "���Ϊ %d �����ײ�����, �޷��黹", literatureNumber);
                            sprintf(mes, "�黹���Ϊ %d ������ʧ��, �����ײ�����", literatureNumber);
                        }
                        else if(re == 1) sprintf(str, "���Ϊ %d �����׹黹�ɹ�", literatureNumber);
                        else sprintf(str, "���Ϊ %d �����׹黹ʧ�ܣ�δ���Ļ�֤���Ŵ���", literatureNumber);
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 6:
                        MessageBox(hnd, getAuthorBooks(t), "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 7:
                        InputBox(s, 500, "������ҪԤԼ���ĵ����ױ��");
                        sscanf(s, "%d", &literatureNumber);
                        re = borrowByAppointment(&t, literatureNumber);
                        if (re == 0)
                            sprintf(str, "���Ϊ %d �����ײ�����, �޷�ԤԼ", literatureNumber);
                        else if(re == 1)
                            sprintf(str, "���Ϊ %d �������ִ�������, �޷�ԤԼ", literatureNumber);
                        else
                            sprintf(str, "���Ϊ %d ������ԤԼ�ɹ�", literatureNumber);
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 8:
                        treePrint(t);
                        sprintf(str, "���ڵ�ǰ�ļ�������tree.png�ļ�");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 9:
                        closegraph();//�رջ�ͼ����
                        sprintf(mes, "�˳�����");
                        writeLog(mes);
                        exit(0);//�����˳�
                    default:
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
//                        printf("\r\n(%d,%d)",M.x,M.y);//��ӡ������꣬�������ʱȷ������
                        break;
                }
                break;
        }
    }





    return 0;

}
