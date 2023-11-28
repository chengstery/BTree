#include "TreeVision.h"

int main(){
    BTree t;
    initRoot(&t);

    // ������Ϣ��B��
    loadDataBinary(&t);
//    loadData(&t);

    caretakers = FALSE;
    login = FALSE;
    initFace = TRUE;
    int i, re, event=0;
    char s[500];//�����ַ�������
    char str[500];
    Liter d;
    KeyType literatureNumber;

    MOUSEMSG M;//���ָ��

    while(TRUE)
    {
        if (initFace){
            interfaces();
            initFace = FALSE;
        }
        HWND hnd = GetHWnd();
        M = GetMouseMsg();//��ȡһ�������Ϣ

        switch(M.uMsg)
        {
//            case WM_MOUSEMOVE:
//                setrop2(R2_XORPEN);
//                setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
//                setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
//                setfillcolor(WHITE);//�����ɫΪ��ɫ
//                if(button_judge(M.x,M.y)!=0)
//                {
//                    if(event != button_judge(M.x,M.y))
//                    {
//                        event = button_judge(M.x,M.y);//��¼��һ�δ����İ�ť
//                        if (!caretakers && event <= 9)
//                            fillrectangle(reg[event-4][0],reg[event-4][1],reg[event-4][2],reg[event-4][3]);//�п������Σ�X1,Y1,X2,Y2��
//                        else
//                            fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//�п������Σ�X1,Y1,X2,Y2��
//                    }
//                }
//                else
//                {
//                    if(event!=0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
//                    {
//                        if (!caretakers && event <= 9)
//                            fillrectangle(reg[event-4][0],reg[event-4][1],reg[event-4][2],reg[event-4][3]);//����ͬ��Ϊԭ����ɫ
//                        else
//                            fillrectangle(reg[event-1][0],reg[event-1][1],reg[event-1][2],reg[event-1][3]);//����ͬ��Ϊԭ����ɫ
//                        event = 0;
//                    }
//                }
//                break;
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
                        treePrint(t);
                        sprintf(str, "���ڵ�ǰ�ļ�������tree.png�ļ�");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 4:
                        InputBox(s, 500, "������Ҫ���������ױ��");
                        if (sscanf(s, "%d", &literatureNumber) == 1){
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
                        }else{
                            sprintf(str, "�����Ŵ�������ȷ�������ֱ��");
                            sprintf(mes, "��������ֱ�ż�������");
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 5:
                        if (!login){
                            sprintf(str, "���ȵ�¼������������");
                            MessageBox(hnd, str, "��ʾ", MB_OK);
                            break;
                        }
                        InputBox(s, 500, "������Ҫ���ĵ����ױ��");
                        if(sscanf(s, "%d", &literatureNumber) == 1){
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
                        }else{
                            sprintf(str, "�����Ŵ�������ȷ�������ֱ��");
                            sprintf(mes, "��������ֱ�Ž�������");
                        }
                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 6:
                        if (!login){
                            sprintf(str, "���ȵ�¼�����黹����");
                            MessageBox(hnd, str, "��ʾ", MB_OK);
                            break;
                        }
                        InputBox(s, 500, "������Ҫ�黹�����ױ��");
                        if(sscanf(s, "%d", &literatureNumber) == 1){
                            re = returnBooks(&t, literatureNumber);
                            if (re == 0) {
                                sprintf(str, "���Ϊ %d �����ײ�����, �޷��黹", literatureNumber);
                                sprintf(mes, "�黹���Ϊ %d ������ʧ��, �����ײ�����", literatureNumber);
                            }
                            else if(re == 1) sprintf(str, "���Ϊ %d �����׹黹�ɹ�", literatureNumber);
                            else sprintf(str, "���Ϊ %d �����׹黹ʧ�ܣ�δ���Ļ�֤���Ŵ���", literatureNumber);
                        }else{
                            sprintf(str, "�����Ŵ�������ȷ�������ֱ��");
                            sprintf(mes, "��������ֱ�Ź黹����");
                        }

                        writeLog(mes);
                        MessageBox(hnd, str, "��ʾ", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 7:
                        MessageBox(hnd, getAuthorBooks(t), "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 8:
                        if (!login){
                            sprintf(str, "���ȵ�¼����ԤԼ��������");
                            MessageBox(hnd, str, "��ʾ", MB_OK);
                            break;
                        }
                        InputBox(s, 500, "������ҪԤԼ���ĵ����ױ��");
                        if(sscanf(s, "%d", &literatureNumber) == 1){
                            re = borrowByAppointment(&t, literatureNumber);
                            if (re == 0)
                                sprintf(str, "���Ϊ %d �����ײ�����, �޷�ԤԼ", literatureNumber);
                            else if(re == 1)
                                sprintf(str, "���Ϊ %d �������ִ�������, �޷�ԤԼ", literatureNumber);
                            else
                                sprintf(str, "���Ϊ %d ������ԤԼ�ɹ�", literatureNumber);
                        }else{
                            sprintf(str, "�����Ŵ�������ȷ�������ֱ��");
                            sprintf(mes, "��������ֱ��ԤԼ����");
                        }
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        saveDataBinary(t);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 9:
                        closegraph();//�رջ�ͼ����
                        sprintf(mes, "�˳�����");
                        writeLog(mes);
                        exit(0);//�����˳�
                    case 10:
                        re = registerUser();
                        if (re)
                            sprintf(str, "ע��ɹ�");
                        else
                            sprintf(str, "ע��ʧ��");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 11:
                        re = loginUser();
                        if (re){
                            login = TRUE;
                            initFace = TRUE;
                            sprintf(str, "��¼�ɹ�");
                        }
                        else
                            sprintf(str, "�˺Ż��������,��¼ʧ��");
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 13:
                        login = FALSE;
                        initFace = TRUE;
                        caretakers = FALSE;
                        sprintf(str, "�˳���¼�ɹ�");
                        sprintf(mes, "%s �˳���¼", userName);
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
                    case 14:
                        re = loginCaretakers();
                        if (re){
                            sprintf(str, "��¼�ɹ�");
                            sprintf(mes, "����Ա��¼");
                        }else{
                            sprintf(str, "�������, ��¼ʧ��");
                            sprintf(mes, "����Ա��¼ʧ��");
                        }
                        writeLog(mes);
                        MessageBoxA(hnd, str, "��ʾ", MB_OK);
                        FlushMouseMsgBuffer();//�����¼�����������Ϣ
                        break;
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
