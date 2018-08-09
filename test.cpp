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

    if (que.count_answers > 0)
    {
        drawAnswer(que.ans[0]);
    }
    if (que.count_answers > 1)
    {
        drawAnswer(que.ans[1]);
    }
    if (que.count_answers > 2)
    {
        drawAnswer(que.ans[2]);
    }
}

int main()
{
    txCreateWindow(900, 600);

    //����� �������
    txSetFillColor(TX_BLACK);
    txClear();
    Question que0 = {"��� ��������",
        0
    };
    drawQuestion(que0);
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    Question que1 = {"��� ������",
        3,
        {{100, 250, 300, 350, "��� �����1"},
         {600, 250, 800, 350, "��� �����2"},
         {400, 350, 600, 450, "��� �����3"}}
    };
    drawQuestion(que1);
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    Question que2 = {"��� ������2",
        2,
        {{100, 250, 300, 350, "��� �����1"},
         {600, 250, 800, 350, "��� �����2"}}
    };
    drawQuestion(que2);
    txSleep(3000);

    return 0;
}
