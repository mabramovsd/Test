#include "TXLib.h"

struct Answer
{
    int x1;
    int y1;
    int x2;
    int y2;
    const char* text;
};

void drawAnswer(Answer ans)
{
    txRectangle(ans.x1, ans.y1, ans.x2, ans.y2);
    txDrawText(ans.x1, ans.y1, ans.x2, ans.y2, ans.text);
}

struct Question
{
    const char* text;
    int count_answers;
    Answer ans[100];
};

void drawQuestion(Question que)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, que.text);

    for (int nomer = 0; nomer < que.count_answers; nomer++)
    {
        drawAnswer(que.ans[nomer]);
    }
}

int main()
{
    txCreateWindow(900, 600);

    Question que[100];
    int count_questions = 3;

    //��������� �������
    que[0] = {"��� ��������",
        0
    };
    que[1] = {"��� ������",
        3,
        {{100, 250, 300, 350, "��� �����1"},
         {600, 250, 800, 350, "��� �����2"},
         {400, 350, 600, 450, "��� �����3"}}
    };
    que[2] = {"��� ������2",
        2,
        {{100, 250, 300, 350, "��� �����1"},
         {600, 250, 800, 350, "��� �����2"}}
    };



    //������ �������
    int nomer_voprosa = 0;
    while (nomer_voprosa < count_questions)
    //for (int nomer = 0; nomer < count_questions; nomer++)
    {
        txSetFillColor(TX_BLACK);
        txClear();
        drawQuestion(que[nomer_voprosa]);
        //������ ������ ��� �����
        //� ��������� ����� �������
        txSleep(3000);
        nomer_voprosa = nomer_voprosa + 1;
    }

    return 0;
}
